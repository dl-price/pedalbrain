#ifndef ButtonModelH
#define ButtonModelH

class ButtonModel;

#include "PBModel.h"
#include <Arduino.h>
#include <ArduinoJson.h>

class ButtonModel : public PBModel {
public:
    ButtonModel(int newPage, int newIndex) : PBModel(newIndex), _page(newPage){};
    static ButtonModel *getButtonForIndices(int pageIndex, int index);
    
    void updateFromJson(JsonObject &root) override;
    void writeToJson(JsonObject &root) override;
    String getFilename() override;
    String getDirectory() override;
    String getSysexId() override { return "button";};
    
private:
    int _page;
    int index;
    String _name = "";
    String label = "";
    int type = 0;
    int ledOn = 0;
    int ledOff = 0;
};

#endif
