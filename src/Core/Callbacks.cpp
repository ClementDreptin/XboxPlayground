#include "pch.h"
#include "Core\Callbacks.h"

namespace Callback
{

void ClickCallback(void *)
{
    Log::Info("Clicked");
}

void RangeCallback(void *pParameters)
{
    float value = *reinterpret_cast<float *>(pParameters);

    Log::Info("number: %f", value);
}

void ToggleCallback(void *pParameters)
{
    bool value = *reinterpret_cast<bool *>(pParameters);

    Log::Info(value ? "On" : "Off");
}

}
