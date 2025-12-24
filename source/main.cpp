#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "bn_core.h"
#include "bn_math.h"
#include "bn_keypad.h"
#include "bn_display.h"
#include "bn_blending.h"

#include "patternMenu.h"
#include "globals.h"

int main(void)
{
    // Start butano!
    bn::core::init();

	while(true)
    {
        if (DesignTool_Menu_State == 1)
        {
            // Update pattern menu
            patternMenu_update();
        }
	}
}


