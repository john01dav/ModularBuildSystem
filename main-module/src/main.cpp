#include <iostream>
#include <yaml-cpp/yaml.h>

#include "log.h"
#include "version.h"

int main(int argc, char *argv[]){
  log(INFO, "Modular Build System Version " + VERSION);

  //load modules
  YAML::Node modulesFile = YAML::LoadFile("modules.yml");
  YAML::Node modules = modulesFile["modules"];
  for(auto it=modules.begin();it!=modules.end();++it){
    std::cout << "Module Name: " << it->first << std::endl;
    std::cout << "Source Path: " << it->second["src-dir"] << std::endl;
    std::cout << "Include Path: " << it->second["include-dir"] << std::endl;

    YAML::Node libraries = it->second["libraries"];
    std::cout << "Libraries: " << std::endl;
    for(auto lit=libraries.begin();lit!=libraries.end();++lit){
      std::cout << "\t- " << lit->as<std::string>() << std::endl;
    }
  }
}
