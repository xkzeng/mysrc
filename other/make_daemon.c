#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

int RunAsDaemon(void)
{
  pid_t pid;
  int fd = -1, nFdCountMax = 0;
  
  pid = fork();
  if(pid < 0)
  {
    printf("fork() failed: %d  %s\n", errno, strerror(errno));
    return -1;
  }
  
  if(pid > 0)
  {
    exit(0);
  }
  
  if(setsid() < 0)
  {
    return -2;
  }
  
  pid = fork();
  if(pid < 0)
  {
    printf("fork() failed: %d  %s\n", errno, strerror(errno));
    return -3;
  }
  
  if(pid > 0)
  {
    exit(0);
  }
  
  signal(SIGHUP, SIG_IGN);
  signal(SIGTTOU,SIG_IGN);
  signal(SIGTTIN,SIG_IGN);
  signal(SIGTSTP,SIG_IGN);
  signal(SIGHUP, SIG_IGN);
  signal(SIGCHLD, SIG_IGN);
  
  chdir("/");
  umask(0);
  
  nFdCountMax = getdtablesize();
  for(fd = 0; fd < nFdCountMax; fd++)
  {
    if(fd != 1 && fd != 2)
    {
      close(fd);
    }
  }
  return 0;
}

int main(int argc,char** argv)
{
  int i = 0;
  
  if(RunAsDaemon() < 0)
  {
    printf("Set as Daemon failed.\n");
  }
  
  for(i = 0; i < 10; i++)
  {
    sleep(10);
    printf("SubProcess: %d\n",i);
  }
  exit(0);
}