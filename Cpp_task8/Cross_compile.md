### Credit to [maxmaster55](https://github.com/maxmaster55)

create a file in home called: user-config.jam
in it (use a valid path):

```
using gcc : arm : "/home/youhana/x-tools/aarch64-rpi3-linux-gnu/bin/aarch64-rpi3-linux-gnu-g++" ;
```

in the boost dir: 

```
./bootstrap.sh
```

then (replace with a valid path on your pc)

```
./b2 toolset=gcc-arm     link=shared threading=multi runtime-link=shared   --with-log   --with-system --with-thread --with-chrono --with-date_time --with-filesystem     --prefix=/home/youhana/ITI_assignments2/cpp_labs/vsomeip_for_rpi/boost-built install
```

no in vsomeip:

```
mkdir build
cd build
cmake ..  -DCMAKE_C_COMPILER=aarch64-rpi3-linux-gnu-gcc  -DCMAKE_INSTALL_PREFIX=/home/youhana/ITI_assignments2/cpp_labs/vsomeip_for_rpi/vsomeip-built/ -DCMAKE_CXX_COMPILER=aarch64-rpi3-linux-gnu-g++   -DBOOST_ROOT=/home/youhana/ITI_assignments2/cpp_labs/vsomeip_for_rpi/boost-built   -DBoost_NO_SYSTEM_PATHS=ON
```

make using more than once core(replace 24 for you pc):

```
make -j 24

make install
```

the libs will be in the build dir. <3