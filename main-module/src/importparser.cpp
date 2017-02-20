#include "importparser.h"

#include <set>
#include <fstream>

#include <boost/filesystem.hpp>

#include "Module.h"

using namespace boost;

void parseFile(const Module &module, std::set<boost::filesystem::path> *includes, const filesystem::path &file){
  std::ifstream fin(file.native());
  std::string line;

  //loop through all lines in file
  while(std::getline(fin, line)){
    //check if current line is an include
    if(line.find("#include") == 0){
      //find first quote
      std::string::iterator firstQuote = std::find(line.begin(), line.end(), '"');
      if(firstQuote != line.end()){ //verify that this is really an include (or at least close enough), and, if so, find the second quote (on the next line)
        std::string::iterator secondQuote = std::find(firstQuote+1, line.end(), '"'); //firstQuote+1 is reliable because it will, at worst, be the same as line.end() C++ compiler will probably handle any further malformed includes (ie. '#include "Module.h""')
        filesystem::path includedFilePath = module.includePath() / std::string(firstQuote+1, secondQuote);
        includes->insert(includedFilePath);

        //print an error if a missing include is included here to give a more useful message than something make may output
        if(!filesystem::exists(includedFilePath) || !filesystem::is_regular_file(includedFilePath)){
          throw std::runtime_error("Missing included file " + includedFilePath.native() + " in file " + file.native());
        }
      }
    }
  }
}
