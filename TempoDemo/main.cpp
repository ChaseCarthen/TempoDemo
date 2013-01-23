#include <iostream>
#include "Leap.h"
#include "TempoDetect.h"
#include <time.h>
using namespace Leap;
TempoDetect globalDector;
class SampleListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
};

void SampleListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
}

void SampleListener::onDisconnect(const Controller& controller) {
  std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void SampleListener::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
  const Frame frame = controller.frame();
  if(frame.hands().count() >= 1 )
  {
	  globalDector.detect(frame.hands()[0].palmPosition(),frame.hands()[0].palmVelocity());
	  std::cout << "Tempo " << globalDector.getTempo() << std::endl;
  }
  else
  {
	  globalDector.reset();
  }
}

int main()
{
  // Create a sample listener and controller
  SampleListener listener;
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