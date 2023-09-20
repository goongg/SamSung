#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

#define INF 9999999
typedef pair<int, int> pii;

int map[126][126];
int cost[16000];

int N;
int i =1;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
void dijk();
int main()
{
    while(1){
    cin>>N;

    if(N==0) return 0;

    for(int i =0; i<N; i++)
        for(int j=0; j<N; j++)
            cin>>map[i][j];
    dijk();

    cout<<"Problem "+to_string(i++) + ": " + to_string(cost[N*N-1]) << '\n';
    }
}

void dijk()
{
    priority_queue<pii, vector<pii>, greater<pii> > pq; //cost, index
    vector<bool> visit((N+1)*(N+1));
    int start = 0;

    pq.push(make_pair(map[0][0], start));
    for(int i =0; i<N*N; i++) cost[i] = INF;
    cost[0] = map[0][0];
    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if(visit[u]) continue;
        visit[u] =1;
        for(int d=0; d<4; d++)
        {
            int r = u/N; 
            int c = u%N;
            int nr = r + dx[d];
            int nc = c + dy[d];
            int v = nr*N + nc;
            if(nr <0 || nc<0 || nr >=N || nc>=N) continue;

            if(cost[v] > cost[u] + map[nr][nc])
            {
                cost[v] = cost[u] + map[nr][nc];
                pq.push(make_pair(cost[v], v));
            }
        }
    }

}