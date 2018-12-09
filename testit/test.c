#include<stdlib.h>
#include<stdio.h>
#include "list.h"
#include<string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
int main(int argc,char** argv){
int n=atoi(argv[1]);
int *ar=malloc(n*4);
int fd= open("testinput",O_WRONLY);
dup2(fd,1);
while(fork()){

printf("parent %d\n",getpid());
if (!n--){
while (n++-atoi(argv[1]))
wait(NULL);
return 0;
}
ar[n]=n;
}
for(int i=0;i<atoi(argv[1]);i++)
printf("n[%d]=%d   child %d\n",i,ar[i],getpid());
}





