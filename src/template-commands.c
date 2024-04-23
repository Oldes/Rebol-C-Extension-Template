// =============================================================================
// Rebol/Template extension commands
// =============================================================================


#include "template-rebol-extension.h"
#include <stdio.h>
#include <stdlib.h> // malloc
#include <math.h>   // fmin, fmax

#define COMMAND int

#define FRM_IS_HANDLE(n, t)   (RXA_TYPE(frm,n) == RXT_HANDLE && RXA_HANDLE_TYPE(frm, n) == t)
#define ARG_Double(n)         RXA_DEC64(frm,n)
#define ARG_Float(n)          (float)RXA_DEC64(frm,n)
#define ARG_Int32(n)          RXA_INT32(frm,n)
#define ARG_Handle_Series(n)  RXA_HANDLE_CONTEXT(frm, n)->series;

#define RETURN_HANDLE(hob)                   \
	RXA_HANDLE(frm, 1)       = hob;          \
	RXA_HANDLE_TYPE(frm, 1)  = hob->sym;     \
	RXA_HANDLE_FLAGS(frm, 1) = hob->flags;   \
	RXA_TYPE(frm, 1) = RXT_HANDLE;           \
	return RXR_VALUE

#define APPEND_STRING(str, ...) \
	len = snprintf(NULL,0,__VA_ARGS__);\
	if (len > SERIES_REST(str)-SERIES_LEN(str)) {\
		RL_EXPAND_SERIES(str, SERIES_TAIL(str), len);\
		SERIES_TAIL(str) -= len;\
	}\
	len = snprintf( \
		SERIES_TEXT(str)+SERIES_TAIL(str),\
		SERIES_REST(str)-SERIES_TAIL(str),\
		__VA_ARGS__\
	);\
	SERIES_TAIL(str) += len;

#define RETURN_ERROR(err)  do {RXA_SERIES(frm, 1) = err; return RXR_ERROR;} while(0)


int Common_mold(REBHOB *hob, REBSER *str) {
	int len;
	if (!str) return 0;
	SERIES_TAIL(str) = 0;
	APPEND_STRING(str, "0#%lx", (unsigned long)(uintptr_t)hob->data);
	return len;
}


int TemplateHandle_free(void* hndl) {
	RXIARG  arg;
	REBSER *blk;
	REBHOB *hob;

	if (!hndl) return 0;
	hob = (REBHOB *)hndl;

	printf("release engine: %p is referenced: %i\n", hob->data, IS_MARK_HOB(hob) != 0);
	UNMARK_HOB(hob);
	blk = hob->series;
	if (blk) {
		int i = blk->tail;
		while (i-->0) {
			if (RXT_HANDLE == RL_GET_VALUE(blk, i, &arg)) {
				RL_FREE_HANDLE_CONTEXT(arg.handle.ptr);
			}
		}
		RESET_SERIES(blk);
		hob->series = NULL;
	}
//	engine = (my_engine*)hob->data;
//	ma_engine_uninit(&engine->engine);
//	ma_device_uninit(&engine->device);
	return 0;
}
int TemplateHandle_get_path(REBHOB *hob, REBCNT word, REBCNT *type, RXIARG *arg) {
//	ma_engine* engine = (ma_engine*)hob->data;
	word = RL_FIND_WORD(arg_words, word);
	switch (word) {
	case W_ARG_RESOURCES:
		*type = RXT_BLOCK;
		arg->series = hob->series;
		arg->index = 0;
		break;
	default:
		return PE_BAD_SELECT;	
	}
	return PE_USE;
}
int TemplateHandle_set_path(REBHOB *hob, REBCNT word, REBCNT *type, RXIARG *arg) {
//	ma_engine* engine = (ma_engine*)hob->data;
	word = RL_FIND_WORD(arg_words, word);
	switch (word) {
//	case W_ARG_VOLUME:
//		switch (*type) {
//		case RXT_DECIMAL:
//		case RXT_PERCENT:
//			ma_engine_set_volume(engine, arg->dec64);
//			break;
//		case RXT_INTEGER:
//			ma_engine_set_volume(engine, (float)arg->int64);
//			break;
//		default: 
//			return PE_BAD_SET_TYPE;
//		}
//		break;
	default:
		return PE_BAD_SET;	
	}
	return PE_OK;
}


COMMAND cmd_init_words(RXIFRM *frm, void *ctx) {
	arg_words  = RL_MAP_WORDS(RXA_SERIES(frm,1));
	type_words = RL_MAP_WORDS(RXA_SERIES(frm,2));

	// custom initialization may be done here...

	return RXR_TRUE;
}

COMMAND cmd_test(RXIFRM *frm, void *ctx) {

	return RXR_TRUE;
}
