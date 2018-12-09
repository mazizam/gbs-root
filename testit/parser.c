
#include<stdlib.h>
#include<stdio.h>
#include "list.h"
#include<string.h>



int accept(char c){
	return (c=='_'||(c>='A'&&c<='Z')||(c>='0'&&c<='9'))?c:0;
}
int add(char* buf,int i,char** accp){
if (buf[i]=='\0') return 0;
	**accp=buf[i];
		*accp=*accp+1;

return i+1;
}
int dollar(char* buf,int i,char** accp,char** envp,char* acc){
**accp='\0';

char* var=malloc(1024);

int j=++i;
	while((var[i-j]=accept(buf[i])))
	if (!((++i-j)%1024)) 
	var=realloc(var,((i-j)/1024+1)*1024);
if (i>=1024)
acc=realloc(acc,1023+strlen(getenv(var)));
strcat(acc,getenv(var));
free(var);
*accp=acc+strlen(acc);
//printf("%c %s\n",buf[i],acc);
		return i;

}


int move(int* state,char* buf,int i,char** accp,char** envp,char* acc){
	int s=*state;
if (s>100){
	*state=*state-100;
return add(buf,i,accp);
}
else if ((buf[i]=='>'||buf[i]=='<'||buf[i]=='|')&&s<2){
if (*accp-acc)return -1;
add(buf,i,accp);
return 0;

}
else switch(buf[i]){
case '$':if (!s)*state=1;return dollar(buf,i,accp,envp,acc);
case ' ':if (!s) return i+1;if(s==1)return 0;else return add(buf,i,accp); break;
case '\'':if (s<2)*state=2;else if(s==2)*state=1;else return add(buf,i,accp);break;
case '\"':if (s<2)*state=3;else if (s==3)*state=1;else return add(buf,i,accp);break;
case '\\':if (!s)s++;*state=s+100;break;
default: if (!buf[i]&&!s) return i+1;if (!s)*state=1;return add(buf,i,accp);
}
return i+1;


}

list_t* parser(char* read,char** envp){
   int* state=calloc(1,sizeof(int));
	   char* acc=calloc(1024,sizeof(char));
	   char** accp=malloc(sizeof(char*));
	   *accp=acc;
	   list_t* list;

list=list_init();
	        for(int i=0, j;i<=strlen(read);){

	        	if ((j=move(state,read,i,accp,envp,acc))<1)
	        	{i++;
i+=j;
**accp='\0';
*state=0;
	        		list_append(list,acc);
	        	acc=calloc(1024,sizeof(char));
	        	*accp=acc;
	        	}else i=j;

	        }
	        

	   free(state);
	   free(accp);
	   return list;
}
