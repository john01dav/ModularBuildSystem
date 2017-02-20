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

    //project object always exists in current directory, class used for
    //conceptual grouping and MBS is not designed to have more than one
    //instance of it
    Project project;
    project.printProject();
    project.createMakefile();
    project.buildAllModules();

    return 0;
  }catch(std::exception &ex){
    log(SEVERE, ex.what());
    return -1;
  }
}
