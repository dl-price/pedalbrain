#include "PBController.h"
#ifdef JUCE_APP_VERSION
#include "../JuceLibraryCode/JuceHeader.h"
#endif
#ifdef ARDUINO
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#define usbMidi usbMIDI
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
    while(usbMidi.read())
    {
        //usbMidi.sendSysEx(usbMidi.getData1(), usbMidi.getSysExArray());
        //Serial.println("Send");
        char *chars = (char*)usbMidi.getSysExArray();
        String str = chars;
        
        String str2 = str.substring(1, str.length());
        if(str2.startsWith("}",0))
        {
            String str3 = str2.substring(1, str2.length());
            receivedPBSysex(str3);
        }
    }
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
        //Logger::outputDebugString(String::fromUTF8( (char*)message.getSysExData()).dropLastCharacters(1));
        //usbMidiOut->sendMessageNow(message);
        String newStr = String::fromUTF8( (char*)message.getSysExData());
        if(newStr.getCharPointer()[0]==(char)0x7D)
        {
            receivedPBSysex(newStr.substring(1));
        }
    }
}
#endif

void PBController::receivedPBSysex(String message)
{
    if(message=="Head")
    {
        sendPBSysex("Shoulders");
    }
    if(message=="Knees")
    {
        sendPBSysex("Toes");
    }
}

void PBController::sendPBSysex(String message)
{
#ifdef ARDUINO
    String newMessage = String((char)0xF0) + "}" + message + String((char)0xF7);
    
    char *chars = new char();
    
    newMessage.toCharArray(chars, newMessage.length());
    
    usbMidi.sendSysEx(newMessage.length(), (uint8_t*)chars);
#endif
#ifdef JUCE_APP_VERSION
    String newMessage = "}" + message;
    CharPointer_UTF8 charPnt = newMessage.getCharPointer();
    
    usbMidiOut->sendMessageNow(MidiMessage::createSysExMessage(charPnt, charPnt.sizeInBytes()));
#endif
}







