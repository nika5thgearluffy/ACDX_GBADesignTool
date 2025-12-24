#pragma once

#include "bn_core.h"
#include "bn_color.h"

// --FUNCTIONS--

// That way, 0xFF/255 can be used for white and etc.
static bn::color DesignTool_ColorSwatch(int red, int blue, int green)
{
    return bn::color(red / 8, blue / 8, green / 8);
}

// --VARIABLES--

// Design that's selected on the pattern menu. From 1 up to 8.
static int DesignTool_Menu_Pattern_Selected = 1;

// Page on the pattern menu.
static int DesignTool_Menu_Pattern_Selected_Page = 1;

// The max count of patterns to show/store/transmit.
static int DesignTool_Menu_Pattern_Max = 8;

/*
    Current menu.

    1 = Design Display Menu
    2 = Pattern Editor
    3 = Name Pattern
*/
static int DesignTool_Menu_State = 1;

// If true, the design tool is animating something
static bool DesignTool_Menu_IsAnimating = false;
