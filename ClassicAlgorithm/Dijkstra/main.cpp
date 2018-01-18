/*
dijkstra�㷨
author: windyear
date: 2018.1.18
�ο����ϣ��������� �㷨�� ���㷨���ۡ�
*/

#include <iostream>
//�����������͵�������Сֵ
#include <climits>

using namespace std;

//һ������ͼ��Ϣ�ĺ�������Ҫ����һ��һ�еıߣ��ֱ���������ͱߵ�Ȩֵ
void InitMap(int* map[], int& source, int num){
    for(int i = 0; i < num; i++){
        for(int j =0; j < num; j++){
            if(i == j){
                    map[i][j] = 0;
            }else{
                map[i][j] = 999;
            }
        }
    }
    cout << "Please input the index of start point: ";
    cin >> source;
    cout << "Please input the number of side: ";
    int num_of_side;
    cin >> num_of_side;
    cout << "Please input the two point and their distance!" << endl;
    for(int i = 0; i < num_of_side; i++){
        int a, b, value_of_side;
        cin >> a >> b >> value_of_side;
        map[a][b] = value_of_side;
    }
}

void Dijkstra(int* map[], int shortest_distance[], int num, int source){
    //��������ֱ����ڽӾ����ɳڼ�¼���飬���ڷ�ֹ����Խ��Ľ����Ŀ��
    //��������������о�������ĳ�ʼ����Ϊ�˷������������Ľ�㶼�Ǵ�0��ʼ�����ġ�
    //�ж�����Ƿ���ڽ����
    if( source >= num){
        cout << "The start point is out of range!" << endl;
        return;
    }
    //���ÿ������Ƿ�����ʼ��������ӣ����û�����ӣ���ʼ������Ϊ�ɱ�ʾ���������ֵ��
    for( int i = 0; i < num; i++){
        //����ͼ��ʱ�����˴������û�����ӵ�������ľ��������������ֵ��
        shortest_distance[i] = map[source][i];
    }

    //һ������������¼�Ѿ��ɳ��˵ĵ㣬0��ʾ��û�ɳڣ�1��ʾ�Ѿ��ɳ�
    int record[num];
    record[source] = 1;
    //������Ӧ���ڱ߽����ɳ�
    //���ڻ�û�ɳڵĵ��о��붥������ĵ㡣
    while(true){
        int shortest = 999;
        int shortest_index = 999;
        for(int i = 0; i < num; i++){
            if(record[i] == 1){
                continue;
            }
            if(shortest > shortest_distance[i]){
                shortest = shortest_distance[i];
                shortest_index = i;
            }
        }

    //����Ӧ����һ���ж��Ƿ����е��Ѿ��������ɳ�
        if( shortest_index == 999){
            break;
        }

    //��������ɳ�
        for(int i = 0; i < num; i++){
        //�ж��Ƿ���Խ����ɳ�
            if(shortest_distance[i] > shortest_distance[shortest_index] + map[shortest_index][i]){
                shortest_distance[i] = shortest_distance[shortest_index] + map[shortest_index][i];
            }
        }
        record[shortest_index] = 1;
        }

}

void ShowShortest(int* shortest_distance, int num){
    for(int i = 0; i < num; i++){
        cout << shortest_distance[i] << " " << endl;
    }
}
int main()
{
    /*
    �㷨˼·��dijkstra�㷨��Ҫ��Ϊ�˽����Դ���·���ļ������⣬���Լ������㵽���н���
    ���·�����ȡ��㷨�Ĺؼ������ڼ�¼һ����㵽ÿ���������·�����飬Ȼ��ÿ�δ�������ѡ
    ����ǰ���������̵ĵ㣬�Ըõ���ڱ߶������㵽���ľ�������ɳڡ�
    1����ʼ�����·������shortest��
    2��������һ�����鱣���������ϣ��ֱ����Ѿ������ɳڵĵ�ʹ��ɳڵĵ㡣
    3��ѡ���������������Ǹ���㣬�����������ڱ߶����е������������ɳڣ����¾��룬���ɳ�
    �����顣
    4��һֱѭ������������ֱ�����е㶼�Ѿ��������ɳڡ�
    */
    cout << "Please input the number of point: " ;
    int num;
    int source;
    cin >> num;
    //��̬���ٶ�ά���飬�¿����У��ٿ�����
    int* shortest_distance = new int[num];
    int** map = new int*[num];
    for(int i = 0; i < num; i++){
        map[i] = new int[num];
    }
    InitMap(map,source, num);
    Dijkstra(map, shortest_distance, num, source);
    ShowShortest(shortest_distance, num);
    //�ͷ������ͷ���
    for(int i = 0; i < num; i++){
        delete[] map[i];
    }
    delete[] map;
    delete[] shortest_distance;
    return 0;
}


