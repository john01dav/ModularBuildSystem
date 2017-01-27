#include <iostream>
#include <vector>
#include <fstream>

#include <yaml-cpp/yaml.h>

#include "log.h"
#include "version.h"
#include "Project.h"

int main(int argc, char *argv[]){
  try{
    log(INFO, "Modular Build System Version " + VERSION);
    log(INFO, "");

    Project project;

    project.printProject();
    project.createMakefile();

    return 0;
  }catch(std::exception &ex){
    log(SEVERE, ex.what());
    return -1;
  }
}
