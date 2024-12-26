#include "pch.h"
#include "Core/Callbacks.h"

namespace Callback
{

bool ClickCallback(void *)
{
    Log::Print("Clicked");

    return true;
}

bool IntegerRangeCallback(void *pParameters)
{
    uint32_t value = *reinterpret_cast<uint32_t *>(pParameters);

    Log::Print("number: %d", value);

    return true;
}

bool FloatRangeCallback(void *pParameters)
{
    float value = *reinterpret_cast<float *>(pParameters);

    Log::Print("number: %f", value);

    return true;
}

bool ToggleCallback(void *pParameters)
{
    bool value = *reinterpret_cast<bool *>(pParameters);

    Log::Print(value ? "On" : "Off");

    return true;
}

}
