#pragma once

namespace EnableConfig{
    const bool CLIMB    = true;
    const bool DRIVE    = true;
    const bool INTAKE   = true;
    const bool SHOOTER  = true;
}

namespace DebugConfig{
    const bool AUTO     = false;

    const bool CLIMB    = false;

    const bool DRIVE    = false;
    const bool AUTO_LINEUP = false;

    const bool INTAKE   = false;

    const struct {
        const bool SHOOTER      = true;
        const bool LEFT_FLY     = true;
        const bool RIGHT_FLY    = false;
        const bool PIVOT        = true;
    } SHOOTER;
}