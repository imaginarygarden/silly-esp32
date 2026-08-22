#ifndef BASE_VIEW_H
#define BASE_VIEW_H

#include "lvgl_cpp.h"

class BaseScreen;

class BaseView {
protected:
    BaseScreen &m_screen;

public:
    BaseView(BaseScreen &screen) : m_screen{screen}
    {
    }

    virtual void build() = 0;
    
    virtual void update() {}

    virtual void onExit() {}
};

#endif