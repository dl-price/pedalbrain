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
    static void sendAllViaSysex();
    String getSysexId() override { return "device";};
    
private:
    static DeviceModel *allModels[MAX_DEVICES];


    const String _modelName = "device";
    String _name = "";
    String _typeId;
    int _channel = 1;
    int _presets = 0;
    int _maxPC = 0;
    bool _sendPC = false;
    int _index = -1;
    String _type;
    
};

#endif
