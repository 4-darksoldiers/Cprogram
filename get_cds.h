#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef __GET_CDS_H__
#define __GET_CDS_H__
#define MAX 100

struct CDS{
    char *version;
    char *gene;
    char *location;
    char *sequence;
    int iscomplement;
};

struct CDS cds;

void initial_cds(){
    cds.version = (char*)malloc(MAX*sizeof(char));
    cds.location = (char*)malloc(MAX*sizeof(char));
    cds.gene = (char*)malloc(MAX*sizeof(char));
    cds.sequence = (char*)malloc(10000*sizeof(char)); 
    cds.iscomplement = 0;  
}

void line_div (char *str, char *line[]) {
   const char s[] = "\"";
   char *token;
   int i = 0;

   /* 获取第一个子字符串 */
   token = strtok(str, s);
   
   /* 继续获取其他的子字符串 */
   for (; token != NULL; i ++)
   {
       strcpy(line[i], token);
       token = strtok(NULL, s);
   }
}

void get_cds(){
    FILE *fp = NULL;
    char c, buf[100];
    char *line[3];
    int i,j = 0;
    for(; i < 3; i++)
        line[i]=(char*)malloc(100*sizeof(char));
    initial_cds;
    
    fp = fopen("sequence.gb","r");
    fscanf(fp, "%s", buf);
    while( strcmp(buf, "VERSION" ) != 0 )                       /*提取version，如LT552780.1*/
        fscanf(fp, "%s", buf);
    fscanf(fp, "%s", cds.version);

    while( strcmp(buf, "gene" ) != 0 )                       /*提取location，如complement(<9..1783)*/  
        fscanf(fp, "%s", buf); 
    fscanf(fp, "%s", cds.location);
    
    if( strstr(cds.location, "complement") )                   /*判断是否为互补链*/
        cds.iscomplement = 1;
    
    fgets(buf, 100, fp);                                       
    fgets(buf, 100, fp);                                      /*两个fgets分别用于读掉上一行剩下的部分（空格）和换行符*/
    line_div(buf, line);                                      /*提取gene，如ABSGL_05122.1 scaffold 6499*/ 
    strcpy(cds.gene, line[1]);

    while( strcmp(buf, "ORIGIN" ) != 0 )                      
        fscanf(fp, "%s", buf);
    
            /*提取序列，序列为小写，剔除空格和数字，未分行*/
    while(!feof(fp)){
        c = fgetc(fp);
        if( c >= 'a' && c <= 'z'){
            cds.sequence[j] = c;
            j++;
        }
    }
    
    fclose(fp);
}

#endif