#ifndef VIEW_H
#define VIEW_H

#include "lvgl_cpp.h"

class ViewHost;

class View {
protected:
    ViewHost &m_screen;

public:
    View(ViewHost &screen) : m_screen{screen}
    {
    }

    virtual ~View() = default;

    virtual void build() = 0;
    
    virtual void update() {}

    virtual void onExit() {}
};

#endif