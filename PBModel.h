#ifndef PBModelH
#define PBModelH

class PBModel;

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SD.h>
#include <SPI.h>


class PBModel
{
public:
    PBModel(int index);
    PBModel(int index, PBModel *newParent);
    ~PBModel();
    
    void writeToFile();
    void writeToFile(String filename);
    virtual String getFilename() = 0;
    virtual void writeToJson(JsonObject &root) = 0;
    virtual void updateFromJson(JsonObject &root) = 0;
    void loadFromFile(String filename);
    void loadFromFile();
    void sendViaSysex();
    virtual String getDirectory(){ return ""; };
    void markForSaving();
    void updateFromSysex(JsonObject &root);
    virtual String getSysexId() = 0;
    virtual void saveSpace() {_spaceSaving = true;};
    
    
protected:
    PBModel *_parent;
    int _index;
    bool _spaceSaving = true;
    
    const String _modelName;
    unsigned long _lastSaved = 0;
    unsigned long _lastUpdated = 0;

};





#endif
