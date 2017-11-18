// Filename: illegal_cheats.c

#include "cheats.h"
#include "hid.h"

/********************************
 *                              *
 *        Illegal Cheats        *
 *                              *
 ********************************/

void    illegalMenu(void) {

    //new_entry("Catch Trial Pokemon", catchTrial);
    new_entry("Catch Trainer's Pokemon", catchTrainers);
    new_entry_arg("Pokemon can learn any TM", learnAnyTM, 0, LEARNANYTM, TOGGLE);
    new_entry_arg("Learn all from Move Reminder", relearnAnyMove, 0, RELEARNANYMOVE, TOGGLE);
}

// Catch Pokémon during Trial
void    catchTrial(void) {

    static const u32 offset[][2] =
    {
        {0x080B8440, 0x0807638C},
        {0x080B88FC, 0x08076530},
        {0x080B8914, 0x08076530}
    };

    if (!checkAddress(offset[gameVer][0]))
        return;
    if (READU32(offset[gameVer][0]) == 0xE1A01004) {
        WRITEU32(offset[gameVer][1], 0xE3A00001);
        WRITEU32(offset[gameVer][0], 0xE3A01000);
    }
}


// Catch Trainer's Pokémon
void    catchTrainers(void) {

    static const u32 offset[] =
    {
        0x005B9E60
    };
	
	WRITEU32(offset[gameVer], 0xE1A04000);
    WRITEU32(offset[gameVer] + 0x04, 0xE92D4003);
    WRITEU32(offset[gameVer] + 0x08, 0xE59D0028);
    WRITEU32(offset[gameVer] + 0x0C, 0xE59F1014);
    WRITEU32(offset[gameVer] + 0x10, 0xE1510000);
	WRITEU32(offset[gameVer] + 0x14, 0x05970004);
	WRITEU32(offset[gameVer] + 0x18, 0x0590000C);
	WRITEU32(offset[gameVer] + 0x1C, 0x03A01000);
	WRITEU32(offset[gameVer] + 0x20, 0x05C01000);
	WRITEU32(offset[gameVer] + 0x24, 0xE8BD8003);
	WRITEU32(offset[gameVer] + 0x28, 0x00709E24);
	WRITEU32(0x0045BCB4, 0xEB057869);
}

void    learnAnyTM(u32 state) {

    static const u32 offset[] =
    {
        0x004AB044
    };

    static u32 original;

    if (state) {
        original = READU32(offset[gameVer]);
        WRITEU32(offset[gameVer], 0xE3A00001);
    } else {
        WRITEU32(offset[gameVer], original);
    }
}

void    relearnAnyMove(u32 state) {

    static u32 original[4];

    if (state) {
        original[0] = READU32(0x004C320C);
        original[1] = READU32(0x0044189C);
        original[2] = READU32(0x004418A0);
        original[3] = READU32(0x004418A4);

        WRITEU32(0x004C320C, 0xE2850001);
        WRITEU32(0x0044189C, 0xE3A01C02);
        WRITEU32(0x004418A0, 0xE28110D8);
        WRITEU32(0x004418A4, 0xE5851004);
    } else {
        WRITEU32(0x004C320C, original[0]);
        WRITEU32(0x0044189C, original[1]);
        WRITEU32(0x004418A0, original[2]);
        WRITEU32(0x004418A4, original[3]);
    }
}
