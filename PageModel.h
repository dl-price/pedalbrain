#ifndef PageModelH
#define PageModelH

class PageModel;

#include "ButtonModel.h"

class PageModel {
public:
    PageModel(){};
    ~PageModel(){};
    
private:
    ButtonModel _buttonModels[MAX_BUTTONS];
    
};

#endif
