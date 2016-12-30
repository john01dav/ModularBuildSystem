#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <vector>

class Module{
public:
  Module(const std::string &name, const std::string &srcPath, const std::string &includePath)
    : m_name(name), m_srcPath(srcPath), m_includePath(includePath) {}

  void buildSourceList();

  const std::string& name() const { return m_name; }
  const std::string& srcPath() const { return m_srcPath; }
  const std::string& includePath() const { return m_includePath; }
  const std::vector<std::string>& libraries() const { return m_libraries; }
  const std::vector<std::string>& sourceFiles() const { return m_sourceFiles; }

  std::vector<std::string>& libraries() { return m_libraries; }

private:
  std::string m_name;
  std::string m_srcPath;
  std::string m_includePath;
  std::vector<std::string> m_libraries;
  std::vector<std::string> m_sourceFiles;
};

#endif
