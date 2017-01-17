#include "PBController.h"
#ifdef JUCE_APP_VERSION
#include "../JuceLibraryCode/JuceHeader.h"
#endif
#ifdef ARDUINO
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#endif

#ifdef ARDUINO
Sd2Card PBController::card;
SdVolume PBController::volume;
SdFile PBController::root;
#endif

PBController *PBController::_instance;

PBController::PBController()
{
    
}

PBController::~PBController()
{
    
}

void PBController::setup()
{
#ifdef ARDUINO
  pinMode(13,OUTPUT);
    digitalWrite(13, LOW);
#endif
    
#ifdef JUCE_APP_VERSION
    usbMidiIn = MidiInput::createNewDevice("PBrain", this);
    usbMidiOut = MidiOutput::createNewDevice("PBrain");
    usbMidiIn->start();
#endif
    
#ifdef ARDUINO
    Serial.begin(9600);
    while(!Serial){}

if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  File myFile = SD.open("example.txt", FILE_WRITE);
  myFile.close();
  if (SD.exists("example.txt")){ 
    Serial.println("example.txt exists.");
  }
  else {
    Serial.println("example.txt doesn't exist.");  
  }
#endif
  
}

#ifdef ARDUINO
void PBController::loop()
{
  
}
#endif

PBController *PBController::getInstance()
{
    if(!PBController::_instance)
    {
        PBController::_instance = new PBController();
    }
    return PBController::_instance;
}

#ifdef JUCE_APP_VERSION
void PBController::handleIncomingMidiMessage(juce::MidiInput *source, const juce::MidiMessage &message)
{
    if(message.isSysEx())
    {
        Logger::outputDebugString(String::fromUTF8( (char*)message.getSysExData()).dropLastCharacters(1));
        usbMidiOut->sendMessageNow(message);
    }
}
#endif







