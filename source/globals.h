#pragma once

#include <gba_input.h>

// -- GBA input functions --

// Is a key pressed?
static bool DesignTool_Inputs_Pressed(u32 key)
{
    bool is_down = (keysDown() & key);
    bool was_down = (keysUp() & key);

    return is_down && !was_down;
}

// Is a key held?
static bool DesignTool_Inputs_Held(u32 key)
{
    bool is_down = (keysDownRepeat() & key);
    return is_down;
}

// Is a key NOT held?
static bool DesignTool_Inputs_Released(u32 key)
{
    bool is_down = (keysDown() & key);
    bool was_down = (keysUp() & key);

    return !is_down && was_down;
}

// Design that's selected on the patterm menu. From 1 up to 8.
static unsigned int DesignTool_Menu_Pattern_Selected = 1;

// The max count of patterns to show/store/transmit.
static unsigned int DesignTool_Menu_Pattern_Max = 8;

/*
    Current menu.

    1 = Design Display Menu
    2 = Pattern Editor
    3 = Name Pattern
*/
static unsigned int DesignTool_Menu_State = 1;
