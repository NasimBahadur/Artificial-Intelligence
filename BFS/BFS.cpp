#include<stdio.h>
#include<vector>
#include<queue>

using namespace std;
int col[100], d[100], par[100] ;
queue<int>Q ;
vector<int>adj[100] ;

void BFS()
{
    while(!Q.empty()){
        int u = Q.front() ;
        Q.pop() ;

        for(int i = 0 ; i < adj[u].size() ; i++){
            int v = adj[u][i] ;
            if(col[v] == 0){
                col[v] = 1 ;
                d[v] = d[u] + 1;
                par[v] = u ;
                Q.push(v) ;
            }
        }
        col[u] = 2 ;
    }
}
void path(int src, int dst){
    if(src == dst){
        printf("%d ", src) ;
        return ;
    }
    printf("%d ", dst) ;
    path(src, par[dst]) ;

}

void Connectivity(int n)
{
    for(int i = 0 ; i < n  ; i++){
        if(col[i] == 0){
            printf("Disconnected\n") ;
            return ;
        }
    }
    printf("Connected\n") ;
}

int main()
{
    freopen("in.txt","r",stdin);
    /freopen("out.txt","w",stdout);
    int n, edge, i, j, u, v ;
    scanf("%d %d", &n , &edge) ;
    for(i = 0 ; i < edge ; i++){
        scanf("%d %d", &u, &v) ;
        adj[u].push_back(v) ;
        adj[v].push_back(u) ;
    }
    for(i = 0 ; i < n ; i++){
        col[i] = 0 ;
        par[i] = -1 ;
        d[i] = 99999 ;
    }

    int source, dst ;
    printf("Source: ") ;
    scanf("%d", &source) ;
    printf("Destination: ") ;
    scanf("%d", &dst) ;

    col[source] = 1 ;
    d[source] = 0 ;
    Q.push(source) ;
    BFS() ;
    Connectivity(n) ;

    if(col[dst] != 0){
        path(source, dst) ;
    }
    else printf("No path\n") ;
}
