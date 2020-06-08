//将genebank
//作者：叶佳晨
//创建日期：2020/06/08
//最后一次修改时间：2020/06/08
#include <stdio.h>
#include "cds.h"
#include "genbank.h"
#include "fasta.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        print("Please use the following format to run this program:\n\tGenebank2Fasta <genebankfile you have> <fastafile you want>");
    }
    else
    {
        FILE *fp;
        fp = fopen(argv[1], "r");
        if (!fp)
            printf("[ERROR] Not found file %s", argv[1]);
        else
        {
            CDS cds;
            get_cds(cds, fp);
            make_fasta(cds, argv[2]);
            printf("[FINISHED] Please check the information you want in file %s", argv[2]);
        }
    }
    return 0;
}