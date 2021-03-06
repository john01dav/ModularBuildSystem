#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include <boost/filesystem.hpp>

#include "ImplementationFile.h"

class Module{
public:
  //constructors to create a module from a YAML::Node
  Module(const std::string &name, const YAML::Node &node);
  explicit Module(const YAML::const_iterator &it) : Module(it->first.as<std::string>(), it->second) {} //allow the direct creation of a Module from a node with a name in a single object

  //modules can not be copied
  Module(const Module &module) = delete;
  Module operator=(const Module &module) = delete;

  //actions
  void printModule() const;
  void rebuildSourceList();
  void emitMakeTargets(std::ostream &out) const;

  //accesors
  std::string makeTarget() const { return "./bin/" + m_name + "/" + m_name; }
  const std::string& name() const { return m_name; }
  const boost::filesystem::path& srcPath() const { return m_srcPath; }
  const boost::filesystem::path& includePath() const { return m_includePath; }
  const std::vector<std::string>& libraries() const { return m_libraries; }
  const std::vector<ImplementationFile>& sourceFiles() const { return m_implementationFiles; }

  std::vector<std::string>& libraries() { return m_libraries; }

private:
  std::string m_name;
  boost::filesystem::path m_srcPath;
  boost::filesystem::path m_includePath;
  std::vector<std::string> m_libraries;
  std::vector<ImplementationFile> m_implementationFiles;
};

#endif
