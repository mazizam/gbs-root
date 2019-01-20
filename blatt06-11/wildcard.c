#include "wildcard.h"

void pri(char* s) {
	printf("%s",s);
}
char* left,*word,*right;
void wildparse(char* data){
char* c=strchr(data,'*'),*r;

r=strchr(c,'/');
if (r){
right=strdup(r);
*r=0;
}
else right="";
while(c>=data&&(*(--c))!='/');
word=strdup(++c);
*c=0;
left=data;
}
char * combine(const char* name){
char* c=calloc(1,strlen(left)+strlen(name)+strlen(right));
	strcat(c,left);
	strcat(c,name);
	strcat(c,right);
	return c;
}
int filter(const struct dirent * d){
	char *ll,*rr;
	char* myword=strdup(word);
		rr=strchr(myword,'*');
		*rr=0;
		rr++;
		ll=myword;
	int b=strncmp(d->d_name,ll,strlen(ll));
	
	
	if (b) {free(myword);return 0;}
	ll=strdup(d->d_name+strlen(ll));
	int x=strlen(ll)-strlen(rr);
	if (x<0) {free(ll);free(myword);return 0;}
	b=strcmp(ll+x,rr);
	if (b) {free(ll);free(myword);return 0;}
	free(ll);
	free(myword);
	b= access( ll=combine(d->d_name),F_OK);
	//printf ("%s %d\n",d->d_name,b);
	free(ll);
	return !b&&(!(d->d_name[0]=='.')||!strcmp(d->d_name,".")||!strcmp(d->d_name,".."));
}



list_t* wildcard(char* read,char** envp){

	list_t* parsed=parser(read,envp);
	struct list_elem* e=parsed->first;
	while(e&&!strchr(e->data,'*'))
		e=e->next;
	if (!e||e==parsed->first)return parsed;
	char* dir=e->data;
	list_remove(parsed,e);
	struct dirent **nl;
	
	wildparse(dir);

	int n=scandir((!*left)?".":left,&nl,filter,alphasort);

	if (n<=0) return parsed;
	
	for(int i=0;i<n;i++)
		list_append(parsed,combine(nl[i]->d_name));
	return parsed;

}