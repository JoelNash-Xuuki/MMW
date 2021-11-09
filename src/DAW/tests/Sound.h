#ifndef SOUND_H
#define SOUND_H

#include <string>

class Sound{
public:
  Sound( double amount, std::string currency )
    : m_amount( amount )
    , m_currency( currency )
  {
  }

  double getAmount() const;
  std::string getCurrency() const;

private:
  double m_amount;
  std::string m_currency;
};

#endif
