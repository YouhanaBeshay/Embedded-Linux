#pragma once

#include "Stream.hpp"
class Istream : virtual public Stream {
private:
  /* data */
public:
  Istream(/* args */);
  ~Istream();
  virtual int readDigit() override;
  Stream &operator>>(int &digit) override;
};
