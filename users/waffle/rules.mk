BOOTMAGIC_ENABLE = yes
EXTRAKEY_ENABLE = yes
NRKO_ENABLE = yes
COMBO_ENABLE = yes 
UNICODEMAP_ENABLE = yes
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
MAGIC_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no

# User specific files
SRC += waffle.c pru.c

VPATH += keyboards/gboards

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
	WPM_ENABLE = yes
endif

ifeq ($(PLATFORM),CHIBIOS)
	LTO_ENABLE = no
	RANDICT = yes
	CFLAGS = -O3
else
	LTO_ENABLE = yes
endif

ifeq ($(strip $(RANDICT)), yes)
	OPT_DEFS += -DRANDICT
endif
