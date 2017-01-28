#include "ButtonModel.h"
#include "PageModel.h"
#include <ArduinoJson.h>

ButtonModel *ButtonModel::getButtonForIndices(int pageIndex, int index)
{
    PageModel *pg = PageModel::getPageForIndex(pageIndex);
    
    return pg->getButtonForIndex(index);
    
}

void ButtonModel::updateFromJson(JsonObject &root)
{
    pbController.xLog("Got button");
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
    
}

String ButtonModel::getDirectory()
{
    
        char dir[] = "buttons/p";
        char indexName[2];
        sprintf(indexName, "%d", _page);
        strcat(dir, indexName);
        return String(dir);
    
}
