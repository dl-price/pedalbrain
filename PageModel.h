#ifndef PageModelH
#define PageModelH

class PageModel;

#include "PBController.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "ButtonModel.h"


class PageModel {
public:
    PageModel(int newPage) {_page = newPage;};
    ~PageModel(){};
    
    static void updateFromJson(JsonObject &root);
    void writeToFile();
    static void writeAllToFile();
    void writeToJson(JsonObject &root);
    void loadFromFile(int id);
    static void loadAllFromFile();
    void sendViaSysex();
    static void sendAllViaSysex();
    
private:
    ButtonModel _buttonModels[MAX_BUTTONS];
    int _page;
    String _name;
    
};

#endif
