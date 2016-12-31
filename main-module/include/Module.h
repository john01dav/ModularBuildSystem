#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <vector>
#include <yaml-cpp/yaml.h>

#include "SourceFile.h"

class Module{
public:
  Module(const std::string &name, const YAML::Node &node);
  Module(const YAML::const_iterator &it) : Module(it->first.as<std::string>(), it->second) {} //allow the direct creation of a Mmodule from a node + name

  void rebuildSourceList();

  const std::string& name() const { return m_name; }
  const std::string& srcPath() const { return m_srcPath; }
  const std::string& includePath() const { return m_includePath; }
  const std::vector<std::string>& libraries() const { return m_libraries; }
  const std::vector<SourceFile>& sourceFiles() const { return m_sourceFiles; }

  std::vector<std::string>& libraries() { return m_libraries; }

private:
  std::string m_name;
  std::string m_srcPath;
  std::string m_includePath;
  std::vector<std::string> m_libraries;
  std::vector<SourceFile> m_sourceFiles;
};

#endif
