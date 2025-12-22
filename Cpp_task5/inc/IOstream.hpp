#pragma once

#include "Istream.hpp"
#include "Ostream.hpp"

class IOstream : public Istream, public Ostream
{
private:
 
public:
    IOstream( );
    ~IOstream();
    void writeDigit(int digit) override;

    Stream& operator<<(int digit) override;
};

