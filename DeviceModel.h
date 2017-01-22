#ifndef DeviceModelH
#define DeviceModelH

#include "PBController.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include "PBModel.h"

class DeviceModel;

class DeviceModel : public PBModel {
public:
    DeviceModel(int newIndex);
    void updateFromJson(JsonObject &root) override;
    void writeToJson(JsonObject &root) override;
    String getFilename() override;
    String getDirectory() override;
    static void initAllModels();
    
private:
    static DeviceModel *allModels[MAX_DEVICES];



    String _name;
    String _typeId;
    int _channel;
    int _presets;
    int _maxPC;
    bool _sendPC;
    int _index = -1;
    String _type;
    
};

#endif
