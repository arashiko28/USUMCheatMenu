// Filename: battle_modifiers.c

#include "cheats.h"
#include "hid.h"

/********************************
 *                              *
 *      Battle Modifiers        *
 *                              *
 ********************************/

// Battle menu entry
void    battleMenu(void) {

    // Creates spoiler and cheat entries

    new_spoiler("Party");
        new_entry_arg("Stat Stages +6", maxBattleStats, 0, MAXBATTLESTATS, TOGGLE);
        //new_entry_arg("Use Z-Moves w/o Z-Crystal", zMoves, 0, ZMOVES, TOGGLE);
        new_entry_managed("Infinite Z-Moves", infZMoves, INFZMOVES, 0); // working crashes leaving poke refresh
        new_entry_managed("Invincible Party", invincibleParty, INVINCIBLEPARTY, 0); // WORKING
		new_entry_managed("Infinite PP", infinitePP, INFINITEPP, 0);
        new_line();
    exit_spoiler();
    new_spoiler("Opponent");
        new_entry_arg("No Wild Encounters", noEncounters, 0, NOENCOUNTERS, TOGGLE); // works
        new_entry("100% Capture Rate", catch100); //working
        //new_entry_arg_note("View Opponent's Info", "Press START to activate", showOpponentInfo, 0, SHOWOPPONENTINFO, TOGGLE);
        new_entry_managed("1-Hit KO", oneHitKO, ONEHITKO, 0); //WORKING
        new_entry_arg("Shiny Chance 100%", shinyPokemon, 0, SHINYPOKEMON, TOGGLE);
		new_entry_managed("Throw pokeball at trials", pokeTrial, POKETRIAL, 0); // working
		new_entry_managed("Random pokemon encounter", randomPk, RANDOMPK, 0);
        new_line();
    exit_spoiler();
}

// No wild encounters unless START is held
void    noEncounters(u32 state) {
    static const u32 offset[] =
    {
        0x0807E24C
    };
    if (state) {
        if (!checkAddress(offset[gameVer]))
            return;
        else {

            if (READU32(offset[gameVer]) == 0xE3A00064) {
                if (is_pressed(BUTTON_ST)) {
                    WRITEU32(offset[gameVer] - 0x8, 0xE3A09064);
			} else {
                    WRITEU32(offset[gameVer] - 0x8, 0xE3A09000);
			}
            }
        }
    } else {
        WRITEU32(offset[gameVer] - 0x8, 0xE3A09064);
    }
}

// Shows opponent Pokémon's info during battle on bottom screen when icon is tapped
void    showOpponentInfoOld(void) {
    if (battleInfo && !getWifiStatus) {
        static const u32 offset[] =
        {
            0x080AE178,
            0x080AE5F8,
            0x080AE610
        };
        if (checkAddress(offset[gameVer])) {
            if (READU32(offset[gameVer]) == 0xE92D40F8)
                WRITEU32(offset[gameVer], 0xEAFFFEE7);
        }
    }
}

// Shows opponent Pokémon's info during battle on top screen when X is held
void    showOpponentInfo(u32 state) {

    if (state)
        battleInfo = true;
    else
        battleInfo = false;
}



// Sets all in-battle stats to +6 ranks
void    maxBattleStats(u32 state) {
	
	static const u32 offset[] =
    {
        0x005B9D60
    };
	WRITEU32(offset[gameVer], 0xE92D401F);
	WRITEU32(offset[gameVer] + 0x04, 0xE59F0018);
	WRITEU32(offset[gameVer] + 0x08, 0xE150000E);
	WRITEU32(offset[gameVer] + 0x0C, 0x18BD801F);
	WRITEU32(offset[gameVer] + 0x10, 0xE59F0010);
	WRITEU32(offset[gameVer] + 0x14, 0xFA000005);
	WRITEU32(offset[gameVer] + 0x18, 0xE59F000C);
	WRITEU32(offset[gameVer] + 0x1C, 0xFA000003);
	WRITEU32(offset[gameVer] + 0x20, 0xE8BD801F);
	WRITEU32(offset[gameVer] + 0x24, 0x0071A77C);
	WRITEU32(offset[gameVer] + 0x28, 0x30000404);
	WRITEU32(offset[gameVer] + 0x2C, 0x300073EC);
	WRITEU32(offset[gameVer] + 0x30, 0x220CB50F);
	WRITEU32(offset[gameVer] + 0x34, 0x33181C03);
	WRITEU32(offset[gameVer] + 0x38, 0x29006801);
	WRITEU32(offset[gameVer] + 0x3C, 0x31F5D008);
	WRITEU32(offset[gameVer] + 0x40, 0x700A31F5);
	WRITEU32(offset[gameVer] + 0x44, 0x708A704A);
	WRITEU32(offset[gameVer] + 0x48, 0x710A70CA);
	WRITEU32(offset[gameVer] + 0x4C, 0x718A714A);
	WRITEU32(offset[gameVer] + 0x50, 0x42833004);
	WRITEU32(offset[gameVer] + 0x54, 0xBD0FD1F0);
	WRITEU32(0x0029B74C, 0xEA0C7983);
}


