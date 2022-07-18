BOOTMAGIC_ENABLE = yes
EXTRAKEY_ENABLE = yes
NRKO_ENABLE = yes
COMBO_ENABLE = yes 
CAPS_WORD_ENABLE = yes
TOP_SYMBOLS = yes
TAP_DANCE_ENABLE = yes
UNICODE_COMMON = yes
MOUSEKEY_ENABLE = no
MAGIC_ENABLE = no
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
DEBOUNCE_TYPE = asym_eager_defer_pk

SRC += waffle.c pru.c

ifeq ($(strip $(OLED_ENABLE)), yes)
	SRC += oled.c
	WPM_ENABLE = yes
endif

ifeq ($(PLATFORM),CHIBIOS)
	LTO_ENABLE = no
	RANDICT = yes
	EXTRAFLAGS = -O3
else
	LTO_ENABLE = yes
endif

ifeq ($(strip $(UNICODE_COMMON)), yes)
	SRC += unicode.c
endif

ifeq ($(strip $(RANDICT)), yes)
	OPT_DEFS += -DRANDICT
endif
