#ifndef PBControllerH
#define PBControllerH

class PBController;
#ifdef JUCE_APP_VERSION
#include "../JuceLibraryCode/JuceHeader.h"
#endif
#ifdef ARDUINO
#include <SD.h>
#include <ArduinoJson.h>

extern StaticJsonBuffer<3000> jsonBuffer;
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
    ~PBController();
    static PBController *getInstance();
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
#ifdef ARDUINO
    void sendPBSysex(JsonObject &root);
#endif
    
    enum MessageType : uint8_t{
        RequestBoardInfo,
        SentBoardInfo
    };
    enum RequestBoardInfoMessages : uint8_t {
        Name,
        Type,
        Version
    };
    
private:
    static PBController *_instance;


};



#endif
