#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef pair<int, int> pii;
int n;
int m;
int map[101][101];
int graph[5000][5000];
#define INF 999999
int answer=INF;
vector< vector<pii> > lands;
int dr[4] ={-1, 0, 1, 0};
int dc[4] ={ 0, 1, 0, -1};

bool visit[101][101];

vector<int> dijk(int start, int n)
{
    vector<bool> vis(n+1);
    for(int i=1 ; i<=n; i++) vis[i]=0;

    vector<int> time(n+1);
    for(int i =1 ; i<=n; i++)
        time[i]=INF;
    time[start]=0;

    priority_queue<pii, vector<pii>, greater<pii> > pq;
    pq.push(make_pair(0, start));

    while(!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        if(vis[u]) continue;
        vis[u]=1;
        for(int v= 1 ; v<=n; v++)
        {
            if(u==v) continue;

            if(time[v] > graph[u][v] + time[u])
            {
                time[v] = graph[u][v] + time[u];
                pq.push( make_pair(time[v], v));
            }
        }
    }

    return time;
}
int max_point=0;
void dfs(int a, int n, int point)
{    
    for(int i =1 ; i<=n-1; i++)
    {
        for(int j =i+1 ; j<=n; j++ )
        {
           if( graph[i][j] == INF) continue; // 이건 끊을필요없음
           vector<int> t;
           int buf= graph[i][j];
           graph[i][j] = INF;
           graph[j][i] = INF;
           t= dijk(1, n);
           bool fin=0;
            for(int ii=1; ii<=n; ii++ )
            {
                // cout<<t[ii]<<" ";
                if(t[ii] ==INF) //갈 수 없는곳이 생기면
                {
                    fin=1; 
                }//가지 안뻗음
            }
            // cout<<endl;
            if(!fin)
            {
                max_point = max(max_point, point+buf);
                // cout<<"이거 끊어도, 전체연결:" << i<<" " <<j <<" "<<buf<<endl;
               dfs(i, n, point+buf);
            }
           graph[i][j] = buf;
           graph[j][i] = buf;
        }
    }
};

vector<pii> cur_land;
void search_land(int idx, pii cur) //idx 섬
{
    int r = cur.first;
    int c = cur.second;
    if(visit[r][c]) return; 
    visit[r][c]=1;
    map[r][c]= idx;
    cur_land.push_back(make_pair(r,c));

    for(int d=0; d<4 ; d++)
    {
        int nr = r+dr[d];
        int nc = c+dc[d];
        if(nc <0 || nc >=m || nr<0 || nr>=n) continue;
        if(map[nr][nc]==0) continue;
        if(visit[nr][nc]) continue;

        search_land(idx, make_pair(nr,nc) );
    }
}

int make_bridge(int from, int to)
{
    int length =INF;
    //두 다리가 연결 가능한지 체크 가능하다면 최솟값 return
    vector<pii> a = lands[from-1];

    int cur_len=0;
    for(int i =0; i< a.size(); i++)
    {
        int r = a[i].first;
        int c = a[i].second;
        cur_len=0;
        for(int d=0; d<4; d++)
        {
            int nr =r;
            int nc =c;
            cur_len=0;
            while(1)
            {
                nr+=dr[d];
                nc+=dc[d];
                if(nc<0 || nc >= m || nr<0 || nr>=n) break;
                if(map[nr][nc] ==0 )
                {
                    cur_len++;
                    continue;
                }
                else if(map[nr][nc] == to)
                {
                    if(cur_len >=2)
                    length= min(length, cur_len);
                    break;
                }
                else
                    break;
            }
        }
    }
    graph[from][to] = length;
    graph[to][from] = length;

    return 1;
}

int main()
{
    cin>>n >> m;
    for(int i=0; i< n; i++)
        for(int j =0 ;j<m; j++)
            cin>>map[i][j];
    
    int idx=1;
    for(int i =0 ; i< n; i++)
    {
        for(int j =0 ;j<m; j++)
        {
            if(visit[i][j]) continue;
            if(map[i][j]==1)
            {
                cur_land.resize(0);
                search_land(idx++, make_pair(i,j));
                lands.push_back(cur_land);
            }
        }
    }

    // cout<<endl;
    // for(int i =0; i<n; i++)
    // {
    //     for(int j =0 ; j<m; j++)
    //     cout<<map[i][j]<<" ";
    //     cout<<endl;
    // }

    for(int i =1; i<= lands.size(); i++)
    {
        for(int j =1 ; j<= lands.size(); j++)
        {
            graph[i][j] = graph[j][i] =INF;       
            if(i==j) graph[i][j] =0;
        }
    }

    for(int i=1; i<= lands.size()-1; i++)
        for(int j = i+1; j<= lands.size(); j++)
            make_bridge(i,j);
    

// cout<<endl;
//     for(int i =1; i<= lands.size(); i++)
//     {
//         for(int j =1 ; j<= lands.size(); j++)
//             cout<<graph[i][j] << " ";
//         cout<<endl;
//     }
    vector<int> tt;
    tt= dijk(1, lands.size());
    answer=0;
    for(int i =1 ; i<= lands.size()-1; i++)
    {
        for(int j =i+1 ; j<= lands.size(); j++)
            if(graph[i][j] !=INF)
                answer+= graph[i][j];
    }
    
    // cout<<"기본 싱테 dijk\n";
    // cout<<answer<<endl;

    for(int i =1 ; i< tt.size(); i++)
    {
        // cout<<tt[i]<<" ";
        if(tt[i] ==INF)
        {
            cout<<-1;
            return 0;
        }
    }

    // cout<<endl;
    dfs(1, lands.size(), 0);

    cout<<answer-max_point<<endl;

    return 0;
}
