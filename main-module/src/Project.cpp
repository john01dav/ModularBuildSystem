#include "Project.h"

#include <memory>
#include <cstdlib>

#include <yaml-cpp/yaml.h>

#include <boost/filesystem.hpp>

void Project::printProject(){
  for(std::shared_ptr<Module> module : m_modules){
    module->printModule();
  }
}

void Project::createMakefile(){
  std::ofstream fout("Makefile");

  //add default message to tell the user how to use the makefile
  fout << "default:" << std::endl;
  fout << "\t" << "@echo Please choose the path of the binary to build or choose all-modules." << std::endl;

  //output all-modules target
  fout << "all-modules: ";
  for(std::shared_ptr<Module> module : m_modules) fout << module->makeTarget() << " ";
  fout << std::endl;

  //output various targets for each module
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

void Project::buildAllModules(){
  std::system("make all-modules -j10");
}
