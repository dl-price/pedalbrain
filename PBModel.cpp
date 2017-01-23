
#include <Arduino.h>
#include <ArduinoJson.h>
#include "PBController.h"
#include <SD.h>
#include <SPI.h>

PBModel::PBModel(int index)
{
    _index = index;
    //_spaceSaving = true;
}

PBModel::PBModel(int index, PBModel *newParent)
{
    _index = index;
    _parent = newParent;
    //_spaceSaving = true;
}

void PBModel::writeToFile()
{
    writeToFile(getFilename());
}

void PBModel::writeToFile(String filename)
{
    /*if(_spaceSaving)
    {
        Serial.println("Cannot write to file. Object currently in space saving mode");
    }*/
    DynamicJsonBuffer jsonBuffer;
    
    
        const char *dirName = getDirectory().c_str();
        if(!SD.exists(dirName))
        {
            if(!SD.mkdir(dirName))
            {
                Serial.println("Error creating directory:");
                Serial.println(dirName);
                return;
            }
            else
            {
                Serial.println("Created directory:");
                Serial.println(dirName);
            }
        }
    
    SD.remove(filename.c_str());
    File file = SD.open(filename.c_str(), FILE_WRITE);
    JsonObject &root = jsonBuffer.createObject();
    writeToJson(root);
    
    String output;
    root.printTo(output);
    file.write(output.c_str());
    file.close();
    
    _lastSaved = millis();
}

void PBModel::loadFromFile()
{
    loadFromFile(getFilename());
}

void PBModel::loadFromFile(String filename)
{
    DynamicJsonBuffer jsonBuffer;
    
    Serial.println(filename);
    
    if(SD.exists(filename.c_str()))
    {
        
        File file = SD.open(filename.c_str(), FILE_READ);
        char buf[1024];
        file.read(buf, file.size());
        JsonObject &root = jsonBuffer.parseObject(buf);
        
        updateFromJson(root);
    }
}

void PBModel::sendViaSysex()
{
    DynamicJsonBuffer jsonBuffer;
    
    JsonObject &root = jsonBuffer.createObject();
    root["send"] = getSysexId();
    
    JsonObject &model = root.createNestedObject("model");
    writeToJson(model);
    
    pbController.sendPBSysex(root);
}

void PBModel::updateFromSysex(JsonObject &root)
{
    updateFromJson(root["model"]);
    markForSaving();
}

void PBModel::markForSaving()
{
    writeToFile();
}
