# linux大作业报告

> 报告时间：2020/06/09
>
> 报告人：石京成 吴玥汀 叶佳晨 谢乐凡



## `genbank.c` 的编写

> 石京成 51811190073

- 获取哪些信息

  我在NCBI上下载了大作业示例的序列对应的fasta文件，其中除序列以外，还包括的信息分别是：

  verison:LT552780.1 

  location: complement(<9..1783)

  gene:ABSGL_05122.1 scaffold 6499

  于是在genbank文件中找到几个信息的对应位置，并根据location中是否有complement来判断是否为互补链

- 怎么提取

  提取的思路比较简单，首先是建立一个结构体保存需要获取的信息，然后对文件流循环使用fscanf函数直至获取到需要的字符串，需要注意的是gene的下一行就是location的信息，因此在获取gene的信息后需要使用两次fgets函数分别读掉gene所在行的剩余部分以及换行符

  另外，在获取到genbank文件中的对应信息后，还要对获取的字符串进行适当处理，即fasta文件中需要的gene的字符串在genbank文件中存在于两个引号之间，获取得到gene对应的字符串后需用strtok函数提取出引号中间的内容

  最后获取序列，思路也很简单，循环读取文件的字符直至终止符，并把'a'-'z'之间的字符全部存入序列中即可

- genbank.c内容

  最后写了三个函数，分别是对结构体进行初始化的的initial_cds、对gene对应字符串进行划分的line_div以及提取fasta文件所需信息的get_cds


## `fasta.c` 的编写

> 吴玥汀 518111910061

- 思路

  根据`genbank.c`中获得的材料，然后放到一个`.fa`文件中。先在`.fa`文件中放一个`>`，然后接着放提取的`version`,`genename`。

- 实现

  对于提取的`location`的形式为`<9..1705`。所以首先需要利用`isdigit`将非数字循环掉，接着提取第一个数字，然后再跳过`..`提取第二个数字。

  输出碱基时，需要利用`switch`。如果判断为互补链，则需要输出互补的碱基的大写字母。如果为非互补链，则需要输出其大写形式。

- 函数

  共有两个函数，`make_fasta`用来实现内容的搬运，`char2int`实现字符串到数字的转换。其中利用了`atoi`函数。因为当字符串不为数字时，`atoi`返回值为0，无法与字符`0`的结果区分，所以加了一步判断，若字符串不都是数字，则返回`-1`。


## `main.c` 的编写以及代码修改

> 叶佳晨 518111910024

- 将石京成的`libgenebank.h`拆分成`genebank.c`和`genebank.h`两个文件，后者声明前者实现。并标注出一些private函数和public函数
- 为`get_cds `增加一个参数`FILE *fp`用于从`main.c`中获取输入的文件指针，并为`get_cds`和`initial_cds`进行一定修改，增加参数`CDS *cds`进行传参从而避免使用全局变量
- 将吴玥汀的`wyt_fasta.c`拆分成`fasta.c`和`fasta.h`两个文件，后者声明前者实现。并标注出一些private函数和public函数和一些其他注释
- 删除`make_fasta`中对`fp`是否为空的判断；并为`make_fasta`函数增加一个参数`char *outPutFile`，用于从`main.c`获取输出文件名
- 删除石京成和吴玥汀对CDS结构体的声明，统一于`cds.h`文件中，避免编译时出现冲突
- 创建`main.c`作为本程序的主函数源文件

```c
//将genebank中cds序列提取出转成fasta文件的主函数cpp
//作者：叶佳晨
//创建日期：2020/06/08
//最后一次修改时间：2020/06/09
#include <stdio.h>
#include "cds.h"
#include "genbank.h"
#include "fasta.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Please use the following format to run this program:\n\tGenebank2Fasta <genebankfile you have> <fastafile you want>\n");
    }			//判断用户输入是否合理，若不合理则给予用户提示
    else
    {
        FILE *fp;
        fp = fopen(argv[1], "r");
        if (!fp)
            printf("[ERROR] Not found file %s", argv[1]);
        else
        {
            CDS cds;
            get_cds(&cds, fp);			//注意使用&cds传地址
            make_fasta(cds, argv[2]);
            printf("[FINISHED] Please check the information you want in file %s\n", argv[2]);
            fclose(fp);
        }
    }

    return 0;
}
```

## `Makefile` 的编写以及gdb过程

> 谢乐凡 516111910022

- 动态共享库的生成以及使用

  在网上查找信息后大概了解到动态共享库的意义以及使用方式

  使用自己的代码进行编写尝试，发现不知道如何生成链接然后通过'-l'进行函数库的调用
  无论是加入到系统默认的路径，或通过'-L'进行路径的指定
  最后的makefile只是直接对于动态库'.so'文件进行调用

  关于makefile的很多使用还很不熟练，中间的编译文件感觉不应该全放在当前文件夹，有些应该被清理掉

- debug过程

  初步合成到dev分支的程序主要存在两个地方的问题
  - get_cds函数进行参数传递时简单进行了传值，使得未对main函数中的参数进行改变
  - make_fasta函数进行坐标提取时逻辑存在疏漏


