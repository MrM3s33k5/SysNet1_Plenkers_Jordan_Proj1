#include <iostream>
#include <stdio.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h> 
#include <sys/wait.h> 
#include "parse.hpp"

#define PATH_MAX                250

/****************** Function Prototypes ******************/
void usage();
bool checkExitFlag(Parse localParse);
void checkFinishBackground(pid_t cpid, bool debugModeFlag);
void checkFinishForeground(pid_t cpid, bool debugModeFlag);


/**
 * Main function
 * 
 */
int main(int argc, char** argv) 
{
    Parse parse;
    bool debugModeFlag = false;
    bool exitFlag = false;
    pid_t cpid;
    string command;
    char* inFileName;
    char* outFileName;
    char cwd[PATH_MAX];
    char* inFilePath;
    char* outFilePath;
    char* tmpPath = cwd;

    
    // Check myshell command line arguments for input.
    // Only options are -debug, -help
    if(argc == 1)
    {
        debugModeFlag = false;
    }
    if(argc > 1)
    {
        // If user requests debug print statements, display them 
        // where available.
        if(strcmp(argv[1], "-debug") == 0 || strcmp(argv[1], "-Debug") == 0)
        {
            debugModeFlag = true;
        }
        // If user requests help menu, print it then exit.
        else if(strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "-Help") == 0)
        {
            usage();
            return 0;
        }
    }
    else if(argc > 2)
    {
        usage();
    }

    
    // Get our current working directory for reading/writing files and executing
    // local binary executables
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        if(debugModeFlag == true)
        {
            printf("Current working dir: %s\n", cwd);
        }
    } 
    // Print error if getcwd() fails
    else 
    {
        perror("getcwd() error");
        return 1;
    }
       

/**************  Loop to do stuff starts here ******************************/


    do{
        command = "\0";
        cout << "\n>>> ";
        getline(cin, command);	
        parse.parseCommand(command);
        exitFlag = checkExitFlag(parse);

        
        // If debug mode is enabled, print parameters
        if(debugModeFlag)
        {
            parse.printParams();
        }
        
                
        // pass arg1 to exec, pass argument vector
        // FIXME:  Original conditions for else didn't
        // work the I thought it would.  Figure 
        // something else out.  
        if(parse.param->getArgCount() > 0)
        {                   
            cpid = fork();
            
            // If fork instantiation fails
            if(cpid < 0)
            {
                cerr << "Error:  Fork failed, child not created" << endl;
            }
            // If cpid == 0, then it is child.  Else used 
            // to print message in debug mode. 
            else if(cpid == 0)
            {
		    outFileName = parse.param->getOutputRedirect();
                if(outFileName != NULL)
                {   strcpy(tmpPath, cwd);

                    //outFilePath = strcat(strcat(tmpPath, "/"), outFileName);
//                     //FIXME:  debug print statement
                    cout << "OutFile:  " << outFilePath << endl;
                    freopen(outFilePath, "w", stdout);
                    tmpPath = (char*) nullptr;
		    fclose(stdout);
                }
                
                if((inFileName = parse.param->getInputRedirect()))
                {
                    strcpy(tmpPath, cwd);
                    inFilePath = strcat(strcat(tmpPath, "/"), inFileName);
                    cout << "InFile:  " << inFilePath << endl;
                    freopen(inFilePath, "r", stdin);
                    tmpPath = (char*) nullptr;
                }
                
                // If execvp fails print error statemnt indicating
                // the return value.
                if((execvp((parse.param->argumentVector[0]), (parse.param->argumentVector))) < 0)
                {
                    cerr << "Command " << parse.param->argumentVector[0] << " not found, try again!" << endl;
                }
                if(debugModeFlag ==  true)
                {
                    cout << "Child running with PID:  " << cpid << "\n" << endl;
                }
                // If execv is successful, this shouldn't be reached. 127 means 
                // execl() failed, but normal termination.
                // FIXME:  Not really sure about this _exit(127)
                _exit(127);
                
            }
            // If cpid greater than zero, then it is parent.  Next load new program.
            else
            {
                // If running in background
                if(parse.param->getBackground() == 0)
                {
                    
                    if(debugModeFlag == true)
                    { 
                        cout << "\nRunning in foreground\n" << endl;
                    }       
                    // call function to run wait()
                    checkFinishForeground(cpid, debugModeFlag);
                }
                // If not running in background
                else if(parse.param->getBackground() > 0)
                {
                        
                    if(debugModeFlag == true)
                    {
                        cout << "\nRunning in background\n" << endl;
                    }
                    // call function to run waitpid()
                    checkFinishBackground(cpid, debugModeFlag);
                }
            }
        }
        else if(exitFlag)
        {
            cout << "Exiting Now!!!" << endl; 
        }
        // Catch everything else generate error message.
        else
        {
            if(debugModeFlag == true)
            {
                cerr << "\n\tError:\tThis shouldn't happen! Are you trying to break me?!" << endl;
                cerr << "\t\tThis is most likely an empty string, i.e. presseing\n\t\tenter without entering a command." << endl;
            }
        }
                
        
        parse.param->clearArgs();
        
    }while(!exitFlag); 
    
    
    // Call destructor.  Parse class instantiates the param
    // object, so parse destructor calls param destructor to
    // destroy param object.  
