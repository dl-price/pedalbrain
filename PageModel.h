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
    void writeToJson(JsonObject &root) override;
    String getFilename() override;
    String getDirectory() override { return "pages";};
    static void initAllModels();
    static void sendAllViaSysex();
    String getSysexId() override { return "page";};
    static PageModel *getPage(int i);
    static PageModel *getPageForIndex(int i);
    ButtonModel *getButtonForIndex(int i);
    
private:
    static PageModel *allModels[MAX_PAGES];
    ButtonModel *_buttonModels[MAX_BUTTONS];
    String _name = "";
    const String _modelName = "page";
    int _page;
    
};

#endif