// 100% Catch rate for Pokemon
void    catch100(void) {
	WRITEU32(0x005B9EA0, 0xE5D00008);
	WRITEU32(0x005B9EA4, 0xE92D4003);
	WRITEU32(0x005B9EA8, 0xE59D0010);
	WRITEU32(0x005B9EAC, 0xE59F100C);
	WRITEU32(0x005B9EB0, 0xE1510000);
	WRITEU32(0x005B9EB4, 0x024000F8);
	WRITEU32(0x005B9EB8, 0x058D0010);
	WRITEU32(0x005B9EBC, 0xE8BD8003);
	WRITEU32(0x005B9EC0, 0x0070A824);
	WRITEU32(0x004AB184, 0xEB043B45);
}



// Make wild Pokemon shiny
void	shinyPokemon(u32 state) {
	WRITEU32(0x005B9FF0, 0xE5C40004);
	WRITEU32(0x005B9FF4, 0xEA000000);
	WRITEU32(0x005B9FF8, 0xE5C41006);
	WRITEU32(0x005B9FFC, 0xE12FFF1E);
	WRITEU32(0x003A7284, 0xEB084B59);
    static const u32 offset[] =
    {
        0x005B9FF4
    };
    WRITEU32(offset[gameVer], (state) ? 0xE3A01001 : 0xEA000000);
}


// Use Z-Moves without the need of a Z-Crystal
void    zMoves(u32 state) {
    static const u32 offset[][3] =
    {
        {0x00595900, 0x00313DC0, 0x0036D0EC},
        {0x00597800, 0x00314300, 0x0036DFF4},
        {0x00597800, 0x00314300, 0x0036DFF4}
    };
    static const u32 data[][3] =
    {
        {0x0078BA28, 0xEB0A06CE, 0xEB0A06B5},
        {0x0078BF60, 0xEB0A0D3E, 0xEB0A0D25},
        {0x0078BF60, 0xEB0A0D3E, 0xEB0A0D25}
    };
    if (state) {
        static const u8    buffer[] =
        {
            0x05, 0x40, 0x2D, 0xE9, 0x06, 0x00, 0xA0, 0xE1,
            0x00, 0x00, 0x00, 0xEA, 0x05, 0x40, 0x2D, 0xE9,
            0x50, 0x20, 0x9D, 0xE5, 0x0C, 0x10, 0x9F, 0xE5,
            0x02, 0x00, 0x51, 0xE1, 0xB4, 0x10, 0xD5, 0x01,
            0x00, 0x10, 0xA0, 0x11, 0x05, 0x80, 0xBD, 0xE8
        };

        memcpy((void *)(offset[gameVer][0]), buffer, 0x28);
        WRITEU32(offset[gameVer][0] + 0x28, data[gameVer][0]);
        WRITEU32(offset[gameVer][1] + 0x00, data[gameVer][1]);
        WRITEU32(offset[gameVer][1] + 0x70, data[gameVer][2]);
        WRITEU32(offset[gameVer][2], 0xE3A00001);

    } else {
        WRITEU32(offset[gameVer][1] + 0x00, 0xE1D510B4);
        WRITEU32(offset[gameVer][1] + 0x70, 0xE1D510B4);
        WRITEU32(offset[gameVer][2], 0xE3A00000);
    }
}


// Inifinite Z-Moves
void    infZMoves(void) {
    static const u32 offset = 0x08031E74;

    if (!checkAddress(offset))
        return;
    else {
		u32 zmov = READU32(offset);
		u32 zmov2 = READU32(offset + 0x04);
		u32 zmov3 = READU32(offset + 0x08);
        if (READU32(0x30000158) == 0x40001 && READU32(0x30000180) == 3) {
			WRITEU32(offset, 0xE3A00000);
            WRITEU32(offset + 0x04, 0xE5C30005);
            WRITEU32(offset + 0x08, 0xE1500000);
        } else {
			// WRITEU32(offset, zmov);
			// WRITEU32(offset + 0x04, zmov2);
			// WRITEU32(offset + 0x08, zmov3);
		}
    }
}

