#include "ButtonModel.h"
#include "PageModel.h"
#include <ArduinoJson.h>
#include <MIDI.h>

ButtonModel *ButtonModel::getButtonForIndices(int pageIndex, int index)
{
    PageModel *pg = PageModel::getPageForIndex(pageIndex);
    
    return pg->getButtonForIndex(index);
    
}

void ButtonModel::updateFromJson(JsonObject &root)
{
    _page = root["pageIndex"];
    if(root.containsKey("name"))
    {
    _name = root["name"].asString();
    }
    else
    {
        _name = "";
    }

    type = root["type"];
    ledOn = root["ledOn"];
    ledOff = root["ledOff"];
    if(root.containsKey("label"))
    {
    label = root["label"].asString();
    }
    else
    {
        label = "";
    }
    if(root.containsKey("mainAudioId"))
    {
        audioId = root["mainAudioId"];
    }
    if(root.containsKey("mainDeviceId"))
    {
        deviceId = root["mainDeviceId"];
    }
    if(root.containsKey("mainAudioOn"))
    {
        audioOn = root["mainAudioOn"];
    }
    if(root.containsKey("mainAudioOff"))
    {
        audioOff = root["mainAudioOff"];
    }
    if(root.containsKey("mainAudioCC"))
    {
        audioCC = root["mainAudioCC"];
    }

    
}

String ButtonModel::getFilename()
{
    char fileName[30];
    strcpy(fileName, getDirectory().c_str());
    
    strcat(fileName, "/");
    char indexName[2];
    sprintf(indexName, "%d", _index);
    strcat(fileName, indexName);
    strcat(fileName, ".txt");
    
    return fileName;
}

void ButtonModel::writeToJson(JsonObject &root)
{
    root["index"] = _index;
    root["pageIndex"] = _page;
    if(_name.length())
    {
    root["name"] = _name;
    }
    root["type"] = type;
    root["ledOn"] = ledOn;
    root["ledOff"] = ledOff;
    if(label.length())
    {
    root["label"] = label;
    }
    if(audioId)
    {
        root["mainAudioId"] = audioId;
    }
    if(deviceId)
    {
        root["mainDeviceId"] = deviceId;
    }
    if(audioCC)
    {
        root["mainAudioCC"] = audioCC;
    }
    if(audioOn)
    {
        root["mainAudioOn"] = audioOn;
    }
    if(audioOff)
    {
        root["mainAudioOff"] = audioOff;
    }
    
}

String ButtonModel::getDirectory()
{
    
        char dir[] = "buttons/p";
        char indexName[2];
        sprintf(indexName, "%d", _page);
        strcat(dir, indexName);
        return String(dir);
    
}

void ButtonModel::press(bool down)
{
    if(down){
    state = !state;
    }
    
    sendState();
    
    pressed();
}

void ButtonModel::pressed()
{
    if(state)
    {
        MIDI.sendControlChange(102,127,1);
    }
    else
    {
        MIDI.sendControlChange(102,0,1);
    }
    if(type == 15)
    {
        // Audio loop
        //pinMode(audioId, OUTPUT);
        pbController.xLog("Relay change");
        pbController.xLog(audioId);
        digitalWrite(audioId, state);
    }

}

void ButtonModel::sendState()
{
    DynamicJsonBuffer jsonBuffer;
    
    JsonObject &root = jsonBuffer.createObject();
    
    root["send"] = "buttonState";
    root["pageIndex"] = _page;
    root["buttonIndex"] = _index;
    root["state"] = state;
    
    pbController.sendPBSysex(root);
}

void ButtonModel::saveSpace()
{
    _name = "";
    label = "";
    
    PBModel::saveSpace();
}


