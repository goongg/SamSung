#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
int map[65][65];
int Q, N, n=1, answer=0, max_size=0;
queue<int> q;
void rotate(int l);
int melt();
void bfs(int ,int);
int main()
{
    cin>>N>>Q;
    for(int i =0; i<N; i++) n*=2;
    for(int i =0 ; i< n; i++)
        for(int j =0; j<n; j++)
            cin>>map[i][j];
    for(int i =0; i< Q; i++)
    {
        int a;  
        cin>>a; q.push(a);
    }
    while(!q.empty())
    {
        max_size=0;
        answer=0;
        int L = q.front();
        q.pop();
        rotate(L);
        answer= melt();
    }
    cout<<answer<<endl<<max_size;
    return 0;
}

void rotate(int L) // map을 격자별로 나눠서 돌림
{
    int l=1;
    int nmap[65][65];
    for(int i =0; i<L; i++) l*=2;

    for(int i =0; i< n; i+= l)
        for(int j=0; j<n; j+=l)
            for(int ii=0; ii<l; ii++)
                for(int jj=0; jj<l; jj++)
                    nmap[i + jj][j + l-1 - ii] = map[i+ii][j+jj];
                
    for(int i =0 ; i< n; i++)
        for(int j =0; j<n; j++)
            map[i][j]= nmap[i][j];
}

vector<pii> vv;
bool visit[65][65];
int dx[4]= {-1, 0, 1, 0};
int dy[4]= {0, 1, 0, -1};
int melt()
{
    int ret=0;
    int nmap[65][65];
    for(int i=0; i< n; i++)
        for(int j =0; j<n; j++)
        {
            int cnt=0;
            if(map[i][j]==0) continue;
            for(int d=0; d<4 ;d++)
            {
                int nx=  i+dx[d];
                int ny = j+dy[d];
                if(nx <0 || nx >=n || ny <0 || ny>=n) continue;
                if(map[nx][ny]!=0) cnt++;
            }
            if(cnt<3 ) nmap[i][j] = map[i][j]-1;
            else nmap[i][j] = map[i][j];
            ret+=nmap[i][j] ;
        }
    
    for(int i =0 ; i< n; i++)
        for(int j =0; j<n; j++)
        {
            map[i][j]= nmap[i][j];
            visit[i][j]=0;
        }
    
    for(int i=0; i< n; i++)
        for(int j =0; j<n; j++)
        {
            if(visit[i][j]) continue;
            if(nmap[i][j]==0) continue;
            vv.resize(0);
            visit[i][j]=1;
            vv.push_back(make_pair(i,j));
            bfs(i,j); // 이 영역과 인접한 영역을 찾아 저장
            max_size= max(max_size, (int)vv.size());
        }
    return ret;
}


void bfs(int x ,int y)
{
    queue<pii> qq;
    qq.push(make_pair(x,y));
    while(!qq.empty())
    {
        pii u = qq.front();
        qq.pop();
        for(int d=0; d<4 ;d++)
        {
            pii v =u;
            int nx = v.first+dx[d];
            int ny = v.second+dy[d];
            if(nx<0 || nx >=n || ny<0 || ny>=n || visit[nx][ny] || map[nx][ny] ==0) continue;
            vv.push_back((make_pair(nx, ny)));
            visit[nx][ny] =1;
            qq.push( make_pair(nx,ny));
        }
    }
}