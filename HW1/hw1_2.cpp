#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/wait.h>

using namespace std;

int main()
{
          cout << "Main Process ID : " << getpid() << endl;
          pid_t pid;
          pid = fork(); //fork1
          if (pid == 0)
          {
                    cout << "Fork1. I'm the child " << getpid() <<",  my parent is " << getppid()  << ".  "<<endl;
                    pid = fork(); //fork2
                    if (pid == 0)
                    {
                              cout << "Fork2. I'm the child " << getpid() <<",  my parent is " << getppid()  << ".  "<<endl;
                              pid = fork(); //fork3
                              if (pid == 0)
                                        cout << "Fork3. I'm the child " << getpid() <<",  my parent is " << getppid()  << ".  "<<endl;
                              else if (pid > 0)
                                        wait(NULL);
                    }
                    else if (pid > 0)
                              wait(NULL);
          }
          else if (pid > 0)
          {
                    wait(NULL);
                    pid = fork(); //fork4
                    if (pid == 0)
                              cout << "Fork4. I'm the child " << getpid() <<",  my parent is " << getppid()  << ".  "<<endl;
                    else if (pid > 0)
                    {
                              wait(NULL);
                              pid = fork(); // fork6
                              if (pid == 0)
                                        cout << "Fork6. I'm the child " << getpid() <<",  my parent is " << getppid()  << ".  "<<endl;
                              else if (pid > 0)
                                        wait(NULL);
                    }
                    pid = fork(); //fork5
                    if (pid == 0)
                              cout << "Fork5. I'm the child " << getpid() <<",  my parent is " << getppid()  << ".  "<<endl;
                     else if (pid > 0)
                              wait(NULL);
          }
          return 0;
}
