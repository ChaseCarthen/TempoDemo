#include <iostream>
#include "Leap.h"
#include "TempoListner.h"
#include <time.h>
using namespace Leap;


int main()
{
  // Create a sample listener and controller
  TempoListener listener;
  Controller controller;

  // Have the sample listener receive events from the controller
  controller.addListener(listener);

  // Keep this process running until Enter is pressed
  std::cout << "Press Enter to quit..." << std::endl;
  std::cin.get();
  
  // Remove the sample listener when done
  controller.removeListener(listener);
	return 0;
}