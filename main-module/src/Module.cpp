#include "Module.h"

#include <stdexcept>

#include <boost/filesystem.hpp>

using namespace boost;

void Module::buildSourceList(){
  filesystem::path sourceDir(m_srcPath);

  if(!filesystem::exists(sourceDir)){
    throw std::invalid_argument("Source directory does not exist: " + m_srcPath);
  }

  if(!filesystem::is_directory(sourceDir)){
    throw std::invalid_argument("Source directory is not a directory: " + m_srcPath);
  }

  for(filesystem::directory_iterator it=filesystem::directory_iterator(sourceDir);it!=filesystem::directory_iterator();++it){
    m_sourceFiles.push_back(it->path().native());
  }
}
