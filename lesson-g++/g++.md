# g++ 基本用法

- gcc / g++ 全称 GNU Compiler Collections

  | gcc编译选项    | 说明                                                         |
  | -------------- | ------------------------------------------------------------ |
  | -E             | 预处理指定的源文件，不进行编译                               |
  | -S             | 编译制定的源文件，但不进行汇编                               |
  | -c             | 编译、汇编指定的源文件，但不进行链接                         |
  | -o             | 将文件编译链接为可执行文文件                                 |
  | -I [directory] | 指定Include的索引目录                                        |
  | -g             | 在编译的时候，生成调试信息，该程序可以被调试程序执行         |
  | -D             | 在程序编译的时候，指定一个宏                                 |
  | -w             | 不生成任何警告信息                                           |
  | -Wall          | 生成所有警告信息                                             |
  | -On            | n的取值范围：0~3。编译的优化选项的4个级别，0没有优化，1为缺省值，3优化级最高 |
  | -l             | 在程序编译时指定用的库                                       |
  | -L             | 编译的时候搜索库的路径                                       |
  | -fpic          | 生成与位置无关的代码                                         |
  | -shared        | 生成共享目标文件，通常用于建立共享库                         |
  | -std           | 指定C标准                                                    |