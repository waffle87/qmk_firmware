BOOTMAGIC_ENABLE = yes
EXTRAKEY_ENABLE = yes
MOUSEKEY_ENABLE = yes
NRKO_ENABLE = yes
COMBO_ENABLE = yes 
LTO_ENABLE = yes
UNICODEMAP_ENABLE = yes
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
RANDICT = no
MAGIC_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no

# User specific files
SRC += waffle.c pru.c

VPATH += keyboards/gboards

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
endif

ifeq ($(strip $(RANDICT)), yes)
	OPT_DEFS += -DRANDICT
endif
