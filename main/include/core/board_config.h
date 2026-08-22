#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

/* LCD geometry and orientation (rotation is clockwise from native portrait). */
#define BOARD_LCD_NATIVE_H_RES               240
#define BOARD_LCD_NATIVE_V_RES               320
#define BOARD_LCD_ROTATION                   LV_DISPLAY_ROTATION_90
#define BOARD_LCD_NATIVE_SWAP_XY             false
#define BOARD_LCD_NATIVE_MIRROR_X            true
#define BOARD_LCD_NATIVE_MIRROR_Y            false

/* LCD SPI bus and panel. */
#define BOARD_LCD_SPI_HOST                   SPI3_HOST
#define BOARD_LCD_SPI_DMA_CHANNEL            SPI_DMA_CH_AUTO
#define BOARD_LCD_PIN_SCLK                   GPIO_NUM_12
#define BOARD_LCD_PIN_MOSI                   GPIO_NUM_11
#define BOARD_LCD_PIN_MISO                   GPIO_NUM_13
#define BOARD_LCD_PIN_CS                     GPIO_NUM_10
#define BOARD_LCD_PIN_DC                     GPIO_NUM_46
#define BOARD_LCD_PIN_RESET                  GPIO_NUM_NC
#define BOARD_LCD_PIXEL_CLOCK_HZ             (40 * 1000 * 1000)
#define BOARD_LCD_SPI_MODE                   0
#define BOARD_LCD_TRANSACTION_QUEUE_DEPTH    10
#define BOARD_LCD_COMMAND_BITS               8
#define BOARD_LCD_PARAMETER_BITS             8
#define BOARD_LCD_BITS_PER_PIXEL             16
#define BOARD_LCD_COLOR_ORDER                LCD_RGB_ELEMENT_ORDER_BGR
#define BOARD_LCD_INVERT_COLORS              true

/* Backlight. */
#define BOARD_LCD_PIN_BACKLIGHT              GPIO_NUM_45
#define BOARD_LCD_BACKLIGHT_ON_LEVEL         1

/* LVGL task and display buffers. */
#define BOARD_LVGL_TASK_PRIORITY             4
#define BOARD_LVGL_TASK_STACK_SIZE           7168
#define BOARD_LVGL_TASK_AFFINITY             (-1)
#define BOARD_LVGL_TASK_MAX_SLEEP_MS         500
#define BOARD_LVGL_TASK_STACK_CAPS           (MALLOC_CAP_INTERNAL | MALLOC_CAP_DEFAULT)
#define BOARD_LVGL_TIMER_PERIOD_MS            5
#define BOARD_LVGL_BUFFER_LINES              40
#define BOARD_LVGL_DOUBLE_BUFFER             true
#define BOARD_LVGL_BUFFER_DMA                true
#define BOARD_LVGL_BUFFER_SPIRAM             false
#define BOARD_LVGL_SOFTWARE_ROTATION         false
#define BOARD_LVGL_SWAP_RGB565_BYTES         true
#define BOARD_LVGL_FULL_REFRESH              false
#define BOARD_LVGL_DIRECT_MODE               false

/* FT6336G touch controller (FT5x06-compatible protocol). */
#define BOARD_TOUCH_I2C_PORT                  I2C_NUM_0
#define BOARD_TOUCH_I2C_CLOCK_HZ              (400 * 1000)
#define BOARD_TOUCH_I2C_GLITCH_FILTER_COUNT   7
#define BOARD_TOUCH_I2C_INTERNAL_PULLUPS      true
#define BOARD_TOUCH_I2C_ADDRESS               0x38
#define BOARD_TOUCH_I2C_CONTROL_PHASE_BYTES   1
#define BOARD_TOUCH_I2C_DC_BIT_OFFSET         0
#define BOARD_TOUCH_I2C_COMMAND_BITS          8
#define BOARD_TOUCH_I2C_DISABLE_CONTROL_PHASE true
#define BOARD_TOUCH_PIN_SDA                   GPIO_NUM_16
#define BOARD_TOUCH_PIN_SCL                   GPIO_NUM_15
#define BOARD_TOUCH_PIN_RESET                 GPIO_NUM_18
#define BOARD_TOUCH_PIN_INTERRUPT             GPIO_NUM_17
#define BOARD_TOUCH_RESET_LEVEL               0
#define BOARD_TOUCH_INTERRUPT_LEVEL           0
#define BOARD_TOUCH_NATIVE_SWAP_XY            false
#define BOARD_TOUCH_NATIVE_MIRROR_X           false
#define BOARD_TOUCH_NATIVE_MIRROR_Y           false

#endif
