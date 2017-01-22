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
    
private:
    static PageModel *allModels[MAX_PAGES];
    ButtonModel *_buttonModels[MAX_BUTTONS];
    int _page;
    String _name;
    const String _modelName = "page";
    
};

#endif
