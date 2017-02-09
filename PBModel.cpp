
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
    
    
    char dirName[20];
    strcpy(dirName, getDirectory().c_str());
        if(!SD.exists(dirName))
        {
            if(!SD.mkdir(dirName))
            {
                Serial.println("Error creating directory:");
                pbController.xLog("Error creating directory:");
                Serial.println(dirName);
                pbController.xLog(dirName);
                return;
            }
            else
            {
                Serial.println("Created directory:");
                pbController.xLog("Created directory:");
                Serial.println(dirName);
                pbController.xLog(dirName);
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
    
    //saveSpace();
}

void PBModel::loadFromFile()
{
    loadFromFile(getFilename());
}

void PBModel::loadFromFile(String filename)
{
    DynamicJsonBuffer jsonBuffer;
    
    if(SD.exists(filename.c_str()))
    {
        
        File file = SD.open(filename.c_str(), FILE_READ);
        char buf[1024];
        file.read(buf, file.size());
        JsonObject &root = jsonBuffer.parseObject(buf);
        
        updateFromJson(root);
        _spaceSaving = false;
    }
}

void PBModel::sendViaSysex()
{
    //if(_spaceSaving)
    //{
       // loadFromFile();
    //}
    DynamicJsonBuffer jsonBuffer;
    
    JsonObject &root = jsonBuffer.createObject();
    root["send"] = getSysexId();
    
    JsonObject &model = root.createNestedObject("model");
    writeToJson(model);
    
    pbController.sendPBSysex(root);
    
    //saveSpace();
}

void PBModel::updateFromSysex(JsonObject &root)
{
    //if(_spaceSaving)
    //{
        loadFromFile();
    //}
    updateFromJson(root["model"]);
    markForSaving();
}

void PBModel::markForSaving()
{
    writeToFile();
}

bool PBModel::parameterIsInt(String str)
{
    return false;
}

bool PBModel::parameterIsString(String str)
{
    return false;
}

int *PBModel::getParameterIfInt(String str)
{
    for(int i=0; i < getParameterMap()->size(); i++)
    {
        if(getParameterMap()->get(i) == str)
        {
            return intParameterList.get(i);
        }
    }
    return NULL;
}

String *PBModel::getParameterIfString(String str)
{
    for(int i=0; i < getParameterMap()->size(); i++)
    {
        if(getParameterMap()->get(i) == str)
        {
            return stringParameterList.get(i);
        }
    }
    return NULL;
}

void PBModel::allocateParameterList()
{
    for(int i=0; i< getParameterMap()->size(); i++)
    {
        intParameterList.add(NULL);
        stringParameterList.add(NULL);
    }
}

void PBModel::setParameter(String str, int newInt)
{
    for(int i=0; i < getParameterMap()->size(); i++)
    {
        if(getParameterMap()->get(i) == str)
        {
            delete intParameterList.get(i);
            intParameterList.set(i, new int(newInt));
        }
    }
}

void PBModel::setParameter(String str, String newString)
{
    for(int i=0; i < getParameterMap()->size(); i++)
    {
        if(getParameterMap()->get(i) == str)
        {
            delete stringParameterList.get(i);
            stringParameterList.set(i, new String(newString));
            
        }
    }
    
   
}
