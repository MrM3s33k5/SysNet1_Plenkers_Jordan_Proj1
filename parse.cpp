#include "parse.hpp"


// FIXME:  Get garbage appended to the end of the last argument
//         in argumentVector when there is a space at the end of 
//         the input string.  Need to try to fix this.  


// Constructor
Parse::Parse(){
   param = new Param();
}

// Destructor, calls destroy on created param object
Parse::~Parse()
{
//     delete param;
}

//used to parse the input string
void Parse::parseCommand(std::string command)
{
    char token[command.length()];
    string redirectCatch;
    int ampersandLoc;
    
    // Checking for background character and if present, 
    // setting background variable and erasing & from 
    // command input stirng. 
    ampersandLoc = param->setBackground(command);
	if(ampersandLoc >= 0)
    {
        command.erase(ampersandLoc, ampersandLoc);
    }
    
    
    strncpy(token, command.c_str(), sizeof(token));
    token[sizeof(token)] = '\0';
   
//    for (int i = 0; i < command.length(); ++i){
//       token[i] = command[i];
//    }
   

    char *tok = strtok(token, " ,\n,\t");
    char *newTok = tok;
    while (newTok != NULL)
    {
      redirectCatch = newTok;
    	    	
        if (redirectCatch.find("<") == 0)
        {
            param->setInput(redirectCatch);
            newTok = strtok(NULL, " ,\n,\t");
      
            if(!param->isValidToken(newTok))
            {
                break;
            }
      	
            redirectCatch = newTok;
        }
   	
        if (redirectCatch.find(">") == 0)
        {
            param->setOutput(redirectCatch);
            newTok = strtok(NULL, " ,\n,\t");
            if(param->getBackground())
            {
                break;
            }
            if(!param->isValidToken(newTok))
            {
                break;
            }
        }
            
        else
        {
            param->setArg(redirectCatch);
            newTok = strtok(NULL, " ,\n,\t");
        }
   }
   
    // execvp needs a char* const array[] with a null in the last
    // position in the array.  
        param->argumentVector[param->argumentCount] = (char*)nullptr;
}

//prints args using Param class' printParam()
void Parse::printParams()
{
   param->printParams();
}
