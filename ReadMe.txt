
特征提取：
  1. 分词：只把字母、数字、连接符视为单词的一部分，其他字符视为单词间的分隔。
  2. 特征选取：将每一个单词的出现频率作为一维特征。
  3. 特征提取：统计每一文档中每个单词(用编号表示)的出现频率作为该文档的特征向量。
 
运行方法:
  1. process从同目录下的dataset文件夹下读入数据，将处理后的文件输出到同目录下的processed_data文件夹中。
  2. task，从同目录下的processed_data文件夹下读入数据，将每个测试组的准确率、召回率、F1分数以及最后的平均性能输出。

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


