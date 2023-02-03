#pragma once

// Class to interact with a value of type T or a pointer of type T* seemlessly
template <typename T>
class ValueOrPtr
{
public:
    ValueOrPtr(const T &value)
        : m_Value(value), m_Ptr(nullptr), m_Index(0) {}

    ValueOrPtr(T *ptr)
        : m_Value(T()), m_Ptr(ptr), m_Index(1) {}

    inline const T &value() const { return m_Index == 1 ? *m_Ptr : m_Value; }

    inline T *ptr() const { return m_Index == 1 ? m_Ptr : const_cast<float *>(&m_Value); }

    inline const T &operator*() const { return value(); }

    inline T *operator&() const { return ptr(); }

    inline const T &operator+=(const T &value) { return m_Index == 1 ? *m_Ptr += value : m_Value += value; }

    inline const T &operator-=(const T &value) { return m_Index == 1 ? *m_Ptr -= value : m_Value -= value; }

private:
    T m_Value;
    T *m_Ptr;
    uint8_t m_Index;
};
