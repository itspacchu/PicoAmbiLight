
#!/usr/bin/bash
echo "BUILDING"
cd build
cmake ..
make -j4
cp *.uf2 /run/media/pac/RPI-RP2
echo "DONE"