#include "pch.h"
#include "Core/Callbacks.h"

namespace Callback
{

bool ClickCallback(void *)
{
    Log::Info("Clicked");

    return true;
}

bool RangeCallback(void *pParameters)
{
    float value = *reinterpret_cast<float *>(pParameters);

    Log::Info("number: %f", value);

    return true;
}

bool ToggleCallback(void *pParameters)
{
    bool value = *reinterpret_cast<bool *>(pParameters);

    Log::Info(value ? "On" : "Off");

    return true;
}

}
