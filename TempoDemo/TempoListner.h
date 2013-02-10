#include "Leap.h"
#include "TempoDetect.h"
using namespace Leap;
//class TempoDetect;

class TempoListener : public Listener {
  public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
	private:
	int frameCount;
	int maxFrameCount;
	bool isStill;
};
