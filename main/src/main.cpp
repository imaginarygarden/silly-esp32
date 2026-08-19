#include <iostream>
#include "test.h"

extern "C" {
    void app_main(void);
}

void app_main(void)
{
    std::cout << simple_variable << std::endl;
}
