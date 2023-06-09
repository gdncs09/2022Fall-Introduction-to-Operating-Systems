#include<iostream>
#include<unistd.h>
#include<vector>
#include<string>
#include<cstring>
#include<fcntl.h>
#include<sys/wait.h>
#define MAX_LINE 80
using namespace std;

int main(void)
{
	int should_run = 1;
	vector<string> arg;
	string tmp;
	vector<char*> argv_t;
	char **argv;
	char buf[80];
	int n;
	int argc;
	int mode;
	pid_t pid;
	bool has_and;

          int start_point = 0;
	while(should_run){
		cout<<"osh>";
		fflush(stdout);
		n = read(STDIN_FILENO, buf ,80);
		for(int i=0;i<n;i++){
			if(buf[i]==' '||i==n-1){
				if(tmp.size()>0)
                                                  arg.push_back(tmp);
				tmp = "";
			}
			else{
				tmp = tmp + buf[i];
			}
		}
		argc = arg.size();
		argv = new char*[argc+1];
		for(int i=0;i<argc;i++){
			argv[i]=new char[arg[i].size()];
			strcpy(argv[i], arg[i].c_str());
		}
		argv[argc] = new char;
		argv[argc] = NULL;
                    /**
		* your code!
		* After reading user input, the step are:
		* (1) fork a child process using fork()
		* (2) the childcd  process will invoke execvp()
		*/
                    if (strcmp(*argv, "exit") == 0)
                    {
                              return 0;
                    }

                    pid = fork();
                    if (pid < 0)
                    {
                              cout << "Fork Error!" << endl;
                              exit(1);
                    }
                    if (pid == 0)
                    {
                              if (execvp(*argv, argv) < 0)
                                        cout << "Command Error!" << endl;
                              exit(1);
                    }
                    else if (pid > 0)
                    {
                              wait(NULL);
                    }

                    while (!arg.empty())
                    {
                              arg.pop_back();
                    }

		argv_t.clear();
		for(int i=0;i<argc;i++){
			delete [] argv[i];
		}
		delete argv;
	}
	return 0;
}

