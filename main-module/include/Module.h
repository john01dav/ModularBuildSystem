#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <vector>

#include <yaml-cpp/yaml.h>

#include <boost/filesystem.hpp>

#include "SourceFile.h"

class Module{
public:
  Module(const std::string &name, const YAML::Node &node);
  explicit Module(const YAML::const_iterator &it) : Module(it->first.as<std::string>(), it->second) {} //allow the direct creation of a Module from a node + name

  void rebuildSourceList();
  void emitMakeTargets(std::ostream &out) const;

  const std::string& name() const { return m_name; }
  const boost::filesystem::path& srcPath() const { return m_srcPath; }
  const boost::filesystem::path& includePath() const { return m_includePath; }
  const std::vector<std::string>& libraries() const { return m_libraries; }
  const std::vector<SourceFile>& sourceFiles() const { return m_sourceFiles; }

  std::vector<std::string>& libraries() { return m_libraries; }

private:
  std::string m_name;
  boost::filesystem::path m_srcPath;
  boost::filesystem::path m_includePath;
  std::vector<std::string> m_libraries;
  std::vector<SourceFile> m_sourceFiles;
};

#endif