//     delete &parse;
//     delete parse.param;
    return 0;
}


// If user runs executable in background, this function is calld using
// waitpid.  If any errors occur, appropriate error statement is printed. 
void checkFinishBackground(pid_t cpid, bool debugModeFlag)
{
    int wstatus;
    pid_t pid;
    do
    {

        pid = waitpid(cpid, &wstatus,WNOHANG | WUNTRACED | WCONTINUED);    

        if(cpid == pid)
        {
            if(WIFEXITED(wstatus) && !WEXITSTATUS(wstatus)) 
            {
                cout << "WEXITSTATUS:  " << WEXITSTATUS(wstatus) << endl;                                                                     cout << "!WEXITSTATUS:  " << !WEXITSTATUS(wstatus) << endl;
                
                /* the program terminated normally and executed successfully */
                if(debugModeFlag)
                {
                    cout << "Process [ " << cpid << " ] executed normally and successfully!\n" << endl;
                }
            }
            else if(WIFEXITED(wstatus) && WEXITSTATUS(wstatus)) 
            {
                if(WEXITSTATUS(wstatus) == 127) 
                {
                    /* exec() failed */
                    cerr << "Error:  exec() failed!!" << endl;
                }    
                else 
                {
                    /* the program terminated normally, but returned a non-zero status */
                    switch(WEXITSTATUS(wstatus)) 
                    {
                        /* handle each particular return code that the program can return */
                    }
                }
            }
            else 
            {
                /* the program didn't terminate normally */
                cerr << "Error:  non-normal termination conditions!" << endl;
            }
        }
    
    }while(!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
}



// If user runs executable in foreground (or not background), this function
// is calld using wait().  If any errors occur, appropriate error statement
// is printed.  
void checkFinishForeground(pid_t cpid, bool debugModeFlag)
{
    int wstatus; 
    pid_t pid;
    
    pid = wait(&wstatus);
    if(pid == cpid)
    {
        if (WIFEXITED(wstatus) && !WEXITSTATUS(wstatus)) 
        {
            /* the program terminated normally and executed successfully */
            if(debugModeFlag == true)
            {  
                cout << "Process [ " << cpid << " ] executed normally and successfully!\n" << endl;
            }

        }
        else if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus)) 
        {
            if (WEXITSTATUS(wstatus) == 127) 
            {
                /* exec() failed */
                cerr << "Error:  exec() failed!!" << endl;
            }    
            else 
            {
                /* the program terminated normally, but returned a non-zero status */
                switch (WEXITSTATUS(wstatus)) 
                {
                    /* handle each particular return code that the program can return */
                }
            }
        } 
        else 
        {
            /* the program didn't terminate normally */
            cerr << "Error:  Non-Normal termination conditions!" << endl;
        }
    }
    else 
    {
        /* wait() failed */
        cerr << "Error:  wait() failed!!" << endl;
    }

}


// Function to check if user input is 'exit'. 
bool checkExitFlag(Parse localParse)
{
    if(strcmp(localParse.param->argumentVector[0], "exit") == 0 || 
       strcmp(localParse.param->argumentVector[0], "Exit") == 0 ||
       strcmp(localParse.param->argumentVector[0], "EXIT") == 0)
    {
        localParse.param->clearArgs();
        return true;
    }
    return false;
}


// Prints usage to the command line on user request or invalid command line 
// arguments. 
void usage()
{
    cout << "\nUsage:  myshell [OPTION]" << endl;
    cout << "Lanches myshell" << endl;
    cout << endl;
    cout << "-Debug, -debug \t\tLaunch myshell in debug mode." << endl;
    cout << "-Help, -help \t\tDisplay this help message.\n" << endl;
}


