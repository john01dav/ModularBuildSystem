#ifndef SOURCEFILE_H
#define SOURCEFILE_H

#include <string>
#include <vector>
#include <ostream>

#include <boost/filesystem.hpp>

class Module;

class SourceFile{
public:
  SourceFile(const boost::filesystem::path &path, const boost::filesystem::path &includePath);

  const boost::filesystem::path& path() const { return m_path; }
  const std::vector<boost::filesystem::path>& includePaths() const { return m_includePaths; }

  std::string emitMakeTarget(std::ostream &out, const Module &module) const;

private:
  const boost::filesystem::path m_path;
  std::vector<boost::filesystem::path> m_includePaths;
};

#endif
