//作者：吴玥汀
/*修改：叶佳晨 2020/06/08
将wyt_fasta.c拆分成fasta.c和fasta.h两个文件，并对一些源代码进行修改，删除make_fasta中对fp是否为空的判断;
并为make_fasta函数增加一个参数char *outPutFile，用于从main.c获取输出文件名*/
//put information into a fasta file
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "fasta.h"

//public:
void make_fasta(CDS cds, char *outPutFile) //make a fasta file containing CDS information
{
    int char2int(char *num);

    FILE *fp;                    //open fasta
    int num1, num2, c, i = 0, j; //location
    char str1[100], str2[100];

    fp = fopen(outPutFile, "w");

    fputs(">", fp);
    fputs(cds.version, fp); //put version:like LT552780.1 into file
    fputs(" ", fp);         //space
    fputs(cds.gene, fp);
    fputs("\n", fp);
    while (!isdigit(c = cds.location[++i]))
        ; //skip front like:complement(<
    j=0;
    while (isdigit(c = cds.location[i]))
    { //get str1
        str1[j++] = c;
	i++;
    }
    str1[j] = '\0';
    i += 2; //skip ..
    j=0;
    while (isdigit(c = cds.location[i]))
    {
	i++;
        str2[j++] = c;
    }
    str2[j] = '\0';

    num1 = char2int(str1);
    num2 = char2int(str2);

    if (num2 < num1)
    {
        int tmp;
        tmp = num2;
        num2 = num1;
        num1 = tmp;
    }

    if (cds.iscomplement == 1)
        for (i = num1 - 1, j = 0; i < num2; i++)
        {
            j++;
            switch (cds.sequence[i])
            {
            case 'a':
                fputs("T", fp);
                break;
            case 't':
                fputs("A", fp);
                break;
            case 'c':
                fputs("G", fp);
                break;
            case 'g':
                fputs("C", fp);
                break;
            }
            if (j == 50) //50 words need change line
            {
                fputs("\n", fp);
                j = 0;
            }
        }
    if (cds.iscomplement == 0)
        for (i = num1 - 1, j = 0; i < num2; i++)
        {
            j++;
            fputc(toupper(cds.sequence[i]), fp);
            if (j == 50) //50 words need change line
            {
                fputs("\n", fp);
                j = 0;
            }
        }
    fputs("\n",fp);
    fclose(fp);
    return;
}

//private:
int char2int(char *num) //change char to int
{
    int i, result;
    for (i = 0; i < strlen(num); i++)
    {
        if (!isdigit(num[i]))
            return -1;
    }
        result = atoi(num);
        return result;
 
}
