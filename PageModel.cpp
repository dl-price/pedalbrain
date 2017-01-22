
#include <Arduino.h>
#include <ArduinoJson.h>
#include "PageModel.h"
#include "PBController.h"
#include <SD.h>
#include <SPI.h>


PageModel::PageModel(int newPage) : PBModel(newPage)
{
    
}

void PageModel::updateFromJson(JsonObject &root)
{
    PageModel *model = pbController.getPage((int)root["page"]);
    
    model->_page = _index + 1;
    model->_name = root["name"].asString();
    
    pbController.pagesChanged = true;
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

void PageModel::writeAllToFile()
{
    for(int i=0; i < sizeof(pbController.pageModels)/sizeof(PageModel*); i++)
    {
        pbController.pageModels[i]->writeToFile();
    }
}

void PageModel::loadAllFromFile()
{
    for (int i=0; i < sizeof(pbController.pageModels)/sizeof(PageModel*); i++)
    {
        pbController.pageModels[i]->loadFromFile();
    }
}

void PageModel::sendAllViaSysex()
{
    for(int i=0; i < sizeof(pbController.pageModels)/sizeof(PageModel*); i++)
    {
        pbController.pageModels[i]->sendViaSysex();
    }
}
