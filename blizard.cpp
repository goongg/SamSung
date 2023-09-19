#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int N, M;
int map[50][50];
typedef pair<int,int> pii;
queue<pii> q;
int point;
int dx[5] ={0, -1, 1, 0, 0};
int dy[5] ={0, 0, 0, -1, 1};
int x, y;
void print()
{
    cout<<endl;
    for(int i =0 ; i<N; i++){
        for(int j =0 ; j<N; j++)
            cout<<map[i][j]<< " ";    
        cout<<endl;
    }
}

bool move() 
{
    bool ret=0;
    int dr[4]={0, 1, 0, -1};
    int dc[4]={-1, 0, 1, 0 };
    int d=0;
    int move=1; //이 방향으로 움직여야 하는 거리
    int r = N/2;
    int c = N/2;
    vector<int> v;
    int nr = r;
    int nc = c;
    int cnt=0; //연속한 구슬의 갯수
    int ex=0;
    while(1) //0,0이 될 때까지 반복
    {
        for(int i =0; i <move; i++)
        {
            nr += dr[d];
            nc += dc[d];
            if(map[nr][nc]!=0)
            if(v.empty())
                v.push_back(map[nr][nc]);

            else if( v.back() != map[nr][nc])
            {
                if(v.back()!=0){
                if(cnt<3)
                {
                    for(int j=0; j<cnt; j++)
                        v.push_back(v.back());
                }
                else
                {
                    point += v.back()*(cnt+1);
                    v.pop_back();
                    v.push_back(0);
                    ret=1;
                }
                }
                v.push_back(map[nr][nc]);
                cnt=0;
            }
            else if(v.back()== map[nr][nc])
                cnt++;

            if(nr==0 && nc==0) break;
        }
        if(nr==0 && nc==0) break;
        d = (d+1) %4;
        if(d==2 || d==0) move++;
    }
    if(cnt<3)
    {
        for(int j =0; j<cnt; j++)
            v.push_back(v.back());
    }
    else
    {
        point += v.back()*(cnt+1);
        v.pop_back();
        ret=1;
    }

    vector<int> nv;
        for(int i : v)
            if(i!=0) nv.push_back(i);
    //구슬이 변화하는 단계
    if(ret ==0)
    {
        v.resize(0);
        int ex= -1;
        cnt =1;
        for(int i : nv)
        {
            if(ex==-1)
                ex=i;
            else if(i == ex)
                cnt++;
            else if(i != ex)
            {
                v.push_back(cnt);
                v.push_back(ex);
                ex=i;
                cnt=1;
            }
        }
        if(ex!=-1) 
        {
            v.push_back(cnt);
            v.push_back(ex);
        }
        nv = v;        
    }

    int idx=0;
    nr =N/2;
    nc =N/2;
    d=0;
    move=1;
    cnt=0;
    while(1) //0,0이 될 때까지 반복
    {
        for(int i =0; i <move; i++)
        {
            nr += dr[d];
            nc += dc[d];
            if(idx<nv.size())
                map[nr][nc] = nv[idx];
            else if(idx>= nv.size())
                map[nr][nc] = 0;
            
            idx++;

            if(nr==0 && nc==0) break;
        }
        if(nr==0 && nc==0) break;
        d = (d+1) %4;
        if(d==2 || d==0) move++;
    }

    return ret;
}


int main()
{
    cin>>N >>M;
    for(int i =0 ; i<N; i++)
        for(int j =0 ; j<N; j++)
            cin>>map[i][j];
    for(int i =0 ; i< M; i++)
    {
        int a, b;
        cin >>a >>b;
        q.push(make_pair(a,b));
    }
    x= y = N/2; // 상어 위치
    while(!q.empty())
    {
        int d = q.front().first;
        int s = q.front().second;
        q.pop();

        int nx= x;
        int ny= y;
        for(int i =0; i< s; i++)
        {
            nx += dx[d], ny += dy[d];
            map[nx][ny] = 0;
        }
        while(1)
        {
            bool b = move();
            if(b==0)
            break;
        }
    }
    cout<<point;
    return 0;
}