#pragma once

#include_next <mcuconf.h>

/*#undef STM32_LSI_ENABLED
#define STM32_LSI_ENABLED TRUE

#undef STM32_LSE_ENABLED
#define STM32_LSE_ENABLED TRUE*/

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE
