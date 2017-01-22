
#include "DeviceModel.h"
#include "PBController.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>

DeviceModel *DeviceModel::allModels[MAX_DEVICES];

DeviceModel::DeviceModel(int index) : PBModel(index)
{
    _index = index;
}

String DeviceModel::getDirectory()
{
    return "devices";
}

String DeviceModel::getFilename()
{
    char *fileName;
    fileName = (char*)getDirectory().c_str();
    char indexName[2];
    sprintf(indexName, "%d", _index);
    strcat(fileName, indexName);
    strcat(fileName, ".txt");
    return fileName;
}

void DeviceModel::updateFromJson(JsonObject &root)
{
    _name = root["name"].asString();
    _channel = (int)root["channel"];
    if(root.containsKey("type"))
    {
    _type = root["type"].asString();
    }
    else
    {
        _type = "";
    }
}

void DeviceModel::writeToJson(JsonObject &root)
        {
            root["index"] = _index;
            root["name"] = _name;
            root["channel"] = _channel;
            root["type"] = _type;
            
        }

void DeviceModel::initAllModels()
{
    for (int i=0; i< MAX_DEVICES;i++)
    {
        DeviceModel *model = new DeviceModel(i);
        DeviceModel::allModels[i] = model;
        model->loadFromFile();
    }
}
