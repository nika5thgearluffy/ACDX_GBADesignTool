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

#include "bn_audio.h"
#include "bn_music.h"
#include "bn_sound.h"
#include "bn_sound_items.h"

#include "bn_keypad.h"

static float overlay_movement_leftTop = 0;

void patternMenu_draw()
{
    // Set the pattern menu overlay color
    bn::bg_palettes::set_transparent_color(DesignTool_ColorSwatch(173, 189, 255));

    // Draw pattern menu overlay!
    bn::regular_bg_ptr patternmenu_overlay_bg = bn::regular_bg_items::patternmenu_overlay.create_bg(overlay_movement_leftTop, overlay_movement_leftTop);

    // Draw window as well
    bn::regular_bg_ptr patternmenu_window_bg = bn::regular_bg_items::patternmenu_window.create_bg(0, 0);
    bn::core::update();
}

void patternMenu_update()
{
    // Move the overlay
    overlay_movement_leftTop = overlay_movement_leftTop - 0.50;

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
                DesignTool_Menu_Pattern_Selected_Page = 2;
                DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Selected + 4;
            }
            else if (DesignTool_Menu_Pattern_Selected_Page == 2)
            {
                DesignTool_Menu_Pattern_Selected_Page = 1;
                DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Selected - 4;
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
                DesignTool_Menu_Pattern_Selected_Page = 2;
                DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Selected + 4;
            }
            else if (DesignTool_Menu_Pattern_Selected_Page == 2)
            {
                DesignTool_Menu_Pattern_Selected_Page = 1;
                DesignTool_Menu_Pattern_Selected = DesignTool_Menu_Pattern_Selected - 4;
            }
        }
    }
}