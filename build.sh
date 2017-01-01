#This script provides a fallback method to build MBS to allow it to be built on systems that do not yet have MBS or before MBS is able to build itself
g++ -g -O0 --std=c++11 `ls ./main-module/src/*.cpp` -I./main-module/include /usr/local/lib/libyaml-cpp.a /usr/local/lib/libboost_filesystem.a /usr/local/lib/libboost_system.a -o mbs
