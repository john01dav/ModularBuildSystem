#ifndef IMPORTPARSER_H
#define IMPORTPARSER_H

#include <vector>

#include <boost/filesystem.hpp>

#include "Module.h"

void parseFile(const Module &module, std::vector<boost::filesystem::path> &includes, const boost::filesystem::path &file);

#endif
