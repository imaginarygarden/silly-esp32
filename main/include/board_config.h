#pragma once

#define BOARD_LCD_H_RES                 240
#define BOARD_LCD_V_RES                 320

#define BOARD_LCD_SPI_HOST              SPI3_HOST
#define BOARD_LCD_PIN_SCLK              GPIO_NUM_12
#define BOARD_LCD_PIN_MOSI              GPIO_NUM_11
#define BOARD_LCD_PIN_MISO              GPIO_NUM_13
#define BOARD_LCD_PIN_CS                GPIO_NUM_10
#define BOARD_LCD_PIN_DC                GPIO_NUM_46

/* The supplied board ties LCD reset to ESP32-S3 EN, not to a GPIO. */
#define BOARD_LCD_PIN_RESET             GPIO_NUM_NC
#define BOARD_LCD_PIN_BACKLIGHT         GPIO_NUM_45
#define BOARD_LCD_BACKLIGHT_ON_LEVEL    1

#define BOARD_LCD_PIXEL_CLOCK_HZ        (40 * 1000 * 1000)

/* Native ES3C28P portrait orientation used by the board BSP. */
#define BOARD_LCD_SWAP_XY               false
#define BOARD_LCD_MIRROR_X              true
#define BOARD_LCD_MIRROR_Y              false
#define BOARD_LCD_COLOR_ORDER           LCD_RGB_ELEMENT_ORDER_BGR
#define BOARD_LCD_INVERT_COLORS         true

#define BOARD_LVGL_BUFFER_LINES         40

/* Reserved for a future touch driver; its controller model is still needed. */
#define BOARD_TOUCH_PIN_SDA             GPIO_NUM_16
#define BOARD_TOUCH_PIN_SCL             GPIO_NUM_15
#define BOARD_TOUCH_PIN_RESET           GPIO_NUM_18
#define BOARD_TOUCH_PIN_INTERRUPT       GPIO_NUM_17
#define BOARD_TOUCH_I2C_ADDRESS         0x38
