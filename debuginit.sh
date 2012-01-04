cd Data
./GenerateCMakeLists.sh
cd ..

mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug