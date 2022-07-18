#pragma once

#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN D3
#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED
#define SERIAL_USART_SPEED 921600
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PAL_MODE 7

#ifdef OLED_ENABLE
#    define LAYER_ANIM
#    define BONGO_CAT
#    define FELIX_DOG
#endif

#ifdef RGB_MATRIX_ENABLE
#    undef RGB_DI_PIN
#    define RGB_DI_PIN B5
#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_EFFECTS
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
#    define WS2812_PWM_DRIVER PWMD3
#    define WS2812_PWM_CHANNEL 3
#    define WS2812_PWM_PAL_MODE 2
#    define WS2812_DMA_STREAM STM32_DMA1_STREAM3
#    define WS2812_DMA_CHANNEL 3
#endif

#ifdef ENCODER_ENABLE
#    define ENCODERS_PAD_A { B2 }
#    define ENCODERS_PAD_B { B6 }
#endif

#ifdef AUDIO_ENABLE
#    define AUDIO_PIN A5
#    define STARTUP_SONG SONG(ODE_TO_JOY)
#    define AUDIO_CLICKY
#endif

#ifdef POINTING_DEVICE_ENABLE
#    define SPLIT_POINTING_ENABLE
#    define POINTING_DEVICE_RIGHT
#endif
