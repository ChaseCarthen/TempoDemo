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
	lastDownBeat = highpoint = Leap::Vector(0.0,0.0,0.0);
	lowpoint = Leap::Vector(0.0,0.0,0.0);
	currentDirection = Leap::Vector(0.0,0.0,0.0);
	lowPoint = false;
	highPoint = false;
}

/* *****************************
Function: detect
Author: Chase Carthen
Description: Accepts a point given to the algorith and a velocity vector.

Starts a clock from the instant the hand enters the leaps field and
then stops the clock when it detects a downbeat. The BPM is then calculated.

********************************/
bool TempoDetect::detect(Leap::Vector point, Leap::Vector velocity)
{
    
	// for detecting if hand is still
	if(previousPoint.distanceTo(point) <= 3.0)
       return false;
	if(!highPoint && !lowPoint)
	{
		lastDownBeat = lowpoint =highpoint = point;
		highPoint = true;
		start = clock();
		previousPoint = point;
		return false;
	}
	else if ( highPoint)
	{
       if(highpoint == lastDownBeat)
		   lastDownBeat = point;  // Really a new down -- this will set a new downbeat if person is replacing hands in or just first time placing in.
	   if(velocity.y >= 0.0f && highpoint.magnitudeSquared() <= point.magnitudeSquared() && lastDownBeat.distanceTo(point) < range)
	   {
		   finish = clock() - start;
		   double interval = finish / (double)CLOCKS_PER_SEC;
		   lowpoint = highpoint = point;
		   // calculate BPM 1 B / X SEC * 60 sec / 1 min = Y B / MIN
		   float LastTempo = Tempo;
		   Tempo = 1.0/interval*60.0;
		   if(Tempo > 400.0)
		   {
			   Tempo = LastTempo;
		   }
		   else
		   {
			   lastDownBeat = point;
		   }
		   highPoint = false;
		   lowPoint = true;
		   start=clock();
		   previousPoint = point;
		   return true;
	   }
	   else
	   {
		   highpoint = point;
		   //return true;
	   }
	}
	else if(lowPoint)
	{
		if(velocity.y <= 0.0f && point.magnitudeSquared() <= lowpoint.magnitudeSquared())
		{
		   finish = clock() - start;
		   lowpoint = highpoint = point;
		   highPoint = true;
		   lowPoint = false;
		   previousPoint = point;
		   return true;
		}
	    else
		{
            lowpoint = point;
			//return true;
		}
	}
    previousPoint = point;
	return false;
}
float TempoDetect::getTempo()
{
	return Tempo;
	/*if (Tempo < 120)
		return 120.0;
	else
		return Tempo;*/
}
void TempoDetect::reset()
{
	lowPoint = highPoint = false;
}