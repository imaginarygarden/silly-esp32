#ifndef DISPLAY_DRIVER_H
#define DISPLAY_DRIVER_H

class DisplayDriver final {
    bool m_init{};

   public:
    DisplayDriver();

    void init();
};

#endif