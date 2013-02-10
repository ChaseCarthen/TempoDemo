#include "TempoListner.h"

TempoDetect globalDector;

void TempoListener::onInit(const Controller& controller) {
  std::cout << "Initialized" << std::endl;
  frameCount = 0;
  maxFrameCount = 100;
  isStill = false;
}

void TempoListener::onConnect(const Controller& controller) {
  std::cout << "Connected" << std::endl;
}

void TempoListener::onDisconnect(const Controller& controller) {
  std::cout << "Disconnected" << std::endl;
}

void TempoListener::onExit(const Controller& controller) {
  std::cout << "Exited" << std::endl;
}

void TempoListener::onFrame(const Controller& controller) {
  // Get the most recent frame and report some basic information
  const Frame frame = controller.frame();
  bool dummy;
  if(isStill)
  {
	  std::cout << "Your holding your hand still dummy" << std::endl;
  }
  if(frame.hands().count() >= 1 )
  {
	  if(globalDector.detect(frame.hands()[0].palmPosition(),frame.hands()[0].palmVelocity(),isStill))
	  {
		  frameCount = 0;
	  }
	  else
	  {
		  frameCount++;
	  }
	  if(frameCount >= 100)
	  {
          frameCount = 0;
		  globalDector.reset();
	  }
	  std::cout << "Tempo " << globalDector.getTempo() << std::endl;
	  std::cout << globalDector.getCount() << std::endl;
  }
  else if(controller.frame(1).hands().count() >= 1)
  {
	  if(globalDector.detect(controller.frame(1).hands()[0].palmPosition(),controller.frame(1).hands()[0].palmVelocity(),dummy))
	  {
		  frameCount = 0;
	  }
	  else
	  {
		  frameCount++;
	  }
	  if(frameCount >= maxFrameCount)
	  {
          frameCount = 0;
		  globalDector.reset();
	  }
	  //std::cout << "Tempo past" << globalDector.getTempo() << std::endl;
  }
  else
  {
	  globalDector.reset();
  }

}