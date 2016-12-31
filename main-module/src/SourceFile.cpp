#include "SourceFile.h"

#include <istream>
#include <algorithm>
#include <stdexcept>

#include <boost/filesystem.hpp>

#include "Module.h"

using namespace boost;

SourceFile::SourceFile(const filesystem::path &path, const filesystem::path &includePath) : m_path(path){
  std::ifstream fin(m_path.native()); //use member variables here instead of constructor arguments to ease any sort of future need to move this code into a standard member function
  std::string line;

  //loop through all lines in file
  while(std::getline(fin, line)){
    //check if current line is an include
    if(line.find("#include") == 0){
      //find first quote
      std::string::iterator firstQuote = std::find(line.begin(), line.end(), '"');
      if(firstQuote != line.end()){ //verify that this is really an include (or at least close enough), and, if so, find the second quote (on the next line)
        std::string::iterator secondQuote = std::find(firstQuote+1, line.end(), '"'); //firstQuote+1 is reliable because it will, at worst, be the same as line.end() C++ compiler will probably handle any furtherm malformed includes (ie. '#include "Module.h""')
        filesystem::path includedFilePath = includePath / std::string(firstQuote+1, secondQuote);
        m_includePaths.push_back(includedFilePath);

        //print an error if a missing include is included here to give a more useful message than something make may output
        if(!filesystem::exists(includedFilePath) || !filesystem::is_regular_file(includedFilePath)){
          throw std::runtime_error("Missing included file " + includedFilePath.native() + " in file " + path.native());
        }
      }
    }
  }

}