#ifndef PARSE_HPP
#define PARSE_HPP

#include "param.hpp"

class Parse{
   private:
   Param* param;

   public:
   Parse();
   Param* getParam();
   int getBackground();
   void parseCommand(std::string command);
   void printParams();
};
#endif

