// Filename: exp_multipliers.c

#include "cheats.h"
#include "hid.h"

/********************************
 *                              *
 *        EXP Multipliers       *
 *                              *
 ********************************/


// EXP menu entry
void    expMenu(void) {

    new_spoiler("EXP Multiplier");
        new_separator();
        new_entry_managed("EXP x2", increaseEXP1, INCREASEEXP1, TOGGLE);
        new_entry_managed("EXP x10", increaseEXP10, INCREASEEXP10, TOGGLE);
        new_entry_managed("EXP x100", increaseEXP100, INCREASEEXP100, TOGGLE);
        new_line();
    exit_spoiler();
}


// Changes exp to x2
void	increaseEXP1(void) {
	WRITEU32(0x005B9A58, 0xE1D002B2);
	WRITEU32(0x005B9A5C, 0xE92D4002);
	WRITEU32(0x005B9A60, 0xE3A01002);
	WRITEU32(0x005B9A64, 0xE0000190);
	WRITEU32(0x005B9A68, 0xE8BD8002);
	WRITEU32(0x004AB190, 0xEB043A30);
}


// Changes exp to x10
void	increaseEXP10(void) {
	WRITEU32(0x005B9A58, 0xE1D002B2);
	WRITEU32(0x005B9A5C, 0xE92D4002);
	WRITEU32(0x005B9A60, 0xE3A0100A);
	WRITEU32(0x005B9A64, 0xE0000190);
	WRITEU32(0x005B9A68, 0xE8BD8002);
	WRITEU32(0x004AB190, 0xEB043A30);
}


// Changes exp to x100
void	increaseEXP100(void) {
	WRITEU32(0x005B9A58, 0xE1D002B2);
	WRITEU32(0x005B9A5C, 0xE92D4002);
	WRITEU32(0x005B9A60, 0xE3A01064);
	WRITEU32(0x005B9A64, 0xE0000190);
	WRITEU32(0x005B9A68, 0xE8BD8002);
	WRITEU32(0x004AB190, 0xEB043A30);
}
