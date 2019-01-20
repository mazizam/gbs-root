#include "wildcard.h"

int size;

void pr(char* s) {
	printf("%s",s);
}
void cd(char** argv,char** envp){
char sss[200];
char* arg=argv[0];
if (argv[1]) {
printf("Usage : cd <dir>\n");
strerror(EINVAL);
return ;
} 
	char* ac;
if (arg){

	if (arg[0]=='/'){
		ac=calloc(1,strlen(arg));
	}
	else{
		ac=getcwd(sss,size+1+strlen(arg));
		int nsize=strlen(ac);
		size=size>nsize?nsize:size;
		strcat(ac,"/");
		size++;
	}

strcat(ac,arg);
if (chdir(ac)){
printf("cd : %s : %s\n",arg,strerror(errno));
return ;
}
size+=strlen(arg);
}
else printf("%s\n",getcwd(sss,size+10));

}

int test(char* path, char**argv,char** envp){
char* p=path,*next;

while(1){
next=strchr(p,':');
if (next) *next='\0';
p=strdup(p);
p=realloc(p,strlen(p)+1+strlen(argv[0]));
strcat(p,"/");
strcat(p,argv[0]);
execve(p,argv,envp);
if (next)p=next+1;
else break;
}
return -1;
}




int main(int argc,char** argv,char** envp){
size=strlen(getenv("PWD"));
	   char* read=malloc(1024);
	list_t* loe;

	   while(1){
	    printf("$ ");
fflush(stdin);
fflush(stdout);
	    int b=!((fgets(read,1025,stdin)!=NULL)&&strncmp(read,"exit\n",5));
read[strlen(read)-1]='\0';
loe=wildcard(read,envp);

char** argv=toArray(loe);
if (argv&&!strcmp(argv[0],"cd"))
	cd(argv+1,envp);
else if (fork()){
int error;
if (!wait(&error)) perror("wait");
}else
return test(getenv("PATH"),argv,envp);
list_finit(loe); 


if (b) break;

	} 

	   return 0;


}
