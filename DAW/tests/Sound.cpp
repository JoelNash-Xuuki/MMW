#include "Sound.h"

#include <string>

double Sound :: getAmount() const
{
    return m_amount;
}

std::string Sound :: getCurrency() const
{
    return m_currency;
}
