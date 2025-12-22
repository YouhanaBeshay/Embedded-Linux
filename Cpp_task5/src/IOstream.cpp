#include "IOstream.hpp"
#include <iostream>
IOstream::IOstream() { std::cout << "IOstream Constructor\n"; }

IOstream::~IOstream() { std::cout << "IOstream Destructor\n"; }

void IOstream::writeDigit(int digit) {
  if (digit != -1) {
    std::cout << digit << "\n";
  }
}

Stream & IOstream::operator<<(int digit){
    writeDigit(digit);
    return *this; // for possible chaining
};