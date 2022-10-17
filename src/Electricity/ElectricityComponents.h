#pragma once
#include "Clap.h"
#include "Tiles.h"

using namespace Clap;

namespace Game2D
{
    enum class ElectricalType
    {
        NONE = 0,
        WIRE,
        BATTERY,
        LED,
        SWITCH,
        TRANSISTOR
    };

    struct ElectricalComponent
    {
        ElectricalType Type;

        uint32_t Width;
        uint32_t Height;

        bool State = false;
    };

    struct BatteryComponent
    {
        
    };
    // CUSTOM BEHAVIOUR CHIP COMPONENT CONTAINS A SCRIPT ATTACHED
    // struct Chip
    // {
    //     ByteCode Task;
    //     std::vector<Entity> Inputs;
    //     std::vector<Entity> Outputs;
    // }

}