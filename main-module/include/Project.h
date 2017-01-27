#ifndef PROJECT_H
#define PROJECT_H

#include <boost/filesystem.hpp>
#include <vector>
#include <memory>

#include "Module.h"

class Project{
public:
  Project() { reparse(); }

  void printProject();
  void createMakefile();
  void reparse();
  void buildAllModules();

private:
  std::vector<std::shared_ptr<Module>> m_modules;
};

#endif
