#pragma once
#include "quantum.h"

#define kxx KC_NO

#define LAYOUT( \
  k00, k01, k02, k03, k04, k05, /* | */ k40, k41, k42, k43, k44, k45, \
  k10, k11, k12, k13, k14, k15, /* | */ k50, k51, k52, k53, k54, k55, \
  k20, k21, k22, k23, k24, k25, /* | */ k60, k61, k62, k63, k64, k65, \
            k32, k33,           /* | */           k72, k73            \
) { \
  { k00, k01, k02, k03, k04, k05 }, \
  { k10, k11, k12, k13, k14, k15 }, \
  { k20, k21, k22, k23, k24, k25 }, \
  { kxx, kxx, k32, k33, kxx, kxx }, \
  { k40, k41, k42, k43, k44, k45 }, \
  { k50, k51, k52, k53, k54, k55 }, \
  { k60, k61, k62, k63, k64, k65 }, \
  { kxx, kxx, k72, k73, kxx, kxx }  \
}
