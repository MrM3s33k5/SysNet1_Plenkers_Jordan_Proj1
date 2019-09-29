#include <iostream>
#include<stdio.h>
#include <stdlib.h>
#include "parse.hpp"
#include <sys/types.h> 
#include <unistd.h>
#include<sys/wait.h>

#define FALSE 0;
#define TRUE 1;
int isDebug = FALSE;

int main(int argc, char** argv) {
	Param param;
        Parse parse;
	string command;

	pid_t pid;
	int status;
	
	string options[] = {"exit", "-Debug", "ls", "-l", "grep", "cat"};
	while(1){
	//pid = fork();
	parse.getParam()->clearArgs();
	cout << "\n>>> ";
        getline(cin, command);
        parse.parseCommand(command);

	if(command.substr(0,5) == options[0]){
	   cout << "Exiting..." << endl;
	   exit(0);
	}
	
	 pid = fork();

	if(pid < 0){
	   cout << "Failure with fork()\n";
	}

	if (pid > 0){ //parent
	   cout << "parent process\n";
	   if(parse.getBackground()){ //sets background process
	      //wait(NULL); //wait for child
	     continue; // waitpid(pid, &status, WNOHANG);
	   }

	   else{
		wait(NULL);
	   }
	}
	else{ //child
           //fflush(NULL);
           //cout << "\n>>> ";
           //getline(cin, command);
	   cout << "child process\n ";
	   parse.printParams();
           execv(parse.getParam()->argumentVector[0],NULL);
}
	}
	return 0;
}
