#ifndef PARAM_HPP
#define PARAM_HPP

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
/* don’t test program with more than this many tokens for input */
#define MAXARGS 32
/* classto hold input data */
/* feel free to add missing constructor, destcructor,and getter/setter functions */
class Param
{
    private:
        char *inputRedirect;           /* file name or NULL */
        char *outputRedirect;          /* file name or NULL */
        int  background;               /* either 0 (false) or 1 (true) */
//    int  argumentCount;            /* number of tokens in argument vector */
    public:
        char* argumentVector[MAXARGS]; /* array of strings */
        int  argumentCount;            /* number of tokens in argument vector */

        Param();
        ~Param();
        bool isValidToken(char* token);
        int setBackground(string arguments);
        int getBackground();
        void setInput(string in);
        char* getInput();
        void setOutput(string out);
        char* getOutput();
        void setArg(string arg);
        void clearArgs();
        void printParams();
        char** getArgVector();
        int getArgCount();

        
        char* getInputRedirect();
        char* getOutputRedirect();
        char* getArgumentAt(int index);

        
};
#endif
