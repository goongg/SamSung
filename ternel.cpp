#include <iostream>
#include <vector>
using namespace std;

int T, N, M, R, C, L;
int map[51][51];
int t[51][51];
bool visit[51][51];
typedef pair< int , int> pii;

int dr[4] ={-1,0,1,0};
int dc[4] ={0,1,0,-1};
#define uu 0
#define rr 1
#define dd 2
#define ll 3

int point;
void dfs(pii cur, int depth)
{

    if(depth == L) return;

    int r= cur.first;
    int c= cur.second;
    vector<int> d;
    d.resize(0);
    t[cur.first][cur.second] = depth; 

    if(map[r][c] == 1) // 네 방향조사 +
    {
        d.push_back(uu); d.push_back(rr); d.push_back(dd); d.push_back(ll);
    }
    else if (map[r][c]==2) // 상 하 조사 |
    {
        d.push_back(uu); d.push_back(dd);
    }
    else if (map[r][c]==3) //좌 우 조사 -
    {
        d.push_back(ll); d.push_back(rr);
    }
    else if (map[r][c]==4) //상 우 조사 
    {
        d.push_back(uu); d.push_back(rr);
    }
    else if (map[r][c]==5) //하 우 조사 
    {
        d.push_back(dd); d.push_back(rr);
    }
    else if (map[r][c]==6) //하 좌 조사 
    {
        d.push_back(dd); d.push_back(ll);
    }
    else if (map[r][c]==7) //좌 상 조사 
    {
        d.push_back(ll); d.push_back(uu);
    }

    for(int i: d)
    {
        int nr = r + dr[i];
        int nc = c+ dc[i];
        if(nr <0 || nr >=N || nc <0 || nc >=M) continue;
        if(map[nr][nc]==0) continue;
        if(t[nr][nc]!=0 && t[nr][nc] <= depth+1 ) continue; //내가 지금 조사할라고 하는곳이  이전에 더 빨리 조사됐던 곳이면 안해도 됨
        if(i == uu)
        {
            if(map[nr][nc] == 1 || map[nr][nc] == 2 || map[nr][nc] == 5 || map[nr][nc] == 6)
            {
                if(!visit[nr][nc])
                {
                    visit[nr][nc]=1;
                    point++;
                }
                // if(time[nr][nc] depth)
                dfs(make_pair(nr,nc), depth+1);
            }
            else
                continue;
        }
        else if (i==dd)
        {
            if(map[nr][nc] == 1 || map[nr][nc] == 2 || map[nr][nc] == 4 || map[nr][nc] == 7)
            {
                if(!visit[nr][nc])
                {
                    visit[nr][nc]=1;
                    point++;
                }
                dfs(make_pair(nr,nc), depth+1);
            }
            else
                continue;
        }
        else if (i ==rr)
        {
            if(map[nr][nc] == 1 || map[nr][nc] == 3 || map[nr][nc] == 6 || map[nr][nc] == 7)
            {
                if(!visit[nr][nc])
                {
                    visit[nr][nc]=1;
                    point++;
                }
                dfs(make_pair(nr,nc), depth+1);
            }
            else
                continue;
        }
        else if(i==ll)
        {
            if(map[nr][nc] == 1 || map[nr][nc] == 3 || map[nr][nc] == 4 || map[nr][nc] == 5)
            {
                if(!visit[nr][nc])
                {
                    visit[nr][nc]=1;
                    point++;
                }
                dfs(make_pair(nr,nc), depth+1);                
            }
            else
                continue;
        }
    }


return ;
}


int main()
{
    cin>>T;
    // int cnt=1;
    vector<int> ret;
    while(T-- >0)
    {
        cin>>N>>M>>R>>C>>L;

        for(int i =0 ; i< N; i++)
            for(int j =0 ; j< M; j++)
            {
                cin>>map[i][j];
                visit[i][j]=0;
                t[i][j]=0;
            }

        visit[R][C]=1;
        point=1; 
        dfs(make_pair(R,C), 1 );
        ret.push_back(point);
    }   

    for(int i =0 ; i< ret.size(); i++)
    {
        cout<<"#"<<i+1<<" "<<ret[i]<<endl;
    }
    return 0;
}