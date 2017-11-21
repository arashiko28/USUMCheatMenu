// Filename: misc.c

#include "cheats.h"
#include "hid.h"

/********************************
 *                              *
 *             Misc             *
 *                              *
 ********************************/


// Misc menu entry
void    miscMenu(void) {

    new_spoiler("Misc");
        qrMenu();
        new_entry("Instant Text Speed", instantText);
        new_entry_managed_note("Access PC Anywhere", "Open Options submenu while holding START", pcAnywhere, PCANYWHERE, 0);
        new_entry_managed_note("Rematch Trainers", "Hold L & talk to Trainer", rematchTrainers, REMATCHTRAINERS, 0);
        new_entry_arg_note("Remove Character Outlines", "Open a menu to see change", toggleOutlines, 0, TOGGLEOUTLINES, TOGGLE);
		new_entry_managed("No forced trainer battles", noTrainer, NOTRAINER, 0);
            //new_entry_arg_note("NTR Debug Connection", "Disables NFC in order to allow stable NTR connection", toggleNFC, 0, TOGGLENFC, TOGGLE);
        //new_spoiler("Group 2");
            //new_entry_managed_note("Change Camera Zoom", "START+L = Enable\nSTART+R = Disable", cameraZoom, CAMERAZOOM, 0);
            //new_entry_managed_note("View IV/EV on Status Screen", "Press (START) or (X) respectively on Pokemon staus screen and then change Pokemon", viewIVEV, VIEWIVEV, 0);
        //exit_spoiler();
        new_line();
    exit_spoiler();
}

// Displays IVs or EVs in place of stats on Pokémon Status screen when X or START is held
void    viewIVEV(void) {

    static const u32 offset = 0x08010000;

    static const u32 version_diff[] =
    {
        0x00,
        0xE8,
        0xDE
    };

    if (!checkAddress(offset + 0xEAC))
        return;
    if (READU32(offset + 0xEAC) == 0xEBFFFCE7) {
        if (is_pressed(BUTTON_X)) {
            WRITEU32(offset + 0xE78, 0xE591000C);
            WRITEU32(offset + 0xE7C, 0xEBF77382 - version_diff[gameVer]);
            WRITEU32(offset + 0xEB0, 0xE596000C);
            WRITEU32(offset + 0xEB4, 0xEBF77374 - version_diff[gameVer]);
            WRITEU32(offset + 0xEE0, 0xE596000C);
            WRITEU32(offset + 0xEE4, 0xEBF7740A - version_diff[gameVer]);
            WRITEU32(offset + 0xF10, 0xE596000C);
            WRITEU32(offset + 0xF14, 0xEBF77409 - version_diff[gameVer]);
            WRITEU32(offset + 0xF40, 0xE596000C);
            WRITEU32(offset + 0xF44, 0xEBF77484 - version_diff[gameVer]);
            WRITEU32(offset + 0xF70, 0xE596000C);
            WRITEU32(offset + 0xF74, 0xEBF77483 - version_diff[gameVer]);
            WRITEU32(offset + 0xFA0, 0xE596000C);
            WRITEU32(offset + 0xFA4, 0xEBF773CF - version_diff[gameVer]);
        }
        if (is_pressed(BUTTON_ST)) {
            WRITEU32(offset + 0xE78, 0xE591000C);
            WRITEU32(offset + 0xE7C, 0xEBF773E3 - version_diff[gameVer]);
            WRITEU32(offset + 0xEB0, 0xE596000C);
            WRITEU32(offset + 0xEB4, 0xEBF773D5 - version_diff[gameVer]);
            WRITEU32(offset + 0xEE0, 0xE596000C);
            WRITEU32(offset + 0xEE4, 0xEBF7742D - version_diff[gameVer]);
            WRITEU32(offset + 0xF10, 0xE596000C);
            WRITEU32(offset + 0xF14, 0xEBF7742E - version_diff[gameVer]);
            WRITEU32(offset + 0xF40, 0xE596000C);
            WRITEU32(offset + 0xF44, 0xEBF774B6 - version_diff[gameVer]);
            WRITEU32(offset + 0xF70, 0xE596000C);
            WRITEU32(offset + 0xF74, 0xEBF774B7 - version_diff[gameVer]);
            WRITEU32(offset + 0xFA0, 0xE596000C);
            WRITEU32(offset + 0xFA4, 0xEBF773F0 - version_diff[gameVer]);
        }
    }
}


// Zooms camera out or in with START+L / START+R
void    cameraZoom(void) {

    static const u32 offset[][2] =
    {
        {0x00595824, 0x0803797C},
        {0x00597724, 0x08037B18},
        {0x00597840, 0x08037B18},
    };

    static const u32 data[] =
    {
        0xEBFAEBA8,
        0xEBFAEB01,
        0xEBFAEB48
    };

    static const u8    buffer[] = {
        0x1C, 0x0A, 0x94, 0xED,
        0x03, 0x1A, 0x9F, 0xED,
        0x01, 0x0A, 0x30, 0xEE,
        0x1C, 0x0A, 0x84, 0xED,
        0x04, 0x00, 0x84, 0xE2,
        0x1E, 0xFF, 0x2F, 0xE1
    };
    memcpy((void *)(offset[gameVer][0]), buffer, 0x18);

    if (!checkAddress(offset[gameVer][1]))
        return;
    else {
        if (READU32(offset[gameVer][1]) == 0xE2840004)
            WRITEU32(offset[gameVer][1], data[gameVer]);
        if (is_pressed(BUTTON_L + BUTTON_ST))
            WRITEU32(offset[gameVer][0] + 0x18, 0xC4BB8000);
        if (is_pressed(BUTTON_R + BUTTON_ST))
            WRITEU32(offset[gameVer][0] + 0x18, 0x00000000);
    }
}


// Sets text speed to instant
void	instantText(void) {
	
    WRITEU32(0x003D08FC, 0xE3A05003);
	WRITEU32(0x003D0058, 0xE3A04003);
}


// Access PC from anywhere by opening options menu
void    pcAnywhere(void) {
	
	static const u32 offset = 0x005B9EE0;
	
		WRITEU32(offset, 0xE92D400E);
		WRITEU32(offset + 0x04, 0xE59F1074);
		WRITEU32(offset + 0x08, 0xE5912000);
		WRITEU32(offset + 0x0C, 0xE3A03000);
		WRITEU32(offset + 0x10, 0xE5813000);
		WRITEU32(offset + 0x14, 0xE3A03C13);
		WRITEU32(offset + 0x18, 0xE2833093);
		WRITEU32(offset + 0x1C, 0xE1520003);
		WRITEU32(offset + 0x20, 0x03A04000);
		WRITEU32(offset + 0x24, 0x11A04000);
		WRITEU32(offset + 0x28, 0xE8BD800E);
		WRITEU32(offset + 0x2C, 0xE350000E);
		WRITEU32(offset + 0x30, 0xEAF711CB);
		WRITEU32(offset + 0x34, 0xE92D400F);
		WRITEU32(offset + 0x38, 0xE24DD010);
		WRITEU32(offset + 0x3C, 0xE3A00000);
		WRITEU32(offset + 0x40, 0xE58D0000);
		WRITEU32(offset + 0x44, 0xE58D0004);
		WRITEU32(offset + 0x48, 0xE58D0008);
		WRITEU32(offset + 0x4C, 0xE58D000C);
		WRITEU32(offset + 0x50, 0xE1A03000);
		WRITEU32(offset + 0x54, 0xE1A02000);
		WRITEU32(offset + 0x58, 0xE3A01C13);
		WRITEU32(offset + 0x5C, 0xE2811093);
		WRITEU32(offset + 0x60, 0xE59F0018);
		WRITEU32(offset + 0x64, 0xE5801000);
		WRITEU32(offset + 0x68, 0xE59F0014);
		WRITEU32(offset + 0x6C, 0xE5900000);
		WRITEU32(offset + 0x70, 0xEBF7803B);
		WRITEU32(offset + 0x74, 0xE3A00002);
		WRITEU32(offset + 0x78, 0xE28DD010);
		WRITEU32(offset + 0x7C, 0xE8BD800F);
		WRITEU32(offset + 0x80, 0x00667000);
		WRITEU32(offset + 0x84, 0x006A3984);
		WRITEU32(0x0037CB10, 0xEB08F4FD);
		WRITEU32(0x00389F88, 0xEB08BFD4);
		
		if (is_pressed(BUTTON_ST))
			WRITEU32(0x005B9F10, 0x1AF711CB);
	
}


// Re-battle trainer that have already been fought. Active by holding L and talking to them
void	rematchTrainers(void) {

    WRITEU32(0x004B9354, (is_pressed(BUTTON_L)) ? 0xE3A00000 :  0xE5911004);
    WRITEU32(0x004B9354 + 0x04, (is_pressed(BUTTON_L)) ? 0xE12FFF1E :  0xE5900044);
}


// Toggles model outlines for player and Pokémon off and on
void	toggleOutlines(u32 state) {

    static const u32 offset[] =
    {
        0x0042E2B8
    };

    WRITEU32(offset[gameVer], (state) ? 0xE320F000 : 0xE5802004);
}

// Disables inGame NFC to allow NTR connection outside of Festival Plaza.
void    toggleNFC(u32 state) {

    static const u32 offset[] =
    {
        0x003DFFD0,
        0x003E14C0,
        0x003E14C0
    };

    WRITEU32(offset[gameVer], (state) ? 0xE3A01000 : 0xE3A01001);
}


void noTrainer(void) {
	
	if (!checkAddress(0x08031E98)) {
		return;
	} else {
		
	u32 train = READU32(0x08031E98);
		WRITEU32(0x08031E98, 0xE3A00001);
	}
}
