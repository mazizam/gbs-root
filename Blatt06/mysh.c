#include<stdlib.h>
#include<stdio.h>
#include "list.h"
#include<string.h>
#include <sys/wait.h>
#include <unistd.h>
list_t* parser(char* ,char** );

void pr(char* s) {
	printf("%s",s);
}

int test(char* path, char**argv,char** envp){
char* p=path,*next;
while((next=strchr(p,':'))){
*next='\0';
p=strdup(p);
strcat(p,"/");
strcat(p,argv[0]);
execve(p,argv,envp);
p=next+1;
}
return -1;
}

int main(int argc,char** argv,char** envp){


	   char* read=malloc(1024);
	list_t* loe;

	   while(1){
	    printf("$ ");
fflush(stdin);
fflush(stdout);
	    int b=!((fgets(read,1025,stdin)!=NULL)&&strncmp(read,"exit\n",5));
read[strlen(read)-1]='\0';
loe=parser(read,envp);
if (fork()){
int error;
if (!wait(&error)) perror("wait");
}else
return test(getenv("PATH"),toArray(loe),envp);
list_finit(loe); 


if (b) break;

	} 

	   return 0;


}
