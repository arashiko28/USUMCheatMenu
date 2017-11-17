// Filename: currency_modifiers.c

#include "cheats.h"
#include "hid.h"

/********************************
 *                              *
 *     Currency Modifiers       *
 *                              *
 ********************************/


// Currency menu entry
void    currencyMenu(void) {
    new_spoiler("Currency");
        new_separator();
        new_entry_managed("Poke Dollars          x9999999", maxMoney, MAXMONEY, EXECUTE_ONCE);
        new_entry_managed("Battle Points         x9999", maxBP, MAXBP, EXECUTE_ONCE);
        //new_entry_managed("Festival Coins        xCCCCCCC", maxCoins, MAXCOINS, EXECUTE_ONCE);
        //new_entry_managed("Total Festival Coins  xCCCCCCC", totalCoins, TOTALCOINS, EXECUTE_ONCE);
        //new_entry_managed("Thumbs Up             xCCCCCCC", totalThumbs, TOTALTHUMBS, EXECUTE_ONCE);
        new_line();
    exit_spoiler();
}

// Set Poké Dollars
void	maxMoney(void) {
	u32 offset = READU32(0x0066F3DC);
	u32 offset2 = READU32(0x0000001C + offset);
	u32 offset3 = READU32(0x00000024 + offset2);
	u32 offset4 = READU32(0x00000004 + offset3);
	WRITEU32(0x000038E8 + offset4, 0x0098967F);
}

// Set current Festival Coins to 999,999
void	maxCoins(void) {
		// No current cheat to do this
}



// Set total Thumbs Up for photos
void	totalThumbs(void) {
	// No current cheat to do this
}


// Set Battle Points Max
void	maxBP(void) {
		u32 bp = READU32(0x0066F3DC);
		u32 bp2 = READU32(0x0000001C + bp);
		u32 bp3 = READU32(0x00000024 + bp2);
		u32 bp4 = READU32(0x00000004 + bp3);
        WRITEU16(0x00003A00 + bp4, 0x270F);
}
