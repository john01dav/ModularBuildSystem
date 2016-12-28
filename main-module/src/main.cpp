#include <iostream>
#include <vector>
#include <yaml-cpp/yaml.h>

#include "log.h"
#include "version.h"
#include "Module.h"

int main(int argc, char *argv[]){
  log(INFO, "Modular Build System Version " + VERSION);
  log(INFO, "");

  //setup data structures
  std::vector<Module> modules;

  //load modules
  YAML::Node modulesFile = YAML::LoadFile("modules.yml");
  YAML::Node modulesNode = modulesFile["modules"];
  for(auto it=modulesNode.begin();it!=modulesNode.end();++it){
    Module module(
      it->first.as<std::string>(),
      it->second["src-dir"].as<std::string>(),
      it->second["include-dir"].as<std::string>()
    );

    YAML::Node libraries = it->second["libraries"];
    for(auto lit=libraries.begin();lit!=libraries.end();++lit){
      module.libraries().push_back(lit->as<std::string>());
    }

    modules.push_back(std::move(module)); //can use std::move safely since this is the last statement in the loop
  }

  //print module list
  for(Module &module : modules){
    log(INFO, "Module Name: " + module.name());
    log(INFO, "Source Path: " + module.srcPath());
    log(INFO, "Include Path" + module.includePath());

    std::string libraries = "Libraries: ";
    for(const std::string &library : module.libraries()){
      libraries += library + " ";
    }

    log(INFO, libraries);
    log(INFO, "");
  }
}
