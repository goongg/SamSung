#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int r, c, k, w;
#define R 1
#define L 2
#define U 3
#define D 4

int dr[5] ={0, 0,0, -1, 1};
int dc[5] ={0, 1, -1 , 0 ,0 };

typedef  pair<int, int> pii;
typedef  pair<pii, int> pii_i;

vector<pii> Search; //조사할곳
vector<pii_i> Hitter; // 히터위치
int temp[21][21];

int map[21][21];
bool wall[21][21][4]; //특정 좌표에서 R L U D 으로 갈 수 있는지 체크

void print_temp()
{
    for(int i =0; i< r; i++)
    {
        for(int j =0; j<c; j++)
            cout<< temp[i][j]<<" ";
        cout<<endl;
    }
}
bool (pii a, pii b)
{
    return 1;
}
void wind(int dirct, pii p) //바람 퍼트리는 함수
{
    bool visit[21][21];
    bool temp_up[21][21];
    int dd_r[3]; //dircet를 기준으로 뻗어갈 세 곳
    int dd_c[3]; 

    for(int i =0 ; i< 21; i++)
        for(int j=0; j<21; j++)  
        {
            temp_up[i][j]=0;  
            visit[i][j]=0;
        }
    switch(dirct)
    {
        case U:  
        dd_r[0] = d_r[U];
        dd_c[0] = d_c[U];

        dd_r[1] = d_r[U] + d_r[R];
        dd_c[1] = d_c[U] + d_c[R];

        dd_r[2] = d_r[U] + d_r[L];
        dd_c[2] = d_c[U] + d_c[L];
            break;

        case D:
        dd_r[0] = d_r[D];
        dd_c[0] = d_c[D];

        dd_r[1] = d_r[D] + d_r[R];
        dd_c[1] = d_c[D] + d_c[R];

        dd_r[2] = d_r[D] + d_r[L];
        dd_c[2] = d_c[D] + d_c[L];
            break;

        case R:
        dd_r[0] = d_r[R];
        dd_c[0] = d_c[R];

        dd_r[1] = d_r[R] + d_r[U];
        dd_c[1] = d_c[R] + d_c[U];

        dd_r[2] = d_r[R] + d_r[D];
        dd_c[2] = d_c[R] + d_c[D];
            break;
        case L:
        dd_r[0] = d_r[L];
        dd_c[0] = d_c[L];

        dd_r[1] = d_r[L] + d_r[U];
        dd_c[1] = d_c[L] + d_c[U];

        dd_r[2] = d_r[L] + d_r[D];
        dd_c[2] = d_c[L] + d_c[D];
            break;

    }
    dd_r[0] = dr[dirct];
    dd_c[0] = dc[dirct];

    dd_r[0] = dr[dirct];
    dd_c[0] = dc[dirct];

    pii_i u;
    u.first.first =p.first;
    u.first.second =p.first;
    u.second = 5;
    queue<pii_i> q;
    q.push(u);
    visit[p.first][p.second]=1;
    while(!q.empty())
    {
        u=q.front();
        q.pop();

        for(int i =0; i<3; i++)
        {
            pii_i v;
            v.first.first = u.first.first + dd_r[i];
            v.second.second = u.second.second + dd_c[i];


        }

    }

}

void spread() //온도 부는 함수
{
    
}


int main()
{
    cin>>r>>c>>k;
    for(int i =0 ; i < r ; i++)
        for(int j =0; j< c;  j ++)
        {
            cin>>map[i][j];
            if(map[i][j]>=1 && map[i][j]<=4)
            {
                pii_i h = make_pair(make_pair(i,j),map[i][j]);
                Hitter.push_back(h);
            }
            else if(map[i][j]==5)
            {
                pii p= make_pair(i,j);
                Search.push_back(p);
            }
            temp[i][j]=0;
        }
    cin>>w;
    for(int i =0; i< w; i++)
    {
        int x;
        int y;
        int t;
        cin>>x>>y>>t;
        x--;
        y--;
        if(t==0)
        {
            wall[x][y][U] = 1; //윗방향에 벽있음
            if(x-1 >=0)
                wall[x-1][y][D] =1; //아랫방향에 벽있음
        }
        else
        {
            wall[x][y][R] = 1; //오른방향에 벽있음
            if(y+1 < c)
                wall[x][y+1][L] =1; //왼방향에 벽있음
        }
    }



    return 0;
}