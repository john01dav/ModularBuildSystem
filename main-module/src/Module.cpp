#include "Module.h"

#include <stdexcept>

#include <boost/filesystem.hpp>

#include "SourceFile.h"

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

void Module::rebuildSourceList(){
  filesystem::path sourceDir(m_srcPath);

  if(!filesystem::exists(sourceDir)){
    throw std::invalid_argument("Source directory does not exist: " + m_srcPath.native());
  }

  if(!filesystem::is_directory(sourceDir)){
    throw std::invalid_argument("Source directory is not a directory: " + m_srcPath.native());
  }

  m_sourceFiles.clear();
  for(filesystem::directory_iterator it=filesystem::directory_iterator(sourceDir);it!=filesystem::directory_iterator();++it){
    m_sourceFiles.push_back(SourceFile(*it, *this));
  }
}

void Module::emitMakeTargets(std::ostream &out) const{
  //add dependency make targets and record names of each target
  for(const SourceFile &sourceFile : m_sourceFiles){
    sourceFile.emitMakeTarget(out);
  }

  //create the executable target name
  std::string executableOut = "./bin/" + m_name + "/" + m_name;

  //output executable target header
  out << executableOut << ": ";
  for(const SourceFile &sourceFile : m_sourceFiles){
    out << sourceFile.makeTargetName() << " ";
  }
  out << std::endl;

  //output linking command
  out << "\t" << "g++ ";
  for(const SourceFile &sourceFile : m_sourceFiles){ //output standard .o files
    out << sourceFile.makeTargetName() << " ";
  }
  for(const std::string &library : m_libraries){ //output library paths -- only static libraries supported ATM
    out << library << " ";
  }
  out << "-o " << executableOut << std::endl;
}
