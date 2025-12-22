#include "Istream.hpp"
#include <iostream>
Istream::Istream() { std::cout << "Istream Constructor\n"; }

Istream::~Istream() { std::cout << "Istream Destructor\n"; }

int Istream::readDigit() {
  // get the digit from the terminal
  std::string input;
  std::cout << "Enter a digit (0-9): ";
  std::cin >> input;

  // check that the input is a digit from 0-9
  if (input.length() == 1 && input[0] >= '0' && input[0] <= '9') {
    return std::stoi(input);
  } else {
    std::cout << "Invalid input\n";
    return -1; // return -1 to indicate an error
  }
}

Stream & Istream::operator>>(int &digit){
    digit = readDigit();
    return *this; // for possible chaining
};