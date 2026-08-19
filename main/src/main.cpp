#include "display_driver.h"
#include "showcase_screen.h"

extern "C" {
    void app_main(void);
}

void app_main(void)
{
    static DisplayDriver display_driver{};
    display_driver.init();

    // Event handlers capture ShowcaseScreen::this, so the wrapper and its
    // callback storage must remain alive after app_main returns.
    static ShowcaseScreen showcase_screen{};
    showcase_screen.render();
}
