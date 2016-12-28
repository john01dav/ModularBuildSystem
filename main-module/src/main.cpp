#include <iostream>

#include "log.h"
#include "version.h"

int main(int argc, char *argv[]){
  log(INFO, "Modular Build System Version " + VERSION);
}
