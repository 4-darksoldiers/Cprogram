//定义一个结构体表示CDS序列信息
//作者：叶佳晨
//创建日期：2020/06/08
//最后一次修改时间：2020/06/08
#ifndef CDS_H
#define CDS_H

typedef struct CDS
{
    char *version;    //版本信息
    char *gene;       //基因序列
    char *location;   //区间范围
    char *sequence;   //CDS序列
    int iscomplement; //是否是互补链
} CDS;

#endif