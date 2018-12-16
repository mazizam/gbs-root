#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <poll.h>
#include <string.h>
#include<sys/socket.h>
#include "list.h"
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include<pthread.h>
#include <math.h>
#define myport 44445
 int secs=0,check=1;
int dif(struct timeval later,struct timeval now){
int secs=later.tv_sec-now.tv_sec
,microsecs=later.tv_usec-now.tv_usec;
return round(secs*1000+microsecs/1000.);

}
void handler(int k){
if (secs==check++) exit(0);
signal(SIGALRM,handler);
}
void setalarm(){
secs++;
alarm(10);

}
void add(list_t* l,connection* c){
gettimeofday(&(c->timeout),NULL);
c->timeout.tv_sec=c->timeout.tv_sec+5;
list_append(l,(char*)c);
}

void* accepting(void* list)
{
list_t* l=(list_t*)list;
int sd=*(int*)(l->first->data);
list_remove(l,l->first);
int i=10;
while(i--)
	{
	connection* c=malloc(sizeof(connection));
	c->sd=accept(sd,NULL,NULL);
	add(l,c);
	}
pthread_exit(0);
}

struct pollfd* listtopollfd(list_t* l){
struct pollfd* pfd=calloc(l->size,sizeof(struct pollfd));
struct list_elem* e=l->first;
for(int i=0;i<l->size;i++,e=e->next)
pfd[i]=(struct pollfd){((connection*) (e->data))->sd,POLLIN};
return pfd;

}
int main(int argc,char** argv,char** envp){
signal(SIGALRM,handler);
setalarm();
char buf[1024];
list_t* list=list_init();
struct sockaddr_in sin;
int* sd=malloc(4);
*sd=socket(AF_INET,SOCK_STREAM,0);

sin=(struct sockaddr_in){AF_INET,htons(myport)};
sin.sin_addr.s_addr=INADDR_ANY;
bind(*sd,(struct sockaddr *)&sin,sizeof(sin));
if (listen(*sd,10)){
perror("error");
return -1;
}
pthread_t* accepter=malloc(sizeof(pthread_t));
list_append(list,(char*)&sd);
pthread_create(accepter,NULL,accepting,(void*)list);
struct timeval current;
connection* actual;
int p;
struct pollfd* pfds;
while(1)
	{

		if (list->first)
		{
			gettimeofday(&current,NULL);
			if((p=poll(pfds=listtopollfd(list),list->size,dif(((connection*)(list->first->data))->timeout,current)))>0)
			{
				struct list_elem* tmp,*element=list->first;
				for(int i=0,j=0;j<p;i++,element=element->next)
					if (pfds[i].revents!=0)
					{j++;
					add(list,actual=((connection*)(element->data)));
					tmp=element;
					element=element->previous;
					list_remove(list,tmp);

						if ((p=recv(pfds[i].fd,buf,sizeof(buf),0))<0)
							return -1;
						else if ((p=send(pfds[i].fd,buf,p,0))<0)
							return -1;

					}
				setalarm();
			}
			else if (!p)
			{
				actual=(connection *)(list->first->data);
				list_remove(list,list->first);
				close(actual->sd);
			}
			else exit(-1);
		}	
	}

}
