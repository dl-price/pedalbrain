#ifndef PBControllerH
#define PBControllerH

class PBController;
#ifdef JUCE_APP_VERSION
#include "../JuceLibraryCode/JuceHeader.h"
#endif
#ifdef ARDUINO
#include <SD.h>
#endif

class PBController {
  public:
#ifdef JUCE_APP_VERSION
    static MidiInput *usbMidiIn;
    static MidiOutput *usbMidiOut;

#endif

#ifdef ARDUINO
static Sd2Card card;
static SdVolume volume;
static SdFile root;
#endif
    
    static void loop();
    static void setup();


};



#endif
