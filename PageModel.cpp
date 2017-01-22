
#include <Arduino.h>
#include <ArduinoJson.h>
#include "PageModel.h"
#include "PBController.h"
#include <SD.h>
#include <SPI.h>

void PageModel::updateFromJson(JsonObject &root)
{
    PageModel *model = pbController.getPage((int)root["page"]);
    
    model->_page = (int)root["page"];
    model->_name = root["name"].asString();
    
    pbController.pagesChanged = true;
}

void PageModel::writeToFile()
{
    if(_page >= 1)
    {
        if(!SD.exists("Pages"))
        {
            if(!SD.mkdir("Pages"))
            {
                Serial.println("Error creating 'Pages' directory");
                return;
            }
            else
            {
                Serial.println("Created 'Pages' directory");
            }
        }
        
        DynamicJsonBuffer jsonBuffer;
        
        
        char fileName[15] = "Pages/";
        char indexName[2];
        sprintf(indexName, "%d", _page);
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

void PageModel::writeToJson(JsonObject &root)
{
    root["page"] = _page;
    root["name"] = _name;
    
}

void PageModel::writeAllToFile()
{
    for(int i=0; i < sizeof(pbController.pageModels)/sizeof(PageModel*); i++)
    {
        pbController.pageModels[i]->writeToFile();
    }
}

void PageModel::loadFromFile(int id)
{
    DynamicJsonBuffer jsonBuffer;
    
    char fileName[15] = "Pages/";
    char indexName[2];
    sprintf(indexName, "%d", id);
    strcat(fileName, indexName);
    strcat(fileName, ".txt");
    if(SD.exists(fileName))
    {
        File file = SD.open(fileName, FILE_READ);
        char buf[300];
        file.read(buf, file.size());
        JsonObject &json = jsonBuffer.parseObject(buf);
        
        _page = id;
        _name = json["name"].asString();
    }
}

void PageModel::loadAllFromFile()
{
    for (int i=0; i < sizeof(pbController.pageModels)/sizeof(PageModel*); i++)
    {
        pbController.pageModels[i]->loadFromFile(i+1);
    }
}

void PageModel::sendViaSysex()
{
    DynamicJsonBuffer jsonBuffer;
    DynamicJsonBuffer jsonBuffer2;
    
    JsonObject &json = jsonBuffer.createObject();
    json["send"] = "page";
    JsonObject &json2 = json.createNestedObject("model");
    json2["page"] = _page;
    json2["name"] = _name;

    
    
    pbController.sendPBSysex(json);
}

void PageModel::sendAllViaSysex()
{
    for(int i=0; i < sizeof(pbController.pageModels)/sizeof(PageModel*); i++)
    {
        pbController.pageModels[i]->sendViaSysex();
    }
}
