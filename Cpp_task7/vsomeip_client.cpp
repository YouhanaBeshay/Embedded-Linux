#include "vsomeip_client.hpp"



int main(int argc, char const *argv[])
{
    vsomeip_client myclient;
    myclient.start();
    return 0;
}
