// Filename: qr_codes.c

#include "cheats.h"
#include "hid.h"

/********************************
 *                              *
 *           QR Codes           *
 *                              *
 ********************************/

// QR Codes menu entry
void    qrMenu(void) {

    new_spoiler("QR Codes");
        new_entry("Remove Island Scan Wait", removeIslandScanWait);
        new_entry("QR Scan Point 100", qrScan100);
        new_line();
    exit_spoiler();
}


// Remove 24 hour wait time for island scanning
void	removeIslandScanWait(void) {
    static const u32 offset[] =
    {
		0x0045388C
    };
	WRITEU32(offset[gameVer], 0xE3A00000);
}

// Sets QR Scan points to 100 allowing you to Island Scan
void	qrScan100(void) {
	u32 offset = READU32(0x0066F3DC);
	u32 offset2 = READU32(0x0000001C + offset);
	u32 offset3 = READU32(0x00000024 + offset2);
	u32 offset4 = READU32(0x00000004 + offset3);
	WRITEU8(0x00069A1B + offset4, 0x64);
}
