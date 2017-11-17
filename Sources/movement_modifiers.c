// Filename: movement_modifiers.c

#include "cheats.h"
#include "hid.h"

/********************************
 *                              *
 *      Movement Modifiers      *
 *                              *
 ********************************/

// Movement menu entry
void    movementMenu(void) {

    new_spoiler("Movement");
        new_entry("Run Faster", runFaster);
        new_entry_managed_note("Walk Through Walls", "Hold R = Enable\nPress R+A to toggle", walkThruWalls, WALKTHROUGHWALLS, 0);
        new_line();
    exit_spoiler();
}


// Increases run speed to 1.375x
void	runFaster(void) {
    static const u32 offset[] =
    {
        0x003A9A60
    };
    WRITEFLOAT(offset[gameVer], (is_pressed(BUTTON_B)) ? 1.375f : 1.0f);
}



// Walk through wall while R is held down or toggle with R+A
void	walkThruWalls(void) {
	static bool permActivation = false;
    static bool btn = false;
    if (is_pressed(BUTTON_R)) {
        WRITEU32(0x003ABDD8, 0xE1A00000);
        WRITEU32(0x003ABF0C, 0xE1A00000);
		if (is_pressed(BUTTON_A) && !btn) {
            permActivation = !permActivation;
            btn = true;
        } else if (!is_pressed(BUTTON_A)) {
            btn = false;
		}
	} else if (permActivation) {
		WRITEU32(0x003ABDD8, 0xE1A00000);
        WRITEU32(0x003ABF0C, 0xE1A00000);
    } else {
        WRITEU32(0x003ABDD8, 0xEB01F79D);
		WRITEU32(0x003ABF0C, 0xEB01F750);
    }
}
