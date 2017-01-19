
#include "DeviceModel.h"
#include "PBController.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>

void DeviceModel::updateFromJson(JsonObject &root)
{
    DeviceModel *model = &pbController.deviceModels[(int)root["index"]];
    
    model->_name = root["name"].asString();
    model->_channel = (int)root["channel"];
    model->_index = (int)root["index"];
    
    pbController.devicesChanged = true;
}

void DeviceModel::writeToFile()
{
    if(_index >= 0)
    {
    if(!SD.exists("Devices"))
    {
        if(!SD.mkdir("Devices"))
        {
            Serial.println("Error creating 'Devices' directory");
            return;
        }
        else
        {
            Serial.println("Created 'Devices' directory");
        }
    }
    
    DynamicJsonBuffer jsonBuffer;
    
    
    char fileName[15] = "Devices/";
        char indexName[2];
        sprintf(indexName, "%d", _index);
    strcat(fileName, indexName);
    strcat(fileName, ".txt");
    
    SD.remove(fileName);
    File file = SD.open(fileName, FILE_WRITE);
    JsonObject &root = jsonBuffer.createObject();
    writeToJson(root);
    String output;
    root.printTo(output);
    file.write(output.c_str());
    file.close();
    }
    
}

void DeviceModel::writeToJson(JsonObject &root)
        {
            root["index"] = _index;
            root["name"] = _name;
            root["channel"] = _channel;
        }

void DeviceModel::writeAllToFile()
{
    for(int i=0; i < sizeof(pbController.deviceModels)/sizeof(DeviceModel); i++)
    {
        pbController.deviceModels[i].writeToFile();
    }
}

void DeviceModel::loadFromFile(int index)
{
    StaticJsonBuffer<300> jsonBuffer;
    
    char fileName[15] = "Devices/";
    char indexName[2];
    sprintf(indexName, "%d", index);
    strcat(fileName, indexName);
    strcat(fileName, ".txt");
    if(SD.exists(fileName))
    {
    
    File file = SD.open(fileName, FILE_READ);
    char buf[300];
    file.read(buf, file.size());
    JsonObject &json = jsonBuffer.parseObject(buf);
    
    _index = index;
    _name = json["name"].asString();
    _channel = (int)json["channel"];
    
    Serial.println(_name);
    }
}

void DeviceModel::loadAllFromFile()
{
    for(int i=0; i < sizeof(pbController.deviceModels)/sizeof(DeviceModel); i++)
    {
        pbController.deviceModels[i].loadFromFile(i);
    }
}

void DeviceModel::sendViaSysex()
{
    StaticJsonBuffer<300> jsonBuffer;
    
    JsonObject &json = jsonBuffer.createObject();
    json["send"] = "device";
    json["index"] = _index;
    json["name"] = _name;
    json["channel"] = _channel;
    
    pbController.sendPBSysex(json);
}

void DeviceModel::sendAllViaSysex()
{
    for(int i=0; i < sizeof(pbController.deviceModels)/sizeof(DeviceModel); i++)
    {
        pbController.deviceModels[i].sendViaSysex();
    }
}
