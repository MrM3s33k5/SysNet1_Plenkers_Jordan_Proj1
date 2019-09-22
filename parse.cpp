#include "parse.hpp"

Parse::Parse(){
   param = new Param();
}

void Parse::parseCommand(std::string command){
   char token[command.length()];
   
   for (int i = 0; i < command.length(); ++i){
      token[i] = command[i];
   }
   
   param->setBackground(command);
	
   char *tok = strtok(token, " ,\n,\t");
   char *newTok = tok;
   
   string redirectCatch;
   while (newTok!= NULL){
      redirectCatch = newTok;
    	    	
      if (redirectCatch.find("<") == 0){
         param->setInput(redirectCatch);
         newTok = strtok(NULL, " ,\n,\t");
      
         if(!param->isValidToken(newTok)){
            break;
         }
      	
         redirectCatch = newTok;
      }
   	
      if (redirectCatch.find(">") == 0){
         param->setOutput(redirectCatch);
         newTok = strtok(NULL, " ,\n,\t");
         if(param->getBackground()){
            break;
         }
         if(!param->isValidToken(newTok)){
            break;
         }
      }
      
      else{
         param->setArg(redirectCatch);
         newTok = strtok(NULL, " ,\n,\t");
      }
   }
}
void Parse::printParams(){
   param->printParams();
}
