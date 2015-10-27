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
const int GroupNum = 5;
const int Length = 50; //文档路径最长长度
const int Maxlength = 100000; //一行最大长度
const int M = 31000; //维度
const double alpha = 1; //步长
const int K = 20; //学习次数
double w[M]; //参数
double f1_mean = 0, precision_mean = 0, recall_mean = 0; //平均f1分数
int true_pos, fal_pos, true_neg, fal_neg;

void init() //初始化变量
{
    true_pos = 0;
    fal_pos = 0;
    true_neg = 0;
    fal_neg = 0;
    memset(w,0, sizeof(w));
}

double h(double * x, double &sum) //计算h值
{
    sum = 0;
    for (int i = 0; i < M; i++)
        sum += w[i] * x[i];
    double res = 1 / (1 + exp(-sum));
    return res;
}

int sign(double x) //根据函数值分类
{
    if (x < 0.5)
        return 0;
    else
        return 1;
}

void read(char *str, int &id, double *x) //读入一个样本
{
    int p;
    double q;
    sscanf(str, "%d", &id);
    while (true)
    {
        str = strchr(str, ' ');
        if (str)
        {
            str++;
            if (!str) break;
            sscanf(str, "%d:%lf", &p, &q);
            x[p] = q;
        }
        else
            break;
    }
}

void study(char* str) //学习一个样本
{
    double x[M];
    int id;
    memset(x, 0, sizeof(x));
    read(str, id, x);
    double sum, hw = h(x, sum);
    for (int d = 0; d < M; d++)
    {
        double deta = alpha * (id - hw) * x[d];
        w[d] += deta;
        sum += deta * x[d];
        hw = 1 / (1 + exp(-sum));
    }
}


void study(ifstream &icin) //学习样本
{
    char str[Maxlength];
    while (icin.getline(str, Maxlength))
    {
        study(str);
    }
}

void check(char * str) //对一个样本进行测试
{
    double x[M], sum;
    int id;
    memset(x, 0, sizeof(x));
    read(str, id, x);
    int res = sign(h(x, sum));
    if (id == 1)
    {
        if (res == 1) true_pos++; else fal_neg++;

    } else
    {
        if (res == 1) fal_pos++; else true_neg++;
    }

}

void check(ifstream &icin) //对样本进行测试
{
    char str[Maxlength];
    while (icin.getline(str, Maxlength))
    {
        check(str);
    }
}

void output(int t) //输出本组测试结果
{
    //cout << true_pos << ' '<<fal_pos<<' '<<true_neg << ' ' <<fal_neg<<endl;
    double precision = true_pos * 1.0 / (true_pos + fal_pos);
    double recall = true_pos * 1.0 / (true_pos + fal_neg);
    double f1 = 2.0 * precision * recall / (precision + recall);
    printf("Test Group: %d\n", t);
    printf("  Precision = %lf\n", precision);
    printf("  Recall = %lf\n", recall);
    printf("  F1 score = %lf\n", f1);
    f1_mean += f1 / 5;
    precision_mean += precision / 5;
    recall_mean += recall / 5;
}

int main()
{
    for (int test_group = 1; test_group <= GroupNum; test_group++) //枚举测试组
    {
        init();
        char path[Length] = "processed_data/data0_part1";
        ifstream icin;
        for (int k = 1; k <= K; k++)
          for (int group = 1; group <= GroupNum; group++)
             for (int type = 0; type <= 1; type++)
                  if (group != test_group)
                  {
                      path[strlen(path) - 1] = group + '0';
                      path[strlen(path) - 7] = type + '0';
                      icin.open(path);
                      study(icin);
                      icin.close();
                  }
        path[strlen(path) - 1] = test_group + '0';
        path[strlen(path) - 7] = '0';
        icin.open(path);
        check(icin);
        icin.close();
        path[strlen(path) - 1] = test_group + '0';
        path[strlen(path) - 7] = '1';
        icin.open(path);
        check(icin);
        icin.close();
        output(test_group); //输出分类结果
    }
    printf("average precision: %lf\n",precision_mean);
    printf("average recall: %lf\n",recall_mean);
    printf("average f1: %lf\n",f1_mean);
    return 0;
}
