#include <iostream>
#include <string>
#include <stdexcept>

#include "log.h"

std::string getLogPrefix(LogLevel logLevel);

void log(LogLevel logLevel, const std::string &message){
  std::ostream &out = (logLevel == INFO ? std::cout : std::cerr);
  out << "[" << getLogPrefix(logLevel) << "]: " << message << std::endl;
}

std::string getLogPrefix(LogLevel logLevel){
  switch(logLevel){
    case INFO:
      return "INFO";
    case WARNING:
      return "WARNING";
    case SEVERE:
      return "SEVERE";
    default:
      throw std::runtime_error("Unknown log level: " + std::to_string(logLevel));
  }
}
