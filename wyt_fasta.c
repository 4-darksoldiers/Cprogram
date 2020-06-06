//put information into a fasta file
//#include <stdio.h>
#include <ctype.h>
#include "get_cds.h"

//make a fasta file containing CDS information
void make_fasta(struct CDS cds){
  int char2int(char *num);
  
  FILE *fp;   //open fasta
  int num1,num2,c,i=0,j;  //location
  char str1[100],str2[100];
  
  fp=fopen("information.fa","w");
  if(fp==NULL){
    printf("ERROR:can not create *.fa\n");
    exit(0);
  }
  fputs(">",fp);
  fputs(cds.version,fp);  //put version:like LT552780.1 into file
  fputs(" ",fp);          //space
  fputs(cds.gene,fp);
  fputs("\n",fp);
  while(!isdight(c=cds.location[++i]));//skip front like:complement(<
  while(isdigit(c=cds.location[++i])){ //get str1
    j=0;
    str1[++j]=c;
      }
  str1[j]='\0';
  i+=2; //skip ..
    while(isdigit(c=cds.location[++i])){
    j=0;
    str2[++j]=c;
      }
  str2[j]='\0';
  
  num1=char2int(str1);
  num2=char2int(str2);

  if(num2>num1)
    {
      int tmp;
      tmp=num2;
      num2=num1;
      num1=tmp;
    }

 
  if(cds.iscomplement==1)
    for(i=num1-1,j=0;i<num2;i++){
      j++;
       switch(cds.sequence[i]){
       case "a":
	 fputs("T",fp);break;
       case "t":
	 fputs("A",fp);break;
       case "c":
	 fputs("G",fp);break;
       case "g":
	 fputs("C",fp);break;
       }
       if(j==50) //50 words need change line
	 {fputs("\n",fp);j=0;}
    }
  if(cds.iscomplement==0)
     for(i=num1-1,j=0;i<num2;i++){
      j++;
      fputs(toupper(cds.sequence[i]),fp);
       if(j==50) //50 words need change line
	 {fputs("\n",fp);j=0;}
     }
  exit(1);
}

//change char to int
int char2int(char *num)
{
  int i,result;
  for(i=0;i<strlen(num);i++)
    {
      if(!isdigit(num[i]))
	return -1;
       
      result=atoi(num);
      return result;
    }
}
