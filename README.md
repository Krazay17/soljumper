C++ game framework by Josh Massarella

git clone --recursive -j8 https://github.com/Krazay17/soljumper
mkdir build
cd build
cmake ..
cmake --build -j8 .

cd bin
./soljumper

# --if submodules arent found--
git submodule update --init --recursive