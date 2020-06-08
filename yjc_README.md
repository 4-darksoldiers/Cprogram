1.将libgenebank.h拆分成genebank.c和genebank.h两个文件
2.为get_cds 增加一个参数FILE *fp用于从main.c中获取输入的文件指针，并为get_cds和initial_cds进行一定修改，增加参数CDS cds进行传参从而避免使用全局变量
3.将wyt_fasta.c拆分成fasta.c和fasta.h两个文件，并添加一些注释
4.删除make_fasta中对fp是否为空的判断;并为make_fasta函数增加一个参数char *outPutFile，用于从main.c获取输出文件名
5.删除sjc和wyt对CDS结构体的声明，统一于cds.h文件中，避免编译时出现冲突
6.创建main.c作为本程序的主函数源文件