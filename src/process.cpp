#include <iostream>
#include <fstream>
#include <cstdio>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <string>
#include <set>
#include <map>

using namespace std;
const int TypeNum = 2; //文档类别数
const int Length = 50; //文档路径最长长度
const int Maxlength = 100000; //输出一行最大长度
char TypeName[TypeNum][10] = {"baseball", "hockey"}; //文档类别名称
map <string, int> word; //单词到整数的映射
int word_count = 0; //总单词数即特征维度
int doc_count[2] ; //文档数


bool valid(char ch) //判断一个字符是否属于一个单词
{
    if (ch=='\'' || ch=='-') return true;
    if (ch>='0' && ch<='9') return true;
    if (ch>='a' && ch<='z') return true;
    if (ch>='A' && ch<='Z') return true;
    return false;
}

void insert(int &m, map<int, int> &count, string w) //用一个单词更新统计结果
{
    m++;
    if (word[w] == 0)
        word[w] = ++word_count;
    count[word[w]]++;
}

void process(ifstream &icin, int type) //预处理一个标号为type_id的文档
{
    doc_count[type]++;
    map<int, int> count;
    int m = 0;
    char ch;
    string now="";
    icin.unsetf(ios::skipws);
    while (icin>>ch)
    {
        if (valid(ch)) now+=ch;
        else
        {
            if (now!="") insert(m, count, now);
            now="";
        }
    }
    if (now!="") insert(m, count, now);
    printf("%d ",type);
    for (map<int,int>::iterator it = count.begin(); it != count.end(); it++)
        printf(" %d:%lf", it->first, it->second*1.0/m);
    printf("\n");
}

void spilt(char * out_path, int doc_count) //平均分成五份
{
    freopen(out_path, "r", stdin);
    int n = doc_count / 5, r = doc_count % 5, now = 1, tar = n + (now <= r);
    char new_path[Length];
    strcpy(new_path, out_path);
    strcat(new_path, "_part1");
    freopen(new_path, "w", stdout);
    char str[Maxlength];
    for (int i = 1; i <= doc_count; i++)
    {
        if (i > tar)
        {
            now++;
            tar += n + (now <= r);
            new_path[strlen(new_path)-1] = now + '0';
            freopen(new_path, "w", stdout);
        }
        gets(str);
        cout<<str<<endl;
    }
    
}

int main()
{
    char out_path[Length] = "processed_data/data0";
    for (int type=0; type < TypeNum; type++)
    {
        out_path[strlen(out_path) - 1] = '0' + type;
        freopen(out_path, "w", stdout);
        DIR *dir;
        struct dirent *ptr;
        char path[Length] = "dataset/";
        strcat(path, TypeName[type]);
        strcat(path, "/");
        dir = opendir(path);
        while ((ptr = readdir(dir)) != NULL) //枚举需要处理的文档
        {
                if (ptr->d_name[0]=='.') continue;
                ifstream icin;
                char file_path[Length];
                strcpy(file_path, path);
                strcat(file_path, ptr->d_name);
                icin.open(file_path);
                process(icin, type);
        }
        closedir(dir);
        spilt(out_path, doc_count[type]);
    }
    //printf("%d\n",word_count);
    return 0;
}