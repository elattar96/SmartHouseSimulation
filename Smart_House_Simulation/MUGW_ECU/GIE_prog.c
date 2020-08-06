#include "STD_types.h"
#include "bitwise.h"
#include "GIE_reg.h"
#include "GIE_int.h"
#include "GIE_priv.h"
#include "GIE_config.h"

/* Enable globale interrupt  */
void GIE_voidEnable(void)
{
	SET_BIT(SREG,GIE_u8_BIT_INDIX);
}

void GIE_voidDisable(void)
{
	CLR_BIT(SREG,GIE_u8_BIT_INDIX);
}




