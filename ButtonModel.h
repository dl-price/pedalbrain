#ifndef ButtonModelH
#define ButtonModelH

class ButtonModel;

#include "PBModel.h"
#include <Arduino.h>
#include <ArduinoJson.h>
//#include <IonDB.h>

class ButtonModel : public PBModel {
public:
    ButtonModel(int newPage, int newIndex);
    static ButtonModel *getButtonForIndices(int pageIndex, int index);
    
    void updateFromJson(JsonObject &root) override;
    void writeToJson(JsonObject &root) override;
    String getFilename() override;
    String getDirectory() override;
    String getSysexId() override { return "button";};
    
    void press(bool down = true);
    
private:
    int _page;
    int index;
    String _name = "";
    String label = "";
    int type = 0;
    int ledOn = 0;
    int ledOff = 0;
    int audioId = 0;
    int deviceId = 0;
    int audioCC = 0;
    int audioOn = 0;
    int audioOff = 0;
    
    bool state = false;
    
    void pressed();
    void sendState();
    
    void saveSpace() override;

    void handleJsonNode(JsonObject::iterator it);

    

    

    

};

#endif
