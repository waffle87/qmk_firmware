### RP2040 Kyria rev2
![photo](https://i.imgur.com/P0urp7n.jpeg)

#### parts & notes
* microcontrollers: [boardsource blok](https://boardsource.xyz/store/628b95b494dfa308a6581622)

blok uses GPIO16/17 for "standard" I2C pins, differing from what's found in [`/platforms/chibios/boards/GENERIC_PROMICRO_RP2040/configs/config.h`](https://github.com/qmk/qmk_firmware/blob/develop/platforms/chibios/boards/GENERIC_PROMICRO_RP2040/configs/config.h#L6-#L20).
this means the following changes are required if using blok:
`config.h`
```c
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP16
#define I2C1_SCL_PIN GP17
```
`mcuconf.h`
```c
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE
```
if not using blok, add `BOARD = GENERIC_PROMICRO_RP2040` to `rules.mk`.

* [35mm cirque trackpad](https://www.mouser.com/ProductDetail/Cirque/TM035035-2024-003?qs=sGAEpiMZZMu3sxpa5v1qrmePy6bg6o9msS9wwvLw9t0%3D) and [holder](https://www.thingiverse.com/thing:5385829)

to use I2C, R1 resistor must be removed.
luckily, the I2C pins are broken out, as i didn't bother using the FPC connector on the trackpad.
from there, wired trackpad directly to oled header pins on pcb. looks a bit iffy...
![trackpad wiring](https://i.imgur.com/tvLVEe0.jpeg)

* [pucks](https://splitkb.com/collections/keyboard-parts/products/tenting-puck) and [tripods](https://www.amazon.com/Manfrotto-MP3-BK-Large-Pocket-Support/dp/B00HCAB8MU) for tenting-puck

i spent quite some time trying to find ideal tripods for tenting, that weren't too costly.
some decent looking options were [joby micro stand](https://www.amazon.com/gp/product/B01MTXTTEB) or [tripod](https://www.amazon.com/gp/product/B07PGDDY8J) w/ [ball head mount](https://www.amazon.com/gp/product/B06XKW7V14).
ultimately ended up going with the manfrotto pocket tripod linked above, which seems to be the best choice for keyboard tenting.
