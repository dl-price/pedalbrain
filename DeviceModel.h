#ifndef DeviceModelH
#define DeviceModelH

#include <Arduino.h>
#include <ArduinoJson.h>

class DeviceModel;

class DeviceModel {
public:
    static void updateFromJson(JsonObject &root);
    void writeToFile();
    void loadFromFile(int index);
    static void writeAllToFile();
    static void loadAllFromFile();
    void writeToJson(JsonObject &root);
    static void sendAllViaSysex();
    void sendViaSysex();


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
