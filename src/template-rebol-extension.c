// =============================================================================
// Rebol/Template extension
// =============================================================================

#include "template-rebol-extension.h"

RL_LIB *RL; // Link back to reb-lib from embedded extensions

//==== Globals ===============================================================//
extern MyCommandPointer Command[];
REBCNT Handle_TemplateHandle;

u32* arg_words;
u32* type_words;
//============================================================================//

static const char* init_block = MINIAUDIO_EXT_INIT_CODE;

int Common_mold(REBHOB *hob, REBSER *ser);

int TemplateHandle_free(void* hndl);
int TemplateHandle_get_path(REBHOB *hob, REBCNT word, REBCNT *type, RXIARG *arg);
int TemplateHandle_set_path(REBHOB *hob, REBCNT word, REBCNT *type, RXIARG *arg);

RXIEXT const char *RX_Init(int opts, RL_LIB *lib) {
	RL = lib;
	REBYTE ver[8];
	RL_VERSION(ver);
	debug_print(
		"RXinit template-extension; Rebol v%i.%i.%i\n",
		ver[1], ver[2], ver[3]);

	if (MIN_REBOL_VERSION > VERSION(ver[1], ver[2], ver[3])) {
		debug_print(
			"Needs at least Rebol v%i.%i.%i!\n",
			 MIN_REBOL_VER, MIN_REBOL_REV, MIN_REBOL_UPD);
		return 0;
	}
	if (!CHECK_STRUCT_ALIGN) {
		trace("CHECK_STRUCT_ALIGN failed!");
		return 0;
	}

	REBHSP spec;
	spec.mold = Common_mold;

	spec.size      = sizeof(my_engine); // It is MY_, not MA_! 
	spec.flags     = HANDLE_REQUIRES_HOB_ON_FREE;
	spec.free      = TemplateHandle_free;
	spec.get_path  = TemplateHandle_get_path;
	spec.set_path  = TemplateHandle_set_path;
	Handle_TemplateHandle = RL_REGISTER_HANDLE_SPEC((REBYTE*)"template-handle", &spec);

	return init_block;
}

RXIEXT int RX_Call(int cmd, RXIFRM *frm, void *ctx) {
	return Command[cmd](frm, ctx);
}
