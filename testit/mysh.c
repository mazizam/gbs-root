#include<stdlib.h>
#include<stdio.h>
#include "list.h"
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
list_t* parser(char* ,char** );

void pr(char* s) {
	printf("%s",s);
}

void pri(char* s) {
	printf("%d",*((int*)s));
}

int test(char* path, char**argv,char** envp){
char* p=path,*next;
while(1){
next=strchr(p,':');
if (next) *next='\0';
p=strdup(p);
strcat(p,"/");
strcat(p,argv[0]);
execve(p,argv,envp);
if (next)p=next+1;
else break;
}
return -1;
}

char** setinout(list_t* loe){
struct list_elem* read=list_find(loe,"<",strcmp)
,*write=list_find(loe,">",strcmp);
//printf("%ld  %ld\n",read,write);
int datei,rw=(read&&write&&!strcmp(read->next->data,write->next->data));
if (rw)datei=open(read->next->data,O_RDWR
//,S_IWOTH|S_IROTH
);
if (read){
if(!rw)datei=open(read->next->data,O_RDWR
//,S_IROTH
);
dup2(datei,0);
list_remove(loe,read->next);
list_remove(loe,read);
}
if (write){
if (!rw)datei=open(write->next->data,O_RDWR
//,S_IWOTH
);
dup2(datei,1);
list_remove(loe,write->next);
list_remove(loe,write);
}
return toArray(loe);
}

int killall(list_t* loc){
while (loc->first){
int* pid=(int*)(loc->first->data);
list_remove(loc,loc->first);
kill(*pid,SIGKILL);
free(pid);
}
return -1;
}
int  parse2(list_t* loe,list_t* loc,char** envp){
test(getenv("PATH"),setinout(loe),envp);
//killall(loc);
//list_print(loe,pr);
return -1;
}



int fold_r(list_t* l,list_t* loc,char** envp,int pip[2])
{
//list_print(l,pr);
int* child=malloc(4);
pipe(pip);
struct list_elem* found=list_find(l,"|",strcmp);
list_t* left;
if (found)
{
	left=list_init();
	memcpy(left,l,sizeof(list_t));
	left->last=found->previous;
	if (!(left->last)) 
		killall(loc);//nothing on the left "$|...."
	else 
		left->last->next=NULL;
	resize(left);
	l->first=found->next;
	if (!(l->first)) 
		killall(loc);//nothing on the right "$....|"
	else 
		l->first->previous=NULL;


}else left=l;
//printf("end found");

if ((*child=fork())>=0)
{
	if (*child){
		list_append(loc,(char*)child);
		dup2(pip[0],0);
		if (found)
			{
			close(pip[1]);
			int r= fold_r(l,loc,envp,pip);
		 	close(pip[0]);
return r;
			}
			return 0;
		}
	else{
		if (found) dup2(pip[1],1);
		return parse2(left,loc,envp);

		}	
}


return killall(loc);

}


int main(int argc,char** argv,char** envp){


	   char* read=malloc(1024);
	list_t* loe,*pros=list_init();

int error,pip[2]={0,1};
	dup2(0,3);
	dup2(1,4);
	   while(1){
	    printf("$ ");
dup2(3,0);
dup2(4,1);
fflush(stdin);
fflush(stdout);
	    int b=!((fgets(read,1025,stdin)!=NULL)&&strncmp(read,"exit\n",5));
if (b) break;
read[strlen(read)-1]='\0';
loe=parser(read,envp);

if ((error=fold_r(loe,pros,envp,pip))){
printf("%d",error);
return error;}
while(pros->first){
if (!wait(&error)) perror("wait");
list_remove(pros,pros->first);
}




	} 

	   return 0;


}
