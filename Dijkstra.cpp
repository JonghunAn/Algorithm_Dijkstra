#include <stdio.h>
#include<iostream>
#include <malloc.h>

using namespace std;
#pragma warning (disable:4996)

#define INF 999

typedef struct Edge
{
    int vertex[2]; // start, end
    int length;      // weight
}Edge;

int** make_array(int n);    
void read_array(int* W[], int n); 
void dijkstra(int n, int* W[], Edge F[]);
FILE* file;

int main()
{
   // file = fopen("Test4.8Data.txt", "r");
    file = fopen("SelfData.txt", "r");
    if (file == NULL) {
        perror("File open error");
        return 0;
    }

    int n;
    fscanf(file, "%d", &n);

    int i;
    int** W;
    Edge* F = (Edge*)malloc(sizeof(Edge) * n);
   // Edge F[5];

    W = make_array(n); 
    read_array(W, n); 

    dijkstra(n, W, F);

    cout<<"    Dijkstra F Edge List\n\n";
    for (i = 0; i < n - 1; i++)
        cout << "\tV" << F[i].vertex[0] + 1 << " -- V" << F[i].vertex[1] + 1 << endl;
    free(F);
    fclose(file);

    return 0;
}

int** make_array(int n) // N x N 배열 만들기
{
    int i;
    int** array;
    n--;
    array = (int**)malloc(sizeof(int*) * n+1);
    for (i = 0; i <= n; i++)
        array[i] = (int*)malloc(sizeof(int) * n+1);

    return array;
}

void read_array(int* W[], int n)    // 파일에게 배열값을 읽어 배열 G에 저장
{
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            fscanf(file, "%d", &W[i][j]);
}

void dijkstra(int n, int* W[], Edge F[])    // 다익스트라 알고리즘
{
    int i, vnear = 0;
    int min, num = 0;
    Edge e;
    int* touch = (int*)malloc(sizeof(int) * n);
    int* length = (int*)malloc(sizeof(int) * n);

    for (i = 1; i < n; i++) {
        touch[i] = 0;        
        length[i] = W[0][i];  // path의 last vertex v1으로 세팅
    }                           

    while (num < n - 1) {            // vertex Y에 추가
        min = INF;
        for (i = 1; i < n; i++)    // shortest path check
            if (length[i] >= 0 && length[i] < min) {
                min = length[i];
                vnear = i;
            }
        e.vertex[0] = touch[vnear];  
        e.vertex[1] = vnear;      
        e.length = min;             
        F[num] = e;                

        for (i = 1; i < n; i++)
            if (length[vnear] + W[vnear][i] < length[i]) {
                length[i] = length[vnear] + W[vnear][i];
                touch[i] = vnear;   // Y에 속하지 않는 각 정점에 대해서,
            }                       // 최단경로를 바꾼다.
        length[vnear] = -1;           // vnear가 인덱스인 정점을 Y에 추가
        num++;                      // repeat(n-1 times)를 위한 변수
    }
}