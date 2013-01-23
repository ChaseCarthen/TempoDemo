/* TempoDetect.h
   Author: Chase Carthen
   Version: 1.0
   Dependencies: Leap SDK 7.1, Magic and Voodoo
*/
#include <time.h>
#include "LeapMath.h"

class TempoDetect
{
   public:
      TempoDetect();
	  bool detect(Leap::Vector point, Leap::Vector normal );
	  float getTempo();
	  void reset();

   private:
	   float Tempo;
	   Leap::Vector highpoint;
	   Leap::Vector lowpoint;
	   Leap::Vector currentDirection;
	   clock_t start;
	   clock_t finish;
	   bool highPoint;
	   bool lowPoint;
};