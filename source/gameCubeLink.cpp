#include "gameCubeLink.h"
#include "globals.h"

#include "LinkCube.hpp"

#include "bn_audio.h"

#include "bn_sound.h"
#include "bn_sound_items.h"

// LinkCube variable
LinkCube* linkCube;

// Magic number converter for transmitting patterns to the GC/Wii
static u32 mJOYSIO_ConvData(u8* data) {
    u8 conv_buf[sizeof(u32)];
  
    conv_buf[0] = data[3];
    conv_buf[1] = data[2];
    conv_buf[2] = data[1];
    conv_buf[3] = data[0];

    return *(u32*)conv_buf;
}

void gameCubeLink_start()
{
    // Better start the connection here
    linkCube = new LinkCube();
    linkCube->activate();
}

void gameCubeLink_update()
{
    // Make sure we can read IF the GameCube Link Cable is connected
    if (linkCube->isActive())
    {
        u32 value = linkCube->read();
        if (value == mJOYSIO_ConvData((u8*)"GAFJ"))
        {
            // Send out 0x8, needed to status an "OK" on ACGC
            //linkCube->send(0x00000008);
            // Send out "AAFJ" as well
            linkCube->send(mJOYSIO_ConvData((u8*)"AAFJ"));

            // The connection from here should be open.
            bn::sound_items::select_pattern.play(); // Example of action to take, for now
        }
    }
}
