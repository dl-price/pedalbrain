#include "ButtonModel.h"
#include "PageModel.h"
#include <ArduinoJson.h>
#include <MIDI.h>
//#include <IonDB.h>


ButtonModel::ButtonModel(int newPage, int newIndex)  : PBModel(newIndex), _page(newPage) {

}

ButtonModel *ButtonModel::getButtonForIndices(int pageIndex, int index)
{
    PageModel *pg = PageModel::getPageForIndex(pageIndex);
    
    return pg->getButtonForIndex(index);
    
}

void ButtonModel::updateFromJson(JsonObject &root)
{
    for (JsonObject::iterator it=root.begin(); it!=root.end(); ++it)

    {
        handleJsonNode(it);
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

        root["mainAudioId"] = audioId;
    

        root["mainDeviceId"] = deviceId;
    

        root["mainAudioCC"] = audioCC;
    
 
        root["mainAudioOn"] = audioOn;
    
   
        root["mainAudioOff"] = audioOff;
    
    
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


void ButtonModel::handleJsonNode(JsonObject::iterator it)
{
    String key = it->key;
    
    pbController.xLog(key);
    
    if(key == "pageIndex")
    {
        _page = it->value;
    }
    else if(key == "name")
    {
        _name = it->value.asString();
    }
    else if(key == "label")
    {
        label = it->value.asString();
    }
    else if(key == "type")
    {
        type = it->value;
    }
    else if(key == "ledOn")
    {
        ledOn = it->value;
    }
    else if(key == "ledOff")
    {
        ledOff = it->value;
    }
    else if(key == "mainAudioId")
    {
        audioId = it->value;
    }
    else if(key == "mainDeviceId")
    {
        deviceId = it->value;
    }
    else if(key == "mainAudioCC")
    {
        audioCC = it->value;
    }
    else if(key == "mainAudioOn")
    {
        audioOn = it->value;
    }
    else if(key == "mainAudioOff")
    {
        audioOff = it->value;
    }
}
