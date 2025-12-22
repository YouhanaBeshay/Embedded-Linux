#pragma once

#include "Stream.hpp"
class Ostream : virtual public Stream {
private:
  /* data */
public:
  Ostream(/* args */);
  ~Ostream();
  void writeDigit(int digit) = 0;
};
