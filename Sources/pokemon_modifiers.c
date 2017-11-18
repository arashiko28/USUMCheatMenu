// Filename: pokemon_modifiers.c

#include "cheats.h"
#include "hid.h"

/********************************
 *                              *
 *       Pokémon Modifiers      *
 *                              *
 ********************************/

// Pokémon menu entry
void    pokemonMenu(void) {

    new_spoiler("Pokemon");
        new_entry("Rename any Pokemon", renamePokemon);
        new_entry_managed_note("Instant Egg from Nursery", "Hold L & talk to Nursery NPC", instantEgg, INSTANTEGG, 0);
        new_entry_arg("Instant Egg Hatching", instantHatch, 0, INSTANTHATCH, TOGGLE);
        new_line();
    exit_spoiler();
}


// Rename any Pokemon at the Name Rater
void	renamePokemon(void) {
    static const u32 offset[] =
    {
        0x004C527C
    };
	WRITEU32(offset[gameVer], 0xE3A00001);
}


// Egg instantly ready when talking to Nursery NPC while holding L | Working!
void	instantEgg(void) {
    static const u32 offset[] =
    {
  		0x0045AAD4
    };
    WRITEU32(offset[gameVer] + 0x00, (is_pressed(BUTTON_L)) ? 0xE3A01001 : 0xE2800E1E);
    WRITEU32(offset[gameVer] + 0x04, (is_pressed(BUTTON_L)) ? 0xE5C011E0 : 0xE1D000D0);
    WRITEU32(offset[gameVer] + 0x08, (is_pressed(BUTTON_L)) ? 0xEA007D37 : 0xE12FFF1E);
}


// Instant egg hatching in one step
void	instantHatch(u32 state) {



    WRITEU32(0x005B9E40, (state) ? 0xE59D000C : 0xE1A00004);
	WRITEU32(0x005B9E44, 0xE59F500C);
	WRITEU32(0x005B9E48, 0xE1500005);
	WRITEU32(0x005B9E4C, 0x03A00000);
	WRITEU32(0x005B9E50, 0x11A00004);
	WRITEU32(0x005B9E54, 0xE12FFF1E);
	WRITEU32(0x005B9E58, 0x007024B4);
	WRITEU32(0x004ADA5C, 0xEB0430F7);


}
