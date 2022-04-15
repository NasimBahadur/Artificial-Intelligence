#include<stdio.h>
#include<queue>


using namespace std ;


struct myqueue
{
    int x, y ;
}temp, temp2;


int grid[100][100], col[100][100] ;
int n, m ;
queue<myqueue>Q ;
myqueue par[100][100] ;

void bfs(){

    while(!Q.empty()){
        temp = Q.front() ;
        Q.pop() ;
        int i = temp.x ;
        int j = temp.y ;

        if(i-1 >=0 &&col[i-1][j] == 0 && grid[i-1][j] == 1){
            col[i-1][j] = 1 ;
            par[i-1][j] = temp ;
            temp2.x = i-1 ;
            temp2.y = j ;
            Q.push(temp2) ;

        }
        if(i+1 < n &&col[i+1][j] == 0 && grid[i+1][j] == 1){
            col[i+1][j] = 1 ;
            par[i+1][j] = temp ;
            temp2.x = i+1 ;
            temp2.y = j ;
            Q.push(temp2) ;

        }

        if(j-1 >=0 &&col[i][j-1] == 0 && grid[i][j-1] == 1){
            col[i][j-1] = 1 ;
            par[i][j-1] = temp ;
            temp2.x = i ;
            temp2.y = j-1 ;
            Q.push(temp2) ;

        }

        if(j+1 < m &&col[i][j+1] == 0 && grid[i][j+1] == 1){
            col[i][j+1] = 1 ;
            par[i][j+1] = temp ;
            temp2.x = i ;
            temp2.y = j+1 ;
            Q.push(temp2) ;

        }


    }
}
int main(){
    int i, j ;
    int stri, strj, fini, finj ;
    scanf("%d %d", &n, &m) ;
    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < m ; j++){
            scanf("%d", &grid[i][j]) ;
            col[i][j] = 0 ;
        }
    }
    scanf("%d %d %d %d", &stri, &strj, &fini, &finj) ;
    col[stri][strj] = 1 ;
    temp.x = stri ;
    temp.y = strj ;
    Q.push(temp) ;
    bfs() ;

    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < m ; j++){
            printf("%d ", col[i][j]) ;
        }
        printf("\n") ;
    }
}
