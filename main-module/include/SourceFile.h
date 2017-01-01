#ifndef SOURCEFILE_H
#define SOURCEFILE_H

#include <string>
#include <vector>
#include <ostream>

#include <boost/filesystem.hpp>

class Module;

class SourceFile{
public:
  SourceFile(const boost::filesystem::path &path, const Module &module);

  const std::string& makeTargetName() const { return m_makeTarget; }
  const boost::filesystem::path& path() const { return m_path; }
  const std::vector<boost::filesystem::path>& includePaths() const { return m_includePaths; }

  void emitMakeTarget(std::ostream &out) const;

private:
  const Module &m_module;
  std::string m_makeTarget;
  boost::filesystem::path m_path;
  std::vector<boost::filesystem::path> m_includePaths;
};

#endif
