#pragma once

#include "Options/Option.h"
#include "Core/ValueOrPtr.h"
#include "UI/Text.h"

// Disable the C4481 warning for the override keyword
#pragma warning(push)
#pragma warning(disable : 4481)

template <typename T>
class RangeOption : public Option
{
public:
    RangeOption();

    RangeOption(const std::wstring &name, Callback callback, const ValueOrPtr<T> &value, T min, T max, T step);

    virtual bool Update(ATG::GAMEPAD *pGamepad) override;

    virtual HRESULT Render(float x, float y, float width) override;

private:
    T m_Min;
    T m_Max;
    T m_Step;
    ValueOrPtr<T> m_Current;

    Text m_Text;
};

#pragma warning(pop)
