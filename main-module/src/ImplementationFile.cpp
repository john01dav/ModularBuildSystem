#include "ImplementationFile.h"

#include <istream>
#include <ostream>
#include <algorithm>
#include <stdexcept>

#include <boost/filesystem.hpp>

#include "Module.h"
#include "importparser.h"

using namespace boost;

ImplementationFile::ImplementationFile(const filesystem::path &path, const Module &module) :
  m_module(module),
  m_makeTarget("./bin/" + module.name() + "/" + path.filename().native() + ".o"),
  m_path(path)
{
  parseFile(module, m_includePaths, path);
}

void ImplementationFile::emitMakeTarget(std::ostream &out) const{
  //make target header
  out << m_makeTarget << ": " << m_path.native() << " ";
  for(const filesystem::path &path : m_includePaths){
    out << path.native() << " ";
  }
  out << std::endl;

  //make target command
  out << "\tg++ --std=c++11 -I" << m_module.includePath().native() << " -c " << m_path.native() << " -o " << m_makeTarget << std::endl;
}
