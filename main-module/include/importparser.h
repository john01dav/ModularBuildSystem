#ifndef IMPORTPARSER_H
#define IMPORTPARSER_H

#include <set>

#include <boost/filesystem.hpp>

#include "Module.h"

void parseFile(const Module &module, std::set<boost::filesystem::path> *includes, const boost::filesystem::path &file);

#endif
