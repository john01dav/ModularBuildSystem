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
    throw std::invalid_argument("Source directory does not exist: " + m_srcPath);
  }

  if(!filesystem::is_directory(sourceDir)){
    throw std::invalid_argument("Source directory is not a directory: " + m_srcPath);
  }

  for(filesystem::directory_iterator it=filesystem::directory_iterator(sourceDir);it!=filesystem::directory_iterator();++it){
    m_sourceFiles.push_back(SourceFile(*it, m_includePath));
  }
}
