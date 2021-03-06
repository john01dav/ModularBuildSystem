#include "Module.h"

#include <stdexcept>
#include <iostream>

#include <boost/filesystem.hpp>

#include "ImplementationFile.h"
#include "log.h"

using namespace boost;

Module::Module(const std::string &name, const YAML::Node &node) :
  m_name(name),
  m_srcPath(node["src-dir"].as<std::string>()),
  m_includePath(node["include-dir"].as<std::string>())
{
  YAML::Node libraries = node["libraries"];

  for(YAML::const_iterator it=libraries.begin();it!=libraries.end();++it){
    m_libraries.push_back(it->as<std::string>());
  }

  rebuildSourceList();
}

void Module::printModule() const{
  log(INFO, "Module Name: " + m_name);
  log(INFO, "Source Path: " + m_srcPath.native());
  log(INFO, "Include Path: " + m_includePath.native());
}

void Module::rebuildSourceList(){
  filesystem::path sourceDir(m_srcPath);

  if(!filesystem::exists(sourceDir)){
    throw std::invalid_argument("Source directory does not exist: " + m_srcPath.native());
  }

  if(!filesystem::is_directory(sourceDir)){
    throw std::invalid_argument("Source directory is not a directory: " + m_srcPath.native());
  }

  m_implementationFiles.clear();
  for(filesystem::directory_iterator it=filesystem::directory_iterator(sourceDir);it!=filesystem::directory_iterator();++it){
    m_implementationFiles.push_back(ImplementationFile(*it, *this));
  }
}

void Module::emitMakeTargets(std::ostream &out) const{
  //add dependency make targets and record names of each target
  for(const ImplementationFile &sourceFile : m_implementationFiles){
    sourceFile.emitMakeTarget(out);
  }

  //output executable target header
  out << makeTarget() << ": ";
  for(const ImplementationFile &sourceFile : m_implementationFiles){
    out << sourceFile.makeTargetName() << " ";
  }
  out << std::endl;

  //output linking command
  out << "\t" << "g++ ";
  for(const ImplementationFile &sourceFile : m_implementationFiles){ //output standard .o files
    out << sourceFile.makeTargetName() << " ";
  }
  for(const std::string &library : m_libraries){ //output library paths -- only static libraries supported ATM
    out << library << " ";
  }
  out << "-o " << makeTarget() << std::endl;
}
