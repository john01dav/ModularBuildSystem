#ifndef LOG_H
#define LOG_H
#include <iostream>

enum LogLevel{
  INFO,
  WARNING,
  SEVERE
};

void log(LogLevel logLevel, const std::string &message);

#endif
