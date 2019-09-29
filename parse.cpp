#include "parse.hpp"

Parse::Parse(){
   param = new Param();
}

Param* Parse::getParam(){
        return param;
}

int Parse::getBackground(){
   return param->getBackground();
}

void Parse::parseCommand(std::string command){
   char token[command.length()];

   strncpy(token, command.c_str(), sizeof token);
   token[sizeof token] = '\0';

   param->setBackground(command);

   char *tok = strtok(token, " ,\n,\t");
   char *newTok = tok;

   string redirectCatch;
   while (newTok!= NULL){
      redirectCatch = newTok;

      if(redirectCatch.find("&")){
            break;
         }

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

