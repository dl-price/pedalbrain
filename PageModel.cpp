
#include <Arduino.h>
#include <ArduinoJson.h>
#include "PageModel.h"
#include "PBController.h"
#include <SD.h>
#include <SPI.h>

PageModel *PageModel::allModels[MAX_PAGES];

PageModel::PageModel(int newPage) : PBModel(newPage)
{
    
}

void PageModel::updateFromJson(JsonObject &root)
{
    _page = _index + 1;
    _name = root["name"].asString();
    
}

String PageModel::getFilename()
{
    char fileName[15] = "Pages/";
    char indexName[2];
    sprintf(indexName, "%d", _index+1);
    strcat(fileName, indexName);
    strcat(fileName, ".txt");
    
    return fileName;
}

void PageModel::writeToJson(JsonObject &root)
{
    root["page"] = _index+1;
    root["name"] = _name;
    
}

void PageModel::initAllModels()
{
    for (int i=0; i< MAX_PAGES;i++)
    {
        PageModel *model = new PageModel(i);
        PageModel::allModels[i] = model;
        model->loadFromFile();
    }
}
