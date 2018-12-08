#include <stdlib.h>
#include "list.h"
#include <stdio.h>

struct list_elem *first(list_t *list, char *data);


list_t   *list_init (){
list_t *l=malloc(sizeof(list_t));
*l=(list_t){NULL,NULL,0};

return l;
}

struct list_elem *list_insert (list_t *list, char *data){
    if (list==NULL) return NULL;
list->size=list->size+1;
    if (list->first==NULL) return first(list,data);
struct list_elem *element_to_add=malloc(sizeof(struct list_elem));
*element_to_add=(struct list_elem){list->first,data};
list->first=element_to_add;
return element_to_add;
}

struct list_elem *list_append (list_t *list, char *data){
      if (list==NULL) return NULL;
list->size=list->size+1;
 if (list->last==NULL) return first(list,data);
struct list_elem *element_to_add=malloc(sizeof(struct list_elem));
*element_to_add=(struct list_elem){NULL,data};
list->last->next=element_to_add;
list->last=element_to_add;
return element_to_add;

}

int list_remove (list_t *list, struct list_elem *elem){
      if (list==NULL||elem==NULL) return -1;
struct list_elem * element=list->first;
while(element!=NULL&&element!=elem){
if (element->next==elem){
element->next=elem->next;
if (list->last==elem) list->last=element;
element=elem;
}else
element=element->next;
}

if (element!=NULL) {
list->size=list->size-1;
    if (list->first==element)list->first=element->next;
if (list->last==element)list->last=NULL; 

free(element);

return 0;}
return -1;
}

void  list_finit (list_t *list){
      if (list==NULL) return ;
struct list_elem *e, *element=list->first;
while(element!=NULL){
e=element->next;
free(element);
element=e;
}
free(list);
}

struct list_elem *list_find (list_t *list, char *data, int (*cmp_elem) (const char *, const char *)){
  if (list==NULL) return NULL;
struct list_elem * element=list->first;
while((element!=NULL)&&cmp_elem(data,element->data)!=0){
    element=element->next;
}
return element;
}

void   list_print (list_t *list, void (*print_elem) (char *)){
    if (list==NULL) return;
struct list_elem *element=list->first;
int i=0;
while(element!=NULL){
printf("%d:",++i);
print_elem(element->data);
printf("\n");
element=element->next;
}


}

void print_string(char *data){
    printf("%s",data);
}

struct list_elem *first (list_t *list, char *data){
struct list_elem* element=malloc(sizeof(struct list_elem));
*element=(struct list_elem){NULL,data};
list->first=element;
list->last=element;
return element;


}
//NULL at the end
char** toArray(list_t *list){
char** ar=calloc(list->size+1,sizeof(char*));
struct list_elem* elem=list->first;
int i=0;
while(elem){
ar[i++]=elem->data;
elem=elem->next;}
ar[i]=NULL;
return ar;

}

