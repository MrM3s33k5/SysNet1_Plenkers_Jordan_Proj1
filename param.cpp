#include "param.hpp"


// Constructor
Param::Param()
{
   background = 0;
   argumentCount = 0;
   for (int i = 0; i < MAXARGS; ++i)
   {
      argumentVector[i] = new char;
   }
}

// Destructor
Param::~Param()
{
    free(argumentVector);
    free(inputRedirect);
    free(outputRedirect);
}

// checks if parsed token is valid
bool Param::isValidToken(char* token)
{
   if(token == NULL)
   {
      return false;
   }
   return true;
}

//takes in a string to set the input redirect
void Param::setInput(string in)
{
   string redirectCatch = in.substr(1);			
   inputRedirect = new char [redirectCatch.length()];
   strcpy(inputRedirect, redirectCatch.c_str());
}

//returns input redirect
char* Param::getInput()
{
   return inputRedirect;
}

//takes in a string to set the output redirect
void Param::setOutput(string out)
{
   string redirectCatch = out.substr(1);
   outputRedirect = new char [redirectCatch.length()];
   strcpy(outputRedirect, redirectCatch.c_str());
   //delete[] outputRedirect;
}

//returns output redirect
char* Param::getOutput()
{
   return outputRedirect;
}

/*
checks command for '&' and sets background arg to 1 (true)
if found and -1(false) if not
*/
int Param::setBackground(string arguments)
{
    int pos = arguments.size() - 1;
    if(arguments.find("&") == arguments.size() - 1)
    {
        background = 1;
        return pos;
    }
    else
    {
        return -1;
    }
}

//returns the background variable
int Param::getBackground()
{
   return background;
}

//copys parsed token into argument vector
void Param::setArg(string arg)
{
        strcpy(argumentVector[argumentCount++], arg.c_str());
}

//returns argument vector
char** Param::getArgVector()
{
    return this->argumentVector;
}

//returns num of current args
int Param::getArgCount()
{
    return this->argumentCount;
}

//returns output redirect
char* Param::getOutputRedirect()
{
    return this->outputRedirect;
}

//returns input redirect
char* Param::getInputRedirect()
{
    return this->inputRedirect;
}

//returns arg at specified index (0 based)
char* Param::getArgumentAt(int index)
{
    return this->argumentVector[index];
}

//clears the input redirect, output redirect and all other args from the shell
void Param::clearArgs()
{
    inputRedirect = NULL;
    outputRedirect = NULL;
    background = 0;
    for(int i = 0; i < argumentCount; ++i)
    {
        delete argumentVector[i];
    }

    for(int i = 0; i < MAXARGS; ++i)
    {
        argumentVector[i] = new char;
    }

    argumentCount = 0;
}

/*
prints list of current args 
Should only be run in DEBUG mode
*/
void Param::printParams()
{
    cout << endl;
    string input = (inputRedirect != NULL) ? inputRedirect:"NULL";
    string output = (outputRedirect != NULL) ? outputRedirect:"NULL";
		
    cout << "InputRedirect:["<< input<< "]"<< endl <<
      "OutputRedirect:["<< output << "]"<< endl <<
      "Background: ["<< background << "]"<< endl <<
      "ArgumentCount: ["<< argumentCount<< "]"<< endl;
    for (int i = 0; i < argumentCount; i++)
    {
        cout << "ArgumentVector[" << i << "]: [" << 
         argumentVector[i]<< "]"<< endl;
    }
    cout << endl;
}
