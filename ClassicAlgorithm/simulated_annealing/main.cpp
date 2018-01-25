/*
author: windyear
date: 2018-01-23
problem: TSP
������������Ҫ����n�����У�ÿ������ֻ����һ�Σ�Ѱ����̵�·������һ��ȫ���е����⡣
NP��ȫ�����⡣
*/

//����ģ���˻��㷨Ѱ��������Ž⣬�������������ѡȡ�����ڵ㽻����

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

//����һЩģ���˻��������Ҫ�õ��ĳ����������ʼ�¶ȵȡ�
const double T = 100000;
const double MIN_T = 1e-8;
const int NUM_OF_CITY = 40;
const int INNER_LOOP = 10000;
const double RATE = 0.995;

//����һ���ṹ�壬�洢����λ�����ꡣ
struct Location{
    double x;
    double y;
};

//����һ���ṹ�壬�洢Ҫ��������������
struct ChangeLocation{
    int location1,location2;
};

//���������������,�������һ�����ļ��ж�ȡ���ݵĳ���
void Input(Location location[], int num){
    cout << "Please input the location of cities:" << endl;
    for(int i = 0; i < num; i++){
        cin >> location[i].x >> location[i].y;
    }
    return ;
}

//���ļ��ж�ȡ����
void InputFromFile(Location location[], int num, char* filename){
    //�ļ���������������һ���ļ�
    ifstream input_path(filename);
    if(input_path){
        int index;
        while(input_path >> index){
            //cout << "the index:" << index << endl;
            input_path >> location[index-1].x >> location[index-1].y;
            //cout << "the location: " << location[index-1].x << location[index-1].y << endl;
        }
    }
    return ;
}
//��ʼ��
void Init(int path[], int num){
    cout << "Init the start path......" << endl;
    //��������һ�������ȫ���бȽ��鷳����������ֱ�Ӱ�˳��ѡ����һ����ʼ����·��
    //�ֱ��Ǵ�0��39��������ɵ�·����
    for(int i = 0; i < num; i++){
        path[i] = i;
    }
    return;
}

//����������֮��ľ���
double GetDistance(Location location[], int start, int end, int num){
    //����һ��ʼд���ˣ���������Ļ�ÿ�ζ��Ǽ����ͬһ��ֵ��Ӧ����path������
    double distance = pow((location[start].x - location[end].x), 2) + pow((location[start].y - location[end].y), 2);
    return sqrt(distance/10.0);
}
//�����ܵľ���,�տ�ʼ��ʱ�����������һ��Ҫ����
double WholeDistance(int path[], int num, Location location[]){
    double whole_distance = 0;
    for(int i = 0; i < num - 1; i++){
        whole_distance = whole_distance + GetDistance(location, path[i], path[i + 1], num);
        //cout << GetDistance(location, i , i+1, num);
    }
    whole_distance = whole_distance + GetDistance(location, 0, path[num-1], path[num]);
    return whole_distance;
}

//������������㣬����ǵ����Ĺؼ���
ChangeLocation ChangePath(int num){
    //�����������Ϊ40���������
    //��һ������
    srand((unsigned)time(NULL));
    ChangeLocation location;
    location.location1 = rand() % num;
    srand((unsigned)time(NULL));
    location.location2 = rand() % num;
    while( location.location1 == location.location2){
        location.location1 = rand() % num;
        srand((unsigned)time(NULL));
        location.location2 = rand() % num;
    }
    return location;
    //����������
    /* int temp = path[new_x];
    path[new_x] = path[new_y];
    path[new_y] = path[new_x]; */
}

void SimulatedAnnealing(Location location[], int path[], int num){
    //���ó�ʼ�¶�
    double t = T;
    //ֻҪ�¶ȴ����趨������ֵ���ͼ���Ѱ�ҽ�
    while( t > MIN_T){
        //��������һ����ѭ������һ���¶�ʱѰ�Ҷ����
        for(int i = 0; i < INNER_LOOP; i++){
            //�����½�
            ChangeLocation change_location = ChangePath(num);
            //����ԭ�����ܾ���
            double original_distance = WholeDistance(path, num, location);
            //����������
            int temp = path[change_location.location1];
            path[change_location.location1] = path[change_location.location2];
            path[change_location.location2] = temp;
            double new_distance = WholeDistance(path, num, location);
            double delta_distance = new_distance - original_distance;
            //����½�ľ���Ⱦɽ�ҪС��������µĽ⣬����ѭ��
            if(delta_distance <= 0){
                continue;
            }
            srand(time(NULL));
            double rd = rand()%999 / 1000;
            //�ؼ�����������µĽ�ȾɵĽ�ľ���Ҫ�� ��Ҫ��һ���ĸ��ʷ�Χ�ڽ��ܸý⡣
            if(exp(-delta_distance/t) > rd){
                continue;
            }
            //�������½⣬����·��Ϊԭ���Ľ⡣
            //���½���������
            temp = path[change_location.location1];
            path[change_location.location1] = path[change_location.location2];
            path[change_location.location2] = temp;
        }
        //����һ����ѭ��֮���ٸı��¶�ֵ
        t *= RATE;
    }
}

//��ʾ·��������
void ShowLocation(Location location[], int path[], int num){
    //for(int i = 0; i < num; i++){
        //cout << location[i].x << " " << location[i].y << endl;
    //}
    cout << "the path is :" << endl;
    for(int i = 0; i <num; i++){
        cout << path[i] << " ";
    }
    return;
}
int main(int argc, char** argv){
    cout << "The simulated annealing: " << endl;
    //������Ŀ��·��������ȱ���
    int num;
    cout << "Please input the number of city: ";
    cin >> num;
    Location* location = new Location[num];
    int* path = new int[num];
    if(argc == 1){
        Input(location, num);
    }else if(argc == 2){
        InputFromFile(location, num, argv[1]);
    }else{
        cout << "Error! Please input the correct arguments." << endl;
        return -1;
    }
    Init(path, num);
    SimulatedAnnealing(location, path, num);
    cout << "The whole distance is :" << WholeDistance(path , num, location) << endl;
    ShowLocation(location, path, num);
    //cin >> num;

}
