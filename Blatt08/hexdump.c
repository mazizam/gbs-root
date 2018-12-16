#include "hexdump.h"
void rec(char*,int,char*,int*);
void left(int);
void finish(int,char*,int*);
int valid(char);
void repeat(int);
static int len;
static FILE *f;

void hexdump (FILE *output, char *buffer, int length){
f=output;
  len=length;
  char* input=buffer;
  int* index=malloc(4);
  *index=0;
rec(input,0,malloc(length),index);
free(index);
printf("\n");


}
void rec(char* current,int  nb,char* str,int *done){
if (nb%16==0){
  left(nb);
}
if (*current=='\0'){
fprintf(f," 00");
str[*done]='.';
*done+=1;
  finish(nb%16,str,done);

free(str);
  return;}

  else {
int pr=*current;
if(valid(*current))
str[*done]=*current;
else {str[*done]='.';
pr&=0xff;
}
fprintf(f," %02x",pr);
*done+=1;
    if(nb%16==15) finish(15,str,done);
  }

  rec(++current,++nb,str,done);
}
void left(int nb){
  fprintf(f,"%06x :",nb);
}
void finish(int nbm,char* str,int *done){
str[*done]='\0';
*done=0;
repeat(3*(16-nbm));
fprintf(f,"%s\n",str);
strcpy(str,"");
}
int valid(char c){
  return c>=32&&c<=126;
}
void repeat(int n){
  for(int i=0;i<n;i++)
  fprintf(f," ");
}
