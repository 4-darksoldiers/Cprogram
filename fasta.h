//作者：吴玥汀
/*修改：叶佳晨 2020/06/08
将wyt_fasta.c拆分成fasta.c和fasta.h两个文件，并添加一些注释*/
#ifndef FASTA_H
#define FASTA_H
#include "cds.h"

//public：
void make_fasta(CDS cds, char *file);

//private：
int char2int(char *num);

#endif