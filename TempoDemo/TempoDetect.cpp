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
	highpoint = Leap::Vector(0.0,0.0,0.0);
	lowpoint = Leap::Vector(0.0,0.0,0.0);
	currentDirection = Leap::Vector(0.0,0.0,0.0);
	lowPoint = false;
	highPoint = false;
}
bool TempoDetect::detect(Leap::Vector point, Leap::Vector normal)
{
			  // std::cout << normal.y << std::endl;
	if(!highPoint && !lowPoint)
	{
		lowpoint =highpoint = point;
		highPoint = true;
		start = clock();
		return false;
	}
	else if ( highPoint)
	{

	   if(normal.y >= 0.0f && lowpoint.magnitudeSquared() <= point.magnitudeSquared())
	   {
		   finish = clock() - start;
		   double interval = finish / (double)CLOCKS_PER_SEC;
		   lowpoint = highpoint = point;
		   // calculate BPM 1 B / X SEC * 60 sec / 1 min = Y B / MIN
		   Tempo = 1.0/interval*60.0;
		   highPoint = false;
		   lowPoint = true;
		   start=clock();
		   return true;
	   }
	   else
		   lowpoint = point;
	}
	if(lowPoint)
	{
		if(normal.y <= 0.0f && point.magnitudeSquared() <= highpoint.magnitudeSquared())
		{
		   finish = clock() - start;
		   lowpoint = highpoint = point;
		   highPoint = true;
		   lowPoint = false;
		   return true;
		}
	    else
            highpoint = point;
	}
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