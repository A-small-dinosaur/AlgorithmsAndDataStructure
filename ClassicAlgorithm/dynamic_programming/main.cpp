/*
author: windyear
date: 2018-01-19
program: dynamic programming for a question about steel bars.
*/
#include <iostream>

using namespace std;

/*
���⣺����һ�����������Լ��ܹ����������б�������и�ĳ�����ȵĸ���
����ʹ�Ļ�õ��������
*/

/*
���ö�̬�滮�ķ�����������Էֽ�Ϊ���������ϣ���������Ž�Ҳ��������
�����Ž����ϡ��������������Ľ��������Ҫ�ظ�������������м������
�����á�����������Էֽ�Ϊ���и�һ�Σ�Ȼ�����ʣ�µ����Ż��и��������
������������
*/

/*��һ����չ���ع��⣬���Ǽ�¼����Ӧ�÷ָ�ķ�����
ֻ��Ҫ��סÿ����ѷָ�ĵ�һ��Ӧ���ж��٣�ʣ�µĿ���ͨ���������ߵݹ������
*/
//��д�Զ����µ��и��
//�ʼ��˼·Ҳʵ���˶�̬�滮�������ȽϷ�������ʵ�����ں����Ŀ�ʼ�ж�
//�Ƿ��Ѿ������˼��㡣
//�ú������ڲ����������ڲ������жϵ�
double Cut_Steel_bars(double profit[], int length, double cut_profit[]){
    if(length == 0){
        return 0;
    }
    //�ҳ������������е����Ž⣬ѭ���ҳ��������
    double max_profit = 0;
    for(int i = 1; i <= length; i++){
        if(profit[length - i] != 0){
            if(max_profit < profit[length -i] + cut_profit[i] ){
                max_profit = profit[length -i] + cut_profit[i];
            }
        }else{
            double temp_profit = Cut_Steel_bars(profit, length - i, cut_profit);
            if(max_profit < temp_profit + cut_profit[i] ){
                max_profit =  temp_profit + cut_profit[i];
            }
        }
    }
    //һ��ʼ����д���ˣ����������д�� max_profit_index, ������ԭ����ֵ��Ӧ���ǵ�ǰ�ĳ�����Ϊ������
    profit[length] = max_profit;
    //cout << max_profit_index << " " << profit[max_profit_index] << endl;
    return max_profit;
}

double Cut_Steel_bars_2(double profit[], int length, double cut_profit[]){
    if(length == 0){
        return 0;
    }
    if(profit[length] != 0){
        return profit[length];
    }
    //�ҳ������������е����Ž⣬ѭ���ҳ��������
    double max_profit = 0;
    for(int i = 1; i <= length; i++){
            double temp_profit = Cut_Steel_bars(profit, length - i, cut_profit);
            if(max_profit < temp_profit + cut_profit[i] ){
                max_profit =  temp_profit + cut_profit[i];
            }
        }
    //һ��ʼ����д���ˣ����������д�� max_profit_index, ������ԭ����ֵ��Ӧ���ǵ�ǰ�ĳ�����Ϊ������
    profit[length] = max_profit;
    //cout << max_profit_index << " " << profit[max_profit_index] << endl;
    return max_profit;
}

//�Ե����ϵķ�����ʹ���˵����ķ�ʽ���������ǰ���������Ѿ����
double Cut_Steel_bars_From_Bottom(double profit[], int length, double cut_profit[], int cut_index[]){
    if(length == 0){
        return 0;
    }
    profit[0] = 0;
    for(int i = 1; i <= length; i++){
        for(int j = 1; j <= i; j++){
            if(profit[i] < cut_profit[j] + profit[i -j]){
                profit[i] = cut_profit[j] + profit[i - j];
                cut_index[i] = j;
            }
        }
    }
    return profit[length];
}
int main()
{
    cout << "Please input the max length of the steel." << endl;
    int steel_length;
    cin >> steel_length;
    cout << "Please input the profit of every length of the steel." << endl;
    //��������ֱ�洢��ͬ���ȿ��Ի�ȡ�����������и��ȡ������
    double* profit = new double[steel_length + 1];
    profit[0] = 0;
    double* cut_profit = new double[steel_length + 1];
    int* cut_index = new int[steel_length + 1];
    for(int i = 1; i <= steel_length; i++){
        cin >> cut_profit[i];
        profit[i] = 0;
        cut_index[i] = 0;
    }

    //Cut_Steel_bars_2(profit, steel_length, cut_profit);
    Cut_Steel_bars_From_Bottom(profit, steel_length, cut_profit, cut_index);
    for(int i = 1; i <= steel_length; i++){
        cout << profit[i] << endl;
    }

    while(steel_length != 0){
        cout << cut_index[steel_length] << " ";
        steel_length = steel_length - cut_index[steel_length];
    }
    delete[] cut_profit;
    delete[] profit;
    delete[] cut_index;
    return 0;
}
