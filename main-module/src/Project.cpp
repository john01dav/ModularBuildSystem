#include "Project.h"

#include <memory>

#include <yaml-cpp/yaml.h>

#include <boost/filesystem.hpp>

void Project::printProject(){
  for(std::shared_ptr<Module> module : m_modules){
    module->printModule();
  }
}

void Project::createMakefile(){
  std::ofstream fout("Makefile");

  fout << "default:" << std::endl;
  fout << "\t" << "@echo Please choose the path of the binary to build." << std::endl;

  for(std::shared_ptr<Module> module : m_modules){
    module->emitMakeTargets(fout);
  }
}

void Project::reparse(){
  m_modules.clear();

  //load modules
  YAML::Node modulesFile = YAML::LoadFile("modules.yml");
  YAML::Node modulesNode = modulesFile["modules"];
  for(YAML::const_iterator it=modulesNode.begin();it!=modulesNode.end();++it){
    m_modules.push_back(std::make_shared<Module>(it));
  }
}
