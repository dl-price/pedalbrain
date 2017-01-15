#ifndef PBControllerH
#define PBControllerH

class PBController;
#ifdef JUCE_APP_VERSION
#include "../JuceLibraryCode/JuceHeader.h"
#endif

class PBController {
  public:
#ifdef JUCE_APP_VERSION
    static MidiInput *usbMidiIn;
    static MidiOutput *usbMidiOut;

#endif
    
    static void loop();
    static void setup();


};



#endif
