#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_blending.h"

#include "gameCubeLink.h"
#include "patternMenu.h"
#include "globals.h"

int main(void)
{
    // Start butano!
    bn::core::init();

    // Start the GameCube link connection
    gameCubeLink_start();

	while(true)
    {
        // Update the link status
        gameCubeLink_update();

        if (DesignTool_Menu_State == 1)
        {
            // Update pattern menu
            patternMenu_update();
        }
	}
}