// 1-Hit KO
void    oneHitKO(void) {
    static const u32 offset[3] =
    {
        0x30004DB6,  // Max HP
        0x30004DB8,  // Displayed HP
        0x3000BDA0   // Actual HP
    };

    if (isInBattle()) {
        for (int i = 0; i < 6; i++) {
            // If Actual HP is above 1, set it to 1
            if (READU16(offset[2] + (i * 0x330)) > 1) {
                WRITEU16(offset[1] + (i * 0x330), READU16(offset[0] + (i * 0x330)));
                WRITEU16(offset[2] + (i * 0x330), 1);

            // If actual HP is 0, make displayed HP match
            } else if (READU16(offset[2] + (i * 0x330)) == 0)
                WRITEU16(offset[1] + (i * 0x330), 0);
        }
    }
}

// Invincible Party
void    invincibleParty(void) {
    static const u32 offset[3] =
    {
        0x30002776,  // Max HP
        0x30002778,  // Displayed HP
        0x30009760   // Actual HP
    };
    if (isInBattle()) {
        for (int i = 0; i < 6; i++) {
            if (READU16(offset[2] + (i * 0x330)) > 0) {
                // If Actual HP is less than 65535 then set it to 65535
                if (READU16(offset[2] + (i * 0x330)) < 0xFFFF)
                    WRITEU16(offset[2] + (i * 0x330), 0xFFFF);
                // If Display HP is less than max then set it to max
                if (READU16(offset[1] + (i * 0x330)) < READU16(offset[0] + (i * 0x330)))
                    WRITEU16(offset[1] + (i * 0x330), READU16(offset[0] + (i * 0x330)));
            }
        }
    }
}

void infinitePP(void) {

    static const u32 offset[] =
    {
        0x08105FD4
    };

	if (!checkAddress(offset[gameVer])) {
		return;
	} else {
		if (READU32(0x30000158) == 0x40001 && READU32(0x30000180) == 3) {
		WRITEU32(offset[gameVer], 0xE1A04000);
		WRITEU32(offset[gameVer] + 0x04, 0xE92D4007);
		WRITEU32(offset[gameVer] + 0x08, 0xE59F0018);
		WRITEU32(offset[gameVer] + 0x0C, 0xE2801018);
		WRITEU32(offset[gameVer] + 0x10, 0xE4902004);
		WRITEU32(offset[gameVer] + 0x14, 0xE1560002);
		WRITEU32(offset[gameVer] + 0x18, 0x03A04000);
		WRITEU32(offset[gameVer] + 0x1C, 0xE1510000);
		WRITEU32(offset[gameVer] + 0x20, 0x1AFFFFFA);
		WRITEU32(offset[gameVer] + 0x24, 0xE8BD8007);
		WRITEU32(offset[gameVer] + 0x28, 0x300073EC);
		WRITEU32(0x0808F868, 0xEB01D9D9);
		}
	}
}

// Throw pokeball at trial
void pokeTrial(void) {
	if (!checkAddress(0x08077B8C)) {
		return;
	} else {
		if (READU32(0x30000158) == 0x40001 && READU32(0x30000180) == 3) {
		WRITEU32(0x08077B8C, 0xE3A00001);
		WRITEU32(0x080BC3D4, 0xE3A01000);
		}
	}
}


// Random pokemon encounter
void randomPk(void) {
	
	WRITEU32(0x005B9FC0, 0xE92D400E);
	WRITEU32(0x005B9FC4, 0xE3A0001E);
	WRITEU32(0x005B9FC8, 0xE5C40004);
	WRITEU32(0x005B9FCC, 0xE59F0008);
	WRITEU32(0x005B9FD0, 0xEBF907E4);
	WRITEU32(0x005B9FD4, 0xE2800001);
	WRITEU32(0x005B9FD8, 0xE8BD800E);
	WRITEU32(0x005B9FDC, 0x00000327);
	WRITEU32(0x003A7298, 0xEB084B48);
	WRITEU32(0x003A72A8, 0xE1D400B0);
	WRITEU32(0x003A72C4, 0xE1D400B0);
	
}
