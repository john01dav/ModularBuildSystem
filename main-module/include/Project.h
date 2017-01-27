#ifndef PROJECT_H
#define PROJECT_H

#include <boost/filesystem.hpp>
#include <vector>
#include <memory>

#include "Module.h"

class Project{
public:
  Project(const boost::filesystem::path &projectRoot) :
    m_projectRoot(projectRoot) { reparse(); }

  void printProject();
  void createMakefile();
  void reparse();

private:
  boost::filesystem::path m_projectRoot;
  std::vector<std::shared_ptr<Module>> m_modules;
};

#endif
