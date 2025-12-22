#include "Ostream.hpp"
#include <iostream>

Ostream::Ostream() {
    std::cout << "Ostream Constructor\n";
}

Ostream::~Ostream() {
    std::cout << "Ostream Destructor\n";
}
