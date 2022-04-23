#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
typedef vector<int> group;

#define debug 1
//좌, 하, 우, 상
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};


class Game {

    public:
        int N, M ; // 격자, 색상
        vector<int> t;
        vector<group> groups;
        group g;
        int point;
        bool visit[400];
        
    void input()
    {
        cin >> N >> M;

        t.resize(N*N);

        for(int i=0; i< t.size(); i++)
            cin>>t[i];
        
        point=0;
        return ;
    };

    int search_group()
    {
        g.resize(0);
        memset(&visit[0], 0, 400*sizeof(bool) );
        
        for(int i=0; i< N*N; i++)
        {
            if(visit[i]==false && t[i]>=1 && t[i]<<M)
            {
                g.clear();
                g.resize(0);
                g.push_back(i);
                visit[i]=true;

        #if debug
        cout<<"bfs init (" <<i/N<<", "<<i%N<<")\n";
        #endif

                bfs(i);
                if(g.size()>=2)
                   groups.push_back(g);
        #if debug
        cout<<"bfs finush: size:" << g.size()<<'\n'<<'\n';
        #endif
            }
        }
        g.clear();
        groups.clear();
        memset(&visit[0], 0, 400*sizeof(bool) );

        for(int i=0; i< N*N; i++)
        {
            if(visit[i]==false && t[i]>=1 && t[i]<<M)
            {
                g.clear();
                g.push_back(i);
                visit[i] = true;
                dfs(i);                
            }        

    };
    void dfs(int i)
    {
        int cur, next;
        int c_x, c_y;
        int n_x, n_y;

        for(int d=0; d<4; d++) //인접 네 방향 조사
        {
            c_x = cur%N; 
            c_y = cur/N;
            n_x = c_x + dx[d];
            n_y = c_y + dy[d];
            
        }

    }
    void bfs(int i)
    {
        queue<int> q;
        q.push(i);
        while(!q.empty())
        {
            int cur, next;
            int c_x, c_y;
            int n_x, n_y;

            cur = q.front();
            q.pop();
            for(int d=0; d<4; d++) //인접 네 방향 조사
            {
                c_x = cur%N; 
                c_y = cur/N;
                n_x = c_x + dx[d];
                n_y = c_y + dy[d];
                next = n_y*N+ n_x;
                if( (n_x >= 0 && n_x <N && n_y >=0 && n_y <N) && //범위에 끝이 아니면서 
                     (t[next] ==t[i]  || t[next] == 0  ) && //무지개이거나 같은숫자인데
                       (visit[next] == false ) )   //아직 방문한 곳이 아니면   
                {
                    g.push_back(next); //다음위치를 그룹에 추가
                    visit[next] = true; //다음위치를 방문처리
                    q.push(next);   // bfs 큐에 추가
        #if debug
        cout<<"같은그룹찾았다 (" <<next/N<<", "<<next%N<<")\n";
        #endif
                }
            }
        }

        //무지개 방문기록은 삭제해
        for(int ii=0; ii<N*N; ii++)
        {
            if(t[ii]== 0)
                visit[ii]=false;
        }
    }

    void del_group(int g_idx)
    {
        for(int i: groups[g_idx])
            t[i] = -2;
        
        point  += groups[g_idx].size()*groups[g_idx].size();
    }

    void gravity()
    {
        
        for(int i=N-1; i>=0; i--) //첫번째 열부터, 이동 시작
        {
            for(int j=0; j<N; j++)
            {
                if(t[i*N + j] == -2) //이곳이 빈곳인지를 체크
                {
                    int ny=i;
                    while(1) //이곳으로부터 정상적인 숫자를 찾을때까지 돌림
                    {
                        ny--;
                        if(t[ny*N + j] == -1) break;
                        if(ny <0) break;
                        if(t[ny*N + j] == -2) continue;
                        if(t[ny*N + j] >= 1 &&t[ny*N + j] <= M )
                        {
                           t[i*N+j] = t[ny*N + j];
                           t[ny*N + j] = -2;
                           break;
                        }
                    }
                }
            }
        }

        #if debug
        for(int i=0; i< N; i++)
        {
            for(int j=0; j<N ; j++)
            cout<< t[i*N+j] <<" ";
        }
        cout<<endl;
        #endif
    }

    void sol()
    {
        inpit();
        game.search_group();
        

    }

};

    

int main()
{

    Game game;
    game.input();
    game.search_group();

    for(int i=0; i<game.groups.size(); i++)
    {
        cout<<game.t[game.groups[i][0]]<<":";
        for(int iii :game.groups[i])
            cout<<"(" << iii/game.N <<", "<< iii%game.N <<")  ";
        cout<<endl;
    }
    return 0;
}