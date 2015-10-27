文件夹结构：
  根目录 2014310618_李雪_homework1
	|-- readme.txt
		对提交的文件进行说明
	|-- bin(子目录)
		包含编译出的可执行文件和实验数据
	|-- src(子目录)
		包含源程序

编程语言: C++

编译工具: GNU GCC Compiler

运行环境: 
  处理器：Intel(R) Core(TM) i7-4790 CPU @ 3.60GHz 
  内存：8GB
  操作系统：Windows 7 旗舰版

特征提取：
  1. 分词：只把字母、数字、连接符视为单词的一部分，其他字符视为单词间的分隔。
  2. 特征选取：将每一个单词的出现频率作为一维特征。
  3. 特征提取：统计每一文档中每个单词(用编号表示)的出现频率作为该文档的特征向量。
 
运行方法:
  1. 运行bin\process.exe文件，从同目录下的dataset文件夹下读入数据，将处理后的文件输出到同目录下的processed_data文件夹中。
  2. 运行bin\task.exe文件，从同目录下的processed_data文件夹下读入数据，将每个测试组的准确率、召回率、F1分数以及最后的平均性能输出到控制台中。

性能评价：
设K=100时，运行约20分钟
  average precision: 0.920
  average recall: 0.940
  average f1: 0.935
设K=20时，运行约4分钟（当前设置）
  average precision: 0.780
  average recall: 0.894
  average f1: 0.832
设K=5时，运行约1分钟
  average precision: 0.618
  average recall: 0.924
  average f1: 0.741

