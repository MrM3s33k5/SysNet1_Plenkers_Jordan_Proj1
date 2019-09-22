#include <iostream>
#include<stdio.h>
#include "parse.hpp"
#include <sys/types.h> 
#include <unistd.h> 

int main(int argc, char** argv) {
	Param param;
        Parse parse;
/*
	pid_t pid;
	pid = fork();
	if(pid < 0){
	   cout << "fail\n";
	}
	if (pid == 0){
	   execv(param.argumentVector[0],param.argumentVector);
	}
	else{
	   cout << "parent process\n";
	}
*/
	string options[] = {"-Debug", "ls", "-l", "grep", "cat", "exit"};
	
	//char* args[] = {"./slow" , NULL};
	//execv(args[0],args);
	
	cout << "\n>>> ";
	
	string command;
   	getline(cin, command);	
	 parse.parseCommand(command);

	execv(parse.param->argumentVector[0],NULL);

	string firstArg = param.argumentVector[0];

	cout <<parse.param->argumentVector[0] << endl;
	//parse.parseCommand(command);
	parse.printParams();
	
	return 0;
}
