
#ifdef JUCE_APP_VERSION
#include "../JuceLibraryCode/JuceHeader.h"
#endif
#ifdef ARDUINO
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>
#define usbMidi usbMIDI
#endif

#include "PBController.h"
#include "DeviceModel.h"
#include "PageModel.h"
#include <MIDI.h>

#ifdef ARDUINO
Sd2Card PBController::card;
SdVolume PBController::volume;
SdFile PBController::root;

#endif

PBController pbController = PBController();

PBController::PBController()
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
    Serial.begin(38400);
    while(!Serial){}

if (!SD.begin(BUILTIN_SDCARD)) {
    pbController.xLog("SD initialization failed!");
    return;
  }
    pbController.xLog("SD initialization done.");

    PageModel::initAllModels();
    DeviceModel::initAllModels();
    
    MIDI.begin(MIDI_CHANNEL_OMNI);
    
#endif
  
}

#ifdef ARDUINO
void PBController::loop()
{
    /*if(millis() - devicesSaved> 5000 && devicesChanged)
    {
        Serial.println("Saving devices");
        DeviceModel::writeAllToFile();
        devicesSaved = millis();
        devicesChanged = false;
    }
    if(millis() - pagesSaved > 5000 && pagesChanged)
    {
        Serial.println("Saving pages");
        PageModel::writeAllToFile();
        pagesSaved = millis();
        pagesChanged = false;
    }*/
    //MIDI.sendControlChange(127,127,16);
    
    while(usbMidi.read())
    {
        String str = (char*)usbMidi.getSysExArray();
        
        pbController.xLog("midi");
        String str2 = str.substring(1, str.length());
        pbController.xLog(str);
        if(str.charAt(1) == '}')
        {
            pbController.xLog("sysex");
            String str3 = str2.substring(1, str2.length());
            receivedPBSysex(str3);
        }
    }
}
#endif

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
  
    pbController.xLog("Received SysEx");

    
#ifdef JUCE_APP_VERSION
    var objVar = JSON::fromString(message);
    DynamicObject *obj = objVar.getDynamicObject();
    
    Logger::outputDebugString(obj->getProperty("request"));
#endif
    
#ifdef ARDUINO
    DynamicJsonBuffer jsonBuffer;
    JsonObject &root = jsonBuffer.parseObject(message);
    if(root["send"] == "device")
    {
        DeviceModel::getDevice((int)root["model"]["index"])->updateFromSysex(root);
        
    }
    else if(root["send"] == "page")
    {
        PageModel::getPageForIndex((int)root["model"]["index"])->updateFromSysex(root);
    }
    else if(root["send"] == "button")
    {
        ButtonModel::getButtonForIndices((int)root["model"]["pageIndex"], (int)root["model"]["index"])->updateFromSysex(root);
    }
    else if(root["send"] == "buttonState")
    {
        int btnIndex = root["buttonIndex"];
        int pageIndex = root["pageIndex"];
        int state = root["state"];
        
        ButtonModel *btn = PageModel::getPageForIndex(pageIndex)->getButtonForIndex(btnIndex);
        
        btn->press(state);
    }
    if(root["request"] == "boardInfo")
    {
        JsonObject &root2 = jsonBuffer.createObject();
        root2["send"] = "boardInfo";
        root2["model"] = boardModel;
        root2["version"] = firmwareVersion;
        root2["name"] = boardName;
        
        sendPBSysex(root2);
    }
    else if(root["request"] == "solidify")
    {
        digitalWrite(13, HIGH);
        JsonObject &root2 = jsonBuffer.createObject();
        root2["send"] = "solidified";
        sendPBSysex(root2);
    }
    else if(root["request"] == "allParameters")
    {
        sendAllParametersViaSysex();
    }
    
#endif
    
}

#ifdef ARDUINO
void PBController::sendPBSysex(JsonObject &root)
{
    String output;
    root.printTo(output);
    String toSend = String((char)0xF0) + "}" + output + String((char)0xF7);
    usbMidi.sendSysEx(toSend.length(), (uint8_t*)toSend.c_str());
}
#endif

void PBController::sendPBSysex(String message)
{
#ifdef ARDUINO
    
    String newMessage = String((char)0xF0) + "}" + message + String((char)0xF7);
   
    usbMidi.sendSysEx(newMessage.length(), (uint8_t*)newMessage.c_str());
 
#endif
#ifdef JUCE_APP_VERSION
    String newMessage = "}" + message;
    CharPointer_UTF8 charPnt = newMessage.getCharPointer();
    
    
    usbMidiOut->sendMessageNow(MidiMessage::createSysExMessage(charPnt, charPnt.sizeInBytes()));
    
#endif
}

void PBController::sendAllParametersViaSysex()
{
    PageModel::sendAllViaSysex();
    DeviceModel::sendAllViaSysex();
}

void PBController::xLog(String message)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &obj = jsonBuffer.createObject();
    obj["send"] = "xLog";
    obj["message"] = message;
    sendPBSysex(obj);
}

PageModel *PBController::getCurrentPage()
{
    return PageModel::getPage(_currPage);
}








