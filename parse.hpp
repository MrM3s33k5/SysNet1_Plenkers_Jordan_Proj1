#ifndef PARSE_HPP
#define PARSE_HPP

#include "param.hpp"

class Parse{
   //private:
    public:
    Param* param;
   
  // public: 
    Parse();
    ~Parse();

    void parseCommand(std::string command);
    void printParams();
};
#endif
