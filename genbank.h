//作者：石京成
/*修改者：叶佳晨 修改时间：2020/06/08
将libgenebank.h拆分成genebank.c和genebank.h两个文件，并对一些源代码进行修改*/
#ifndef __GET_CDS_H__
#define __GET_CDS_H__
#define MAX 100
#include "cds.h"

//private function
void initial_cds(CDS *cds);              //初始化结构体
void line_div(char *str, char *line[]); //主要用于提取cds.gene，把含有引号的字符串划分，提取引号内的字符串

//public function
void get_cds(CDS *cds, FILE *file); //依次提取结构体中的各内容

#endif