#This script provides a fallback method to build MBS to allow it to be built on systems that do not yet have MBS or before MBS is able to build itself
g++ --std=c++11 `ls ./main-module/src/*.cpp` -I./main-module/include -o mbs
