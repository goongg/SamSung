//6시 10분

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define debug 0

typedef vector<int> group;

int dx[4] ={ -1, 0, 1, 0};
int dy[4] ={  0, 1, 0, -1};

class game
{
    vector<group> groups;   //전채 그룹
    group max_group;        //선택 받은 그룹
    int max_group_size= 1;
    bool end=0;
    int score=0;
    vector<int> t;
    vector<bool> visit; //for dfs

    int n, m;
    int group_index=0;

    group dfs_ret;
    int dfs_num;

    public:
    void input()
    {
        cin>> n>> m;
        t= vector<int>(n*n);
        for(int i=0; i<n*n; i++) cin>>t[i];
        visit.resize(n*n);
    }

    void search_group() //bfs
    {

        //한칸씩 돌면서 dfs를 수행.. 이미 그룹핑이 되어있는거면 노드 진행 안함
        //돌면서 방문하지 않은 일반 블록이 나오면 dfs 시작

        #if debug
        cout<<"\nauto move, score:" << score<<endl;
        #endif

        visit.clear();
        visit.resize(n*n);
        groups.clear();
        groups.resize(0);

        max_group_size=1;
        end=1;
        for(int i=0; i<n ; i++){
            for(int j=0; j<n ; j++)
            {
                if( t[i*n +j] >0 && t[i*n +j] <=m && !visit[i*n+j]  )
                {
                    dfs_num= t[i*n +j];
                    visit[ i*n +j] = 1;
                    dfs_ret.clear();
                    dfs_ret.resize(0);
                    dfs_ret.push_back(i*n +j );
                    dfs(i*n +j);

                    if(dfs_ret.size() >= 2 )
                    {
                        end=0;
                        groups.push_back(dfs_ret);
                        if(max_group_size < dfs_ret.size())
                            max_group_size = dfs_ret.size();
                        #if debug
                        cout<<"group_first :" << i<<" "<<j <<" block:"<< dfs_num<< " size:"<< max_group_size<<endl;
                        #endif
                        group_index++;
                        
                    }
                    for(int ii=0; ii<n*n; ii++)
                        if(t[ii]==0) visit[ii]=0;

                    dfs_ret.clear();
                    dfs_ret.resize(0);
                }
            }
        }
    }
    
    void dfs(int cur) // cur로 부터 주변에 자기와 같은 숫자가 있는지 체크 있다면
    {
        for(int i=0; i<4 ; i++)
        {
            int nx = cur%n + dx[i];
            int ny = cur/n + dy[i];
            int next = ny*n + nx;
            if( nx<0 || nx>=n || ny<0 || ny>=n) continue;
            if( t[next] == -1 ) continue;

            if( ( t[next] == dfs_num || t[next] ==0 ) && !visit[next]) 
            {

                visit[next]= 1; //방문처리 하고
                dfs_ret.push_back(next);
                dfs(next);
            }
        }

    }

    // 
    void delete_block()
    {
        #if debug
        cout<<"delete block\n";
        #endif
        int ret=0;
        int max_y=-1;  //기준 블럭중 가장 큰 행
        int max_x=-1;  //기준 블럭중 가장 큰 열
        int max_rain_bow=0; //무지개 블럭의 수
        vector<group> new_groups;
        vector<int> rain_bow_size;  //무지개 블럭의 수

        for(group g : groups)
        {
            if(g.size() == max_group_size)
            {
                int rain =0;
                for(int i : g)
                {
                    if( t[i] ==0) rain++; 
                }
                rain_bow_size.push_back(rain);
                if(max_rain_bow  < rain)  max_rain_bow= rain;
                new_groups.push_back(g);   
            }
        }

        int i=0;
        for(group g : new_groups)
        {
            if(rain_bow_size[i]== max_rain_bow)
            {
                if(g[0]/n > max_y) max_y = g[0]/n;
            }
            i++;
        }

        i=0;
        for(group g : new_groups)
        {
            if(rain_bow_size[i]== max_rain_bow && g[0]/n  == max_y)
            {
                if(g[0]%n > max_x) max_x = g[0]%n;
            }
            i++;
        }

        i=0;
        for(group g : new_groups)
        {
            if(rain_bow_size[i]== max_rain_bow && g[0]/n  == max_y && max_x == g[0]%n)
            {
                break;                    
            }
            i++;
        }
        //이게 파괴할 블럭
        for(int ii: new_groups[i])
        {
            #if debug
            cout<<"delete :" << ii/n <<" "<< ii%n<< " "<< t[ii]<<endl;
            #endif

            t[ii]= -7;
            ret++;

        }

        #if debug
        cout<<endl;
        for(int i=0; i<n ; i++)
        {
            for(int j=0; j<n; j++)
                cout<<t[i*n+j]<<"   ";
            cout<<endl;
        }
cout<<endl;
#endif

        score += ret*ret;
    }

    void gravity()
    {
        
        for(int i=n-2; i>=0 ; i--)
        {
            for(int j=0; j<n; j++)
            {
                if( t[i*n+j] != -7 && t[i*n+j] != -1)
                for(int k=i+1; k<n; k++) //지금 좌표부터 밑을 조사
                {
                    if(t[k*n+j] == -1)
                        break;

                    if(t[k*n+j] == -7)
                    {
                        t[k*n+j] = t[(k-1)*n+j];
                        t[(k-1)*n+j] = -7;
                    }                                        
                }
            }
        }
#if debug
        cout<<endl;
        for(int i=0; i<n ; i++)
        {
            for(int j=0; j<n; j++)
                cout<<t[i*n+j]<<"   ";
            cout<<endl;
        }
#endif
    }

    void lotate()
    {
        vector<int> nt(n*n);
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                nt[  (n-1-j)*n +i] = t[ i*n+j];
            }
        }
        t= nt;
    }

    int sol()
    {
        input();
        while(!end)
        {
            search_group();
            if(end) break;
            delete_block();
            gravity();
            lotate();
            gravity();
        }
        return score;

    }

};


int main()
{
    game gg;
    cout<<gg.sol();

    return 0;
}