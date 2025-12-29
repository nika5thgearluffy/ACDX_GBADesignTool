#include "patternMenu.h"
#include "globals.h"

#include "bn_core.h"

#include "bn_bgs.h"
#include "bn_bg_palettes.h"
#include "bn_bitmap_bg.h"

#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_item.h"
#include "bn_regular_bg_actions.h"

#include "bn_regular_bg_items_patternmenu_window.h"
#include "bn_regular_bg_items_patternmenu_overlay.h"

#include "bn_sprites.h"
#include "bn_sprite_tiles.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_tiles.h"
#include "bn_sprite_tiles_item.h"

#include "bn_sprite_items_patternmenu_handcursor.h"
#include "bn_sprite_items_patternmenu_selectedpattern.h"

#include "bn_audio.h"
#include "bn_music.h"
#include "bn_music_items.h"

#include "bn_sound.h"
#include "bn_sound_items.h"

#include "bn_keypad.h"

static float overlay_movement_leftTop = 0;
static int patternMenu_hasStarted = false;

static int patternmenu_selectedpattern_x = 42;
static int patternmenu_selectedpattern_y = 42;

void patternMenu_start()
{
    if (!patternMenu_hasStarted)
    {
        /*if (bn::music::playing_item()->bn::music_items::pattern_editor)
        {
            bn::music_items::pattern_editor.stop();
        }*/
        bn::music_items::main_menu.play();
    }
    patternMenu_hasStarted = true;
}

void patternMenu_draw()
{
    // Set the pattern menu overlay color
    bn::bg_palettes::set_transparent_color(DesignTool_ColorSwatch(173, 189, 255));

    // Draw pattern menu overlay!
    bn::regular_bg_ptr patternmenu_overlay_bg = bn::regular_bg_items::patternmenu_overlay.create_bg(overlay_movement_leftTop, overlay_movement_leftTop);

    // Draw window as well
    bn::regular_bg_ptr patternmenu_window_bg = bn::regular_bg_items::patternmenu_window.create_bg(0, 0);

    // Draw pattern selector box
    bn::sprite_ptr patternmenu_box_pattern_selected = bn::sprite_items::patternmenu_selectedpattern.create_sprite(patternmenu_selectedpattern_x, patternmenu_selectedpattern_y);

    // Draw hand pointer
    bn::sprite_ptr patternmenu_handcursor_ptr = bn::sprite_items::patternmenu_handcursor.create_sprite(patternmenu_selectedpattern_x + 18, patternmenu_selectedpattern_y - 20);
    bn::sprite_animate_action<3> patternmenu_handcursor_action = bn::create_sprite_animate_action_forever(patternmenu_handcursor_ptr, 8, bn::sprite_items::patternmenu_handcursor.tiles_item(), 0, 1, 2);

    patternmenu_handcursor_action.update();
    bn::core::update();
}

void patternMenu_update()
{
    // Starting function
    patternMenu_start();

    // Move the overlay
    overlay_movement_leftTop = overlay_movement_leftTop - 0.25;

    // Draw the menu
    patternMenu_draw();

    if (!DesignTool_Menu_IsAnimating)
    {
        if (bn::keypad::left_pressed() || bn::keypad::right_pressed() || bn::keypad::up_pressed() || bn::keypad::down_pressed())
        {
            bn::sound_items::move_cursor.play();
        }
        if (bn::keypad::a_pressed())
        {
            bn::sound_items::select_pattern.play();
        }

        // Selected pattern
        if (DesignTool_Menu_Pattern_Selected_Page == 1)
        {
            patternmenu_selectedpattern_x = -60 + ((DesignTool_Menu_Pattern_Selected - 1) * 40);
            patternmenu_selectedpattern_y = -20;
        }
        else if (DesignTool_Menu_Pattern_Selected_Page == 2)
        {
            patternmenu_selectedpattern_x = -60 + (((DesignTool_Menu_Pattern_Selected - 4) - 1) * 40);
            patternmenu_selectedpattern_y = 20;
        }

        // Moving pattern selections
        if (bn::keypad::left_pressed())
        {
            DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Selected - 1;
            if (DesignTool_Menu_Pattern_Selected < 1 && DesignTool_Menu_Pattern_Selected_Page == 1)
            {
                DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Max / 2;
            }
            else if (DesignTool_Menu_Pattern_Selected < 5 && DesignTool_Menu_Pattern_Selected_Page == 2)
            {
                DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Max;
            }
        }
        else if (bn::keypad::right_pressed())
        {
            DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Selected + 1;
            if (DesignTool_Menu_Pattern_Selected > (DesignTool_Menu_Pattern_Max / 2) && DesignTool_Menu_Pattern_Selected_Page == 1)
            {
                DesignTool_Menu_Pattern_Selected = 1;
            }
            else if (DesignTool_Menu_Pattern_Selected > DesignTool_Menu_Pattern_Max && DesignTool_Menu_Pattern_Selected_Page == 2)
            {
                DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Max / 2;
            }
        }
        else if (bn::keypad::up_pressed())
        {
            DesignTool_Menu_Pattern_Selected_Page = DesignTool_Menu_Pattern_Selected_Page - 1;
            if (DesignTool_Menu_Pattern_Selected_Page < 1)
            {
                DesignTool_Menu_Pattern_Selected_Page = 1;
            }
            else if (DesignTool_Menu_Pattern_Selected_Page > 2)
            {
                DesignTool_Menu_Pattern_Selected_Page = 2;
            }

            if (DesignTool_Menu_Pattern_Selected_Page == 1)
            {
                if (DesignTool_Menu_Pattern_Selected > 4)
                {
                    DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Selected - 4;
                }
            }
            else if (DesignTool_Menu_Pattern_Selected_Page == 2)
            {
                if (DesignTool_Menu_Pattern_Selected < 5)
                {
                    DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Selected + 4;
                }
            }
        }
        else if (bn::keypad::down_pressed())
        {
            DesignTool_Menu_Pattern_Selected_Page = DesignTool_Menu_Pattern_Selected_Page + 1;
            if (DesignTool_Menu_Pattern_Selected_Page < 1)
            {
                DesignTool_Menu_Pattern_Selected_Page = 1;
            }
            else if (DesignTool_Menu_Pattern_Selected_Page > 2)
            {
                DesignTool_Menu_Pattern_Selected_Page = 2;
            }

            if (DesignTool_Menu_Pattern_Selected_Page == 1)
            {
                if (DesignTool_Menu_Pattern_Selected > 4)
                {
                    DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Selected - 4;
                }
            }
            else if (DesignTool_Menu_Pattern_Selected_Page == 2)
            {
                if (DesignTool_Menu_Pattern_Selected < 5)
                {
                    DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Selected + 4;
                }
            }
        }
    }
}