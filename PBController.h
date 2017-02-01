#ifndef PBControllerH
#define PBControllerH

#define MAX_PAGES 15
#define MAX_BUTTONS 11
#define MAX_DEVICES 16

class PBController;
extern PBController pbController;


#include "ButtonModel.h"
#include "PageModel.h"
#include "PresetModel.h"
#include "DeviceModel.h"


#ifdef JUCE_APP_VERSION
#include "../JuceLibraryCode/JuceHeader.h"
#endif
#ifdef ARDUINO
#include <SD.h>
#ifndef JsonH
#define JsonH
#include <ArduinoJson.h>
#endif


#endif

#ifdef JUCE_APP_VERSION
class PBController : public MidiInputCallback
#endif
#ifdef ARDUINO
class PBController
#endif
{
  public:
    PBController();
    ~PBController(){};
    const char *boardModel = "TestBoardA";
    const double firmwareVersion = 0.01;
    const char *boardName = "Dan's Board";
    
    PageModel *getCurrentPage();
    
#ifdef JUCE_APP_VERSION
    MidiInput *usbMidiIn;
    MidiOutput *usbMidiOut;
    

#endif

#ifdef ARDUINO
static Sd2Card card;
static SdVolume volume;
static SdFile root;
#endif
    
#ifdef ARDUINO
    void loop();
#endif
#ifdef JUCE_APP_VERSION
    void handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message) override;
#endif
    void setup();
    void receivedPBSysex(String message);
    void sendPBSysex(String message);
    void xLog(String message);
#ifdef ARDUINO
    void sendPBSysex(JsonObject &root);
#endif
    
    PageModel *getPage(int pageId);
    
    void sendAllParametersViaSysex();
    
private:
    int _currPage = 1;


};







#endif
