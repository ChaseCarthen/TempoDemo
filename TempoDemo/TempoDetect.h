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
	  bool detect(Leap::Vector point, Leap::Vector velocity, bool& still );
	  float getTempo();
	  float getCount();
	  void reset();

   private:
	   float Tempo;
	   Leap::Vector highpoint;
	   Leap::Vector lowpoint;
	   Leap::Vector lastDownBeat;
	   Leap::Vector currentDirection;
	   Leap::Vector previousPoint;
	   Leap::Vector testpoint;
	   Leap::Vector testpoint2;
	   clock_t start;
	   clock_t finish;
	   bool highPoint;
	   bool lowPoint;
	   bool testCheck;
	   bool beatone;
	   float range;
	   int count;
	   int frameCount;
	   float average;
};