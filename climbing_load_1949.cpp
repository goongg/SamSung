//10시 30분
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dx[4]={-1, 0, 1, 0};
int dy[4]={ 0, 1, 0, -1};

class mount
{
    int n, k;  
    vector<bool> visit;
    vector<int> load_length;
    int dfs_max= -1;
    vector<int> map;
    vector<int> init_map;
    public: 
    void input()
    {
        cin>>n>>k;
        map= vector<int>(n*n);
        
        for(int i=0; i< n*n; i++) cin>>map[i];
        visit= vector<bool>(n*n);
        init_map= map;
        load_length= vector<int>(n*n);
    }
    int search_load()   //가장 높은 봉우리를 찾아서 등산로를 결정하는 함수 /dfs
    {
        vector<int> highst; // 가장 높은 봉우리를 저장하는 벡터
        int high_max= -1;
        int load_max = -1; // 가장 긴 등산로

        for(int i=0; i< n*n; i++)
            if(high_max < init_map[i]) high_max = init_map[i];

        for(int i=0; i< n*n; i++)
        {
            if(high_max  == init_map[i])
            {
                highst.push_back(i);
                // cout<< i<<" ";
            }
        }

        // cout<<"\n\n";
        // for(int i=0; i<n; i++){
        //     for(int j=0; j<n; j++)
        //         cout<<map[i*n+j]<<" ";
        //     cout<<endl;
        // }
        // cout<<"\n\n";

        for(int i=0; i< highst.size(); i++)
        {
            // cout<<"dfs_start:"<<endl;

            for(int j=0; j<n*n; j++)
                visit[j]=0;

            for(int j=0; j<n*n; j++)
                load_length[j]=0;

            visit[highst[i]]=1;
            load_length[highst[i]]=1;

            dfs_max = -1;       
            int buf = dfs(highst[i]);
            // cout<< buf<<endl;
            if(load_max< buf) load_max= buf;
        }

        return load_max;
    }
    
    int dfs(int cur)
    {
        int mmax= -1;
        int buf;
        // cout<<"cur: "<<cur/n <<" "<< cur%n <<endl;
        //네방향 조사
        for(int d=0 ; d<4 ; d++)
        {
            int x = cur % n;
            int y = cur / n;
            int nx = x +dx[d];
            int ny = y +dy[d];
        // cout<<"next: "<<ny <<" "<< nx <<visit[ny*n + nx ] <<endl;

            if( nx <0 || nx >=n || ny <0 || ny >=n) continue;
            if( visit[ny*n + nx ]) continue;

            if( map[ny*n + nx] < map[cur]  ) //다음이 더 작으면 노드 뻗기
            {
                // cout<<"뻗음:"<<d<<" "<< ny<<" "<< nx<<endl;
                load_length[ny*n + nx] = load_length[cur] + 1;
                visit[ny*n + nx]=1;
                if(dfs_max < load_length[ny*n + nx])
                    dfs_max= load_length[ny*n + nx];

                dfs(ny*n + nx);
                visit[ny*n + nx]=0;
                load_length[ny*n + nx] -= load_length[cur] + 1;
            }
        }
        // cout<<"end:"<< dfs_max<<'\n';
        return dfs_max;
    }

    int sol()
    {
        int ret;
        int ret_max= -1;
        input();
       // ret_max= search_load(); //안깍았을떄, 최대길이

        for(int kk= 1; kk<=k ; kk++)   //k 개만큼 깍으면서 구하기
        {
            for(int i=0; i< n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    // cout<<"\n------------------------------\n";
                    // cout<<kk<<" "<< i<<" "<< j<<endl;
                    map[i*n +j] -=kk;  //k만큼 깍은 맵
                    if(map[i*n +j] >=0)
                    	ret = search_load(); // 그맵에서 결과 내기
                    map[i*n +j] += kk; //원상복귀
                    if(ret_max < ret) ret_max= ret;
                }
            }
        }
        return ret_max;
    }

};




int main()
{
mount m;

cout<< m.sol();

    return 0;
}
