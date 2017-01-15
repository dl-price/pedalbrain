#include "PBController.h"
#ifdef JUCE_APP_VERSION
#include "../JuceLibraryCode/JuceHeader.h"
#endif
#ifdef ARDUINO
#include <Arduino.h>
#endif

#ifdef JUCE_APP_VERSION
MidiInput *PBController::usbMidiIn;
MidiOutput *PBController::usbMidiOut;
#endif

void PBController::setup()
{
#ifdef ARDUINO
  pinMode(13,OUTPUT);
    digitalWrite(13, LOW);
#endif
    
#ifdef JUCE_APP_VERSION
    //PBController::usbMidiIn = MidiInput::createNewDevice("PBrain", NULL);
    PBController::usbMidiOut = MidiOutput::createNewDevice("PBrain");
#endif
  
}

void PBController::loop()
{
  
}





