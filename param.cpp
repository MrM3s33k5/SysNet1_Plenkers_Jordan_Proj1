#include "param.hpp"

Param::Param(){
   background = 0;
   argumentCount = 0;
   for (int i = 0; i < MAXARGS; ++i)
      argumentVector[i] = new char;
}

bool Param::isValidToken(char* token){
   if(token == NULL){
      return false;
   }
   return true;
}

void Param::setInput(string in){
   string redirectCatch = in.substr(1);			
   inputRedirect = new char [redirectCatch.length()];
   strcpy(inputRedirect, redirectCatch.c_str());
   //delete[] inputRedirect;
}

char* Param::getInput(){
   return inputRedirect;
}

void Param::setOutput(string out){
   string redirectCatch = out.substr(1);
   outputRedirect = new char [redirectCatch.length()];
   strcpy(outputRedirect, redirectCatch.c_str());
   //delete[] outputRedirect;
}
char* Param::getOutput(){
   return outputRedirect;
}

void Param::setBackground(string arguments){
   if(arguments.find("&") == arguments.size() - 1){
      background = 1;
   }
}

int Param::getBackground(){
   return background;
}

void Param::setArg(string arg){
   strcpy(argumentVector[argumentCount++], arg.c_str());
}

void Param::clearArgs(){
   for(int i = 0; i < argumentCount; ++i){
      argumentVector[i] = NULL;
   }
   argumentCount = 0;
}
	
void Param::printParams(){
   string input = (inputRedirect != NULL) ? inputRedirect:"NULL";
   string output = (outputRedirect != NULL) ? outputRedirect:"NULL";
		
   cout << "InputRedirect:["<< input<< "]"<< endl <<
      "OutputRedirect:["<< output << "]"<< endl <<
      "Background: ["<< background << "]"<< endl <<
      "ArgumentCount: ["<< argumentCount<< "]"<< endl;
   for (int i = 0; i < argumentCount; i++)
      cout << "ArgumentVector[" << i << "]: [" << 
         argumentVector[i]<< "]"<< endl;
}
