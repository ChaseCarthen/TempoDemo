#include "TempoDetect.h"
#include <iostream>
/*
   	   float Tempo;
	   Leap::Vector highpoint;
	   Leap::Vector lowpoint;
	   Leap::Vector currentDirection;
	   clock_t start;
	   clock_t finish;
	   bool highPoint;
	   bool lowPoint;
*/
TempoDetect::TempoDetect()
{
	Tempo = 120.0;
	range = 25.0;
	count = 0;
	lastDownBeat = highpoint = Leap::Vector(0.0,0.0,0.0);
	lowpoint = Leap::Vector(0.0,0.0,0.0);
	currentDirection = Leap::Vector(0.0,0.0,0.0);
	lowPoint = false;
	highPoint = false;
	testCheck = false;
}

/* *****************************
Function: detect
Author: Chase Carthen
Description: Accepts a point given to the algorith and a velocity vector.

Starts a clock from the instant the hand enters the leaps field and
then stops the clock when it detects a downbeat. The BPM is then calculated.

Addition:
Counting Downbeats and keeping track of patterns.

********************************/
bool TempoDetect::detect(Leap::Vector point, Leap::Vector velocity, bool& still)
{
    		   
		   //if(tempor.angleTo(velocity)*Leap::RAD_TO_DEG<11)
		//	   std::cout << tempor.angleTo(velocity)*Leap::RAD_TO_DEG << " " << velocity.normalized() << std::endl;
	// for detecting if hand is still
	if(previousPoint.distanceTo(point) <= 3.0)
	{
	   still = true;
       return false;
	}
	else
	{
		still = false;
	}
	if(!highPoint && !lowPoint)
	{
		lastDownBeat = lowpoint =highpoint = point;
		highPoint = true;
		start = clock();
		previousPoint = point;
		average = 0;
		frameCount =0;
		beatone = false;
		return false;
	}
	//drop phase
	else if ( highPoint)
	{
       if(highpoint == lastDownBeat)
		   lastDownBeat = point;  // Really a new down -- this will set a new downbeat if person is replacing hands in or just first time placing in.
	   if(velocity.y >= 0.0f /*&& highpoint.magnitudeSquared() <= point.magnitudeSquared() && lastDownBeat.distanceTo(point) < range*/)
	   {
		   finish = clock() - start;
		   double interval = finish / (double)CLOCKS_PER_SEC;
		   lowpoint = highpoint = point;
		   // calculate BPM 1 B / X SEC * 60 sec / 1 min = Y B / MIN
		   float LastTempo = Tempo;
		   Tempo = 1.0/interval*60.0;
		   if((testpoint - point).magnitude() <200)
		   count++;
		   else
			   count = 0;
		   //if(beatone)
		//	   count =0;
		   //beatone = false;
		   if(Tempo > 400.0)
		   {
			   Tempo = LastTempo;
		   }
		   else
		   {
			   lastDownBeat = point;
		   }
		   testCheck = false;
		   highPoint = false;
		   lowPoint = true;
		   start=clock();
		   average = average/(float)frameCount;
		   //std::cout << average *Leap::RAD_TO_DEG<< std::endl;
		   average = 0;
		   frameCount = 0;
		   //std::cout << (testpoint - point).magnitude() << std::endl;
		   //if(tempor.angleTo(velocity)*Leap::DEG_TO_RAD < 2.0f)
		   //{
		//	   count = 0;
		  // }
		   previousPoint = point;
		   return true;
	   }
	   else
	   {
		   average += velocity.angleTo( Leap::Vector::down());
		   if(15.5f<Leap::RAD_TO_DEG*velocity.angleTo( Leap::Vector::down()) && !testCheck)
		   {
			   testpoint = point;
			   testCheck = true;
		   }
		   
		   frameCount++;
		   highpoint = point;
	   }
	}
	// rise phase
	else if(lowPoint)
	{
		if(velocity.y <= 0.0f /*&& point.magnitudeSquared() <= lowpoint.magnitudeSquared()*/)
		{
		   finish = clock() - start;
		   lowpoint = highpoint = point;
		   highPoint = true;
		   lowPoint = false;
		   previousPoint = point;
		   //std::cout << velocity.angleTo(Leap::Vector::down())*Leap::RAD_TO_DEG << std::endl;
		   return true;
		}
	    else
		{
			///average += velocity.angleTo( Leap::Vector::down());
		    //frameCount++;
            lowpoint = point;
		}
	}
    previousPoint = point;
	return false;
}
float TempoDetect::getTempo()
{
	return Tempo;
	if (Tempo < 30)
		return 30.0;
	else if( Tempo > 400.0)
		return 400.0;
	else
		return Tempo;
}
void TempoDetect::reset()
{
	lowPoint = highPoint = false;
}

float TempoDetect::getCount()
{
	return count;
}