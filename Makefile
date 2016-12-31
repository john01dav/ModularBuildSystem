./bin/main-module/Module.cpp.o:
	g++ --std=c++11 -I./main-module/include -c ./main-module/src/Module.cpp -o ./bin/main-module/Module.cpp.o
./bin/main-module/log.cpp.o:
	g++ --std=c++11 -I./main-module/include -c ./main-module/src/log.cpp -o ./bin/main-module/log.cpp.o
./bin/main-module/SourceFile.cpp.o:
	g++ --std=c++11 -I./main-module/include -c ./main-module/src/SourceFile.cpp -o ./bin/main-module/SourceFile.cpp.o
./bin/main-module/main.cpp.o:
	g++ --std=c++11 -I./main-module/include -c ./main-module/src/main.cpp -o ./bin/main-module/main.cpp.o
./bin/main-module/main-module: ./bin/main-module/Module.cpp.o ./bin/main-module/log.cpp.o ./bin/main-module/SourceFile.cpp.o ./bin/main-module/main.cpp.o 
	g++ ./bin/main-module/Module.cpp.o ./bin/main-module/log.cpp.o ./bin/main-module/SourceFile.cpp.o ./bin/main-module/main.cpp.o /usr/local/lib/libyaml-cpp.a /usr/local/lib/libboost_filesystem.a /usr/local/lib/libboost_system.a -o ./bin/main-module/main-module
