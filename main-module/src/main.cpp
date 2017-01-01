#include <iostream>
#include <vector>
#include <fstream>

#include <yaml-cpp/yaml.h>

#include "log.h"
#include "version.h"
#include "Module.h"

int main(int argc, char *argv[]){
  try{
    log(INFO, "Modular Build System Version " + VERSION);
    log(INFO, "");

    //setup data structures
    std::vector<Module*> modules; //pointers to ensure that references & pointers can be held to this module

    //load modules
    YAML::Node modulesFile = YAML::LoadFile("modules.yml");
    YAML::Node modulesNode = modulesFile["modules"];
    for(YAML::const_iterator it=modulesNode.begin();it!=modulesNode.end();++it){
      log(INFO, "Loading Module: " + it->first.as<std::string>());
      modules.push_back(new Module(it));
    }

    //print module list (Temporary code)
    for(Module *module : modules){
      log(INFO, "Module Name: " + module->name());
      log(INFO, "Source Path: " + module->srcPath().native());
      log(INFO, "Include Path: " + module->includePath().native());

      std::string libraries = "Libraries: ";
      for(const std::string &library : module->libraries()){
        libraries += library + " ";
      }

      log(INFO, libraries);

      log(INFO, "Source Files: ");
      for(const SourceFile &file : module->sourceFiles()){
        std::cout << file.path().native() << ", "; //no need to create a new log line
      }

      log(INFO, "");
    }

    //emit makefile
    std::ofstream fout("Makefile");

    for(Module *module : modules){
      module->emitMakeTargets(fout);
      delete module;
    }

    return 0;
  }catch(std::exception &ex){
    log(SEVERE, ex.what());
    return -1;
  }
}
