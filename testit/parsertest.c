#include<stdlib.h>
#include<stdio.h>
#include "list.h"
#include<string.h>
list_t* parser(char* ,char** );

void pr(char* s) {
	printf("%s",s);
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
list_print(loe=parser(read,envp),pr);
list_finit(loe);
if (b) break;

	} 

	   return 0;


}
