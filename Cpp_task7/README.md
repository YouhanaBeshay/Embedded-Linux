# vSomeIP Caplock Service & client :
- A vSomeIP service that waits for a client to to send either '0' or '1' to control the CapsLock LED.
- A vSomeIP client that sends '0' or '1' to the service to control the CapsLock LED.
## Build & Run
***NOTE:*** Run the service and client in different terminals
```bash
cmake . -B build
cmake --build build
cd build

sudo ./vsomeip_service

./vsomeip_client
```