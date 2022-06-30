// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include_next <mcuconf.h>

// see note in config.h; blok requires
// I2C0 to enable I2C driver 1
// set to I2C1 if not using blok
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE
