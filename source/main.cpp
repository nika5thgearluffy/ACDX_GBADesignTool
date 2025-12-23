#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <gba_console.h>

//#include <BoyScout.h>

#include "globals.h"

//#include "music_bgf.h"
//#define TUNE music_bgf

int main(void)
{
	/*
        The vblank interrupt must be enabled for VBlankIntrWait() to work.

        Since the default dispatcher handles the bios flags, no vblank handler
        is required.
	*/ 

	irqInit();
	irqEnable(IRQ_VBLANK);

    /*
    // Start up the song!
    unsigned int nBSSongSize;

	// Initialize BoyScout
	BoyScoutInitialize();

	// Get needed song memory
	nBSSongSize = BoyScoutGetNeededSongMemory(TUNE);

	// Allocate and set BoyScout memory area
	BoyScoutSetMemoryArea((unsigned int)malloc(nBSSongSize));

	// Open song
	BoyScoutOpenSong(TUNE);

	// Play song and loop
	BoyScoutPlaySong(1);
    */

    // Allow Interrupts
	REG_IME = 1;

    consoleDemoInit();
    iprintf("Press a button now.\n");

	while (1)
    {
        // Scan inputs from the console
        scanKeys();

        // DEBUG: Left Pressing
        if (DesignTool_Inputs_Pressed(KEY_LEFT))
        {
            DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Selected - 1;
            if (DesignTool_Menu_Pattern_Selected < 1)
            {
                DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Max;
            }
            iprintf("Left pressed:\n");
            iprintf(std::string(std::to_string(DesignTool_Menu_Pattern_Selected) + "\n").c_str());
        }

        // DEBUG: Right Pressing
        if (DesignTool_Inputs_Pressed(KEY_RIGHT))
        {
            DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Selected + 1;
            if (DesignTool_Menu_Pattern_Selected > DesignTool_Menu_Pattern_Max)
            {
                DesignTool_Menu_Pattern_Selected = 1;
            }
            iprintf("Right pressed:\n");
            iprintf(std::string(std::to_string(DesignTool_Menu_Pattern_Selected) + "\n").c_str());
        }

		VBlankIntrWait();
	}
}


