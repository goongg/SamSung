#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N;
typedef pair<int, int> pii;
int dr[4] ={-1, 0, 0, 1};
int dc[4] ={0, -1, 1, 0 };

class shark
{
    public:
    int r, c;
    int depth;
    int m;
};

vector<pii> fish;
vector<pii> find_fish;
int spend_time=0;
int map[21][21];
shark s;
int eat=0;//먹은 믈고기의 수

void bfs() //현재 위치에서 먹을 수 있는 물고기를 찾아 find_fish에 저장, 쓴 시간은 spend_time에 저장
{
    bool visit[21][21];
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            visit[i][j]=0;

    spend_time=99999999;
    queue<shark> q;
    shark u;   
    u =s;
    u.depth=0;
    q.push(u);
    visit[u.r][u.c]=1;
    while(!q.empty())
    {
        u = q.front();
        q.pop();

        if(u.depth > spend_time) break;        

        if(map[u.r][u.c] < u.m && map[u.r][u.c]>0) //먹을 수 있는 물고기를 발견하면
        {
            // cout<<"find!!"<<u.r<<" "<<u.c<<endl;
            spend_time = min(spend_time, u.depth);
            find_fish.push_back( make_pair(u.r, u.c));
            continue; //더 뻗어나갈 필요는 없음
        }


        for(int d=0; d<4; d++)
        {
            int nr = u.r + dr[d];
            int nc = u.c + dc[d];
            if(nr < 0 || nr >=N || nc <0 || nc>=N) continue;
            if(visit[nr][nc]) continue;
            if(map[nr][nc] > u.m) continue; //자기보다 큰 물고기가 있는곳은 지나갈 수 없음
            visit[nr][nc]=1;
            shark v= u;
            v.r = nr;
            v.c = nc;
            v.depth++;
            q.push(v);
            v.depth--;
        }
    }
}

int main()
{
    cin>>N;
    for(int i =0 ; i< N; i++)
        for(int j =0 ; j<N; j++)
        {
            cin>>map[i][j];
            if(map[i][j] >= 1 && map[i][j] <=6)
                fish.push_back(make_pair(i,j));
            else if (map[i][j]==9)
            {
                s.r=i;
                s.c=j;
                s.m=2;
                s.depth=0;
                map[i][j]=0;
            }
        }
    
    int answer=0;
    while(1)
    {
        bool finish=1;
        //먹을 수 있는 물고기가 있는지 조사, 먹은앤 0으로 표시
        for(pii p : fish)
        {
            if(map[p.first][p.second] ==0) continue;
            if(map[p.first][p.second] < s.m) 
            {
                finish=0;
                break;
            }
        }
        //먹을 수 있는 물고기가 없으면 끝냄
        if(finish==1) break;
        find_fish.clear();
        find_fish.resize(0);
        bfs();
        if(find_fish.size()==0) break;
        int min_r=1000;
        int min_c=1000;

        for(pii p : find_fish)
            min_r=  min(p.first,min_r);
        
        for(pii p : find_fish)
        {
            if(p.first == min_r)
                min_c=  min(p.second,min_c);
        }
        // cout<<"현재 위치"<<s.r<<" "<<s.c<<" "<<s.m<<endl;
        // cout<<"찾은 물고기\n";
        // for(pii p : find_fish)
        // {
        //     cout<<p.first<<" "<<p.second<<endl;
        // }


        // cout<<"\n선택물고기:"<<min_r<<" "<<min_c<<" "<<map[min_r][min_c]<<endl;
        // cout<<"소요시간"<<spend_time<<endl;
        map[min_r][min_c] = 0;
        s.r = min_r;
        s.c = min_c;
        eat++;
        if(eat==s.m)
        {
            s.m+=1;
            eat=0;
        }
        answer+=spend_time;
    }

    cout<<answer;
    return 0;
}