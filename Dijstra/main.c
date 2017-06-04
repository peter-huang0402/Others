#include <stdio.h>
#include <stdlib.h>
# define SIZE 500
# define NO_PATH 999999

int vertexN = 0;
int matrix[SIZE][SIZE];
int distance[SIZE];
int parentVertex[SIZE];
int visit[SIZE];

void dijkstra(int);

void initMatrix(){
    int i,j=0;
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){

           if ( i == j ){
                matrix[i][j]=0;
                matrix[j][i]=0;
                continue;
           }

           matrix[i][j]=NO_PATH;
        }
    }
}


void initDijkstra(){
    int i=0;
    for(i=0;i<=vertexN;i++){
        //distance[i]=matrix[1][i];
        distance[i] = NO_PATH;
        parentVertex[i]=0;
        visit[i]=0;
    }
}

void relax(int from,int to){
    if ( !visit[to] &&  distance[to] > distance[from]+ matrix[from][to]){
        distance[to] = distance[from]+matrix[from][to];
        parentVertex[to] = from;  /// ....missing
    }
}

void dijkstra(int start){
    initDijkstra();
    distance[start]=0;  ///key!!
    parentVertex[start]=start;

    int i,j=0;
    int shortestPath=NO_PATH;
    int vertex = 0;


    for(i=1;i<=vertexN;i++){
        shortestPath= NO_PATH ; ///* key...missing */
        
        for(j=1;j<=vertexN;j++){
            if (!visit[j] && shortestPath > distance[j]){
                shortestPath = distance[j]; ///... missing
                vertex=j;
            }
        }


        visit[vertex] = 1; /// key ... missing
        ///parentVertex[vertex]=i;  ///key!! because parentVertex will be updated in relax action.

        for(j=1;j<=vertexN;j++){
            relax(vertex,j);
        }
    }


}

int main()
{

    #if ! defined(ONLINE_JUDGE)
    freopen("test_input.txt","r",stdin);
    freopen("test_output.txt","w",stdout);
    # endif

    int row=0;
    int v1,v2,path=0;
    while( (scanf("%d %d",&vertexN,&row)==2)  && vertexN && row){

        initMatrix();

        while(row--){
            scanf("%d %d %d",&v1,&v2,&path);
            matrix[v1][v2]=path;
            matrix[v2][v1]=path;
            ///matrix[v1][v1]=0;
            ///matrix[v2][v2]=0;
        }

        dijkstra(1);
        printf("AAAAAAAAAAAAAAA");
    }

    printf("Hello world!\n");
    return 0;
}







