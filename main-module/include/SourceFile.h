#ifndef SOURCEFILE_H
#define SOURCEFILE_H

#include <string>
#include <vector>

#include <boost/filesystem.hpp>

class SourceFile{
public:
  SourceFile(const boost::filesystem::path &path, const boost::filesystem::path &includePath);

  const boost::filesystem::path& path() const { return m_path; }
  const std::vector<boost::filesystem::path>& includePaths() const { return m_includePaths; }

  void emitMakeTarget(std::ostream &out);

private:
  const boost::filesystem::path m_path;
  std::vector<boost::filesystem::path> m_includePaths;
};

#endif
