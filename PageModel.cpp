
#include <Arduino.h>
#include <ArduinoJson.h>
#include "PageModel.h"
#include "PBController.h"
#include <SD.h>
#include <SPI.h>

PageModel *PageModel::allModels[MAX_PAGES];

PageModel::PageModel(int newPage) : PBModel(newPage)
{
    for(int i = 0; i < MAX_BUTTONS; i++)
    {
        ButtonModel *model2 = new ButtonModel(_index, i);
        _buttonModels[i] = model2;
        model2->loadFromFile();
    }
}

void PageModel::updateFromJson(JsonObject &root)
{
    _page = _index + 1;
    _name = root["name"].asString();
    
}

String PageModel::getFilename()
{
    char fileName[30];
    strcpy(fileName, getDirectory().c_str());
    strcat(fileName, "/");
    char indexName[2];
    sprintf(indexName, "%d", _index+1);
    strcat(fileName, indexName);
    strcat(fileName, ".txt");
    
    return fileName;
}

void PageModel::writeToJson(JsonObject &root)
{
    root["index"] = _index;
    root["page"] = _index+1;
    root["name"] = _name;
    
}

void PageModel::initAllModels()
{
    for (int i=0; i < MAX_PAGES;i++)
    {
        pbController.xLog("Loop");
        PageModel *model = new PageModel(i);
        PageModel::allModels[i] = model;
        model->loadFromFile();
        
    }
}

void PageModel::sendAllViaSysex()
{
    for(int i=0; i < MAX_PAGES; i++)
    {
        allModels[i]->sendViaSysex();
        for(int i2=0; i2 < MAX_BUTTONS; i2++)
        {
            pbController.xLog(String(i2));
            allModels[i]->getButtonForIndex(i2)->sendViaSysex();
        }
    }
}

PageModel *PageModel::getPage(int i)
{
    return allModels[i+1];
}

PageModel *PageModel::getPageForIndex(int i)
{
    return allModels[i];
}

ButtonModel *PageModel::getButtonForIndex(int i)
{
    return _buttonModels[i];
}
