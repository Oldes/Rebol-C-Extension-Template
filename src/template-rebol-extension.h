
//
// auto-generated file, do not modify!
//

#include "rebol-extension.h"

#define SERIES_TEXT(s)   ((char*)SERIES_DATA(s))

#define MIN_REBOL_VER 3
#define MIN_REBOL_REV 14
#define MIN_REBOL_UPD 1
#define VERSION(a, b, c) (a << 16) + (b << 8) + c
#define MIN_REBOL_VERSION VERSION(MIN_REBOL_VER, MIN_REBOL_REV, MIN_REBOL_UPD)

typedef struct my_engine {
//	ma_engine engine;
//	ma_device device;
	RXICBI    callback;
} my_engine;

extern REBCNT Handle_TemplateHandle;

extern u32* arg_words;
extern u32* type_words;

enum ext_commands {
	CMD_MINIAUDIO_INIT_WORDS,
	CMD_MINIAUDIO_TEST,
};


int cmd_init_words(RXIFRM *frm, void *ctx);
int cmd_test(RXIFRM *frm, void *ctx);

enum ma_arg_words {W_ARG_0,
	W_ARG_RESOURCES
};
enum ma_type_words {W_TYPE_0
};

typedef int (*MyCommandPointer)(RXIFRM *frm, void *ctx);

#define MINIAUDIO_EXT_INIT_CODE \
	"REBOL [Title: {Rebol Template Extension} Type: module Version: 0.0.1 needs: 3.14.1]\n"\
	"init-words: command [args [block!] type [block!]]\n"\
	"test: command [\"Just an example\"]\n"\
	"init-words [resources][]\n"\
	"protect/hide 'init-words\n"\
	"\n"

#ifdef  USE_TRACES
#include <stdio.h>
#define debug_print(fmt, ...) do { printf(fmt, __VA_ARGS__); } while (0)
#define trace(str) puts(str)
#else
#define debug_print(fmt, ...)
#define trace(str) 
#endif

