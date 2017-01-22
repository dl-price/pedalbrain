#ifndef PageModelH
#define PageModelH

class PageModel;

#include "PBController.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "PBModel.h"
#include "ButtonModel.h"


class PageModel : public PBModel {
public:
    PageModel(int newPage);
    ~PageModel(){};
    
    void updateFromJson(JsonObject &root) override;
    static void writeAllToFile();
    void writeToJson(JsonObject &root) override;
    static void loadAllFromFile();
    static void sendAllViaSysex();
    String getFilename() override;
    
private:
    ButtonModel _buttonModels[MAX_BUTTONS];
    int _page;
    String _name;
    const String _modelName = "page";
    
};

#endif
