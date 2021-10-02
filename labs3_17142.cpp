//연구소 3 다시풀기 8시 40분
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;
#define debug 0
int dx[4] ={ -1, 0, 1, 0};
int dy[4] ={  0, 1, 0, -1 };
class lab
{
    public:
    int n, m;
    vector<int> t;
    vector<int> vis;
    int blac=0;
    int time;

    void input()
    {
        cin>>n >> m;
        t= vector<int>(n*n);
        for(int i=0; i<n*n; i++){             
            cin>> t[i];
            if(t[i]==2) vis.push_back(i);
            if(t[i]==0) blac++;
        }
    }

    int spread(vector<int> selected)
    {
        vector<int> nt =t; //퍼진 후 멥
        queue<int> q_vis;

           
        vector<int> sp_t(n*n); //각 칸에 퍼진 시간을 기록
        int spread_time=0;

        int sp_area=0;
#if debug
cout<<"\n selected :" ;
#endif
        for(int i: selected) //활성 비이러스로 바꾸기, 활성 바이러스는 4로 표시
        {
            nt[i] = 4;
            q_vis.push(i);
#if debug
cout<<i<<" ";
#endif
        }

        while(!q_vis.empty())
        {
            int cur = q_vis.front();
            q_vis.pop();
            int x = cur%n;
            int y = cur/n;

            for(int j=0; j<4 ;j++)//현재 위치를 기준으로 4방향 조사
            {

                int nx= x+dx[j];
                int ny= y+dy[j];

                if(nx>=n || nx<0 || ny>=n || ny<0 ) continue; //큐에 넣을 필요 없는놈들
                if(nt[ny*n+nx]==1 || nt[ny*n+nx]==4) continue;

                if(t[ny*n+nx]==0) sp_area++;    
                sp_t[ny*n+nx] = sp_t[cur]+1; // 이 칸에 최초로 퍼진 시간은, 이칸을 퍼트린 놈의 시간 +1 
                if( spread_time < sp_t[cur]+1  && t[ny*n+nx]==0 ) spread_time = sp_t[cur]+1 ;       


                // 저 조건들을 제외하면 0 또는 2(비 활성 바이러스) 
                nt[ny*n+nx] = 4; //활성 시켜주고
                q_vis.push(ny*n+nx); //다음에 여기서부터 뻗어가도록 추가
            }


#if debug
    cout<<endl;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
        char a;
        if(t[i*n+j]==1) a='-';
        else if(t[i*n+j]==2) a='*';
        else a= to_string(sp_t[i*n+j])[0];
            cout<< a<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
#endif  

        }
    
        if(sp_area == blac)
            return spread_time;
        else
            return -1;

    }




    int sol()
    {
        input();

        // if(vis.size()==0 && blac !=0) return -1;
        if(blac ==0) return 0;

        //vis 중에 m개를 선택
        int min_time=999999;
        int time;
        vector<int> selected;
        vector<bool> combintaion;
        for(int i=0; i<m; i++)
            combintaion.push_back(1);
        while(combintaion.size() < vis.size()) combintaion.push_back(0);

        sort(combintaion.begin(), combintaion.end());
        do
        {
            for(int i=0; i<combintaion.size(); i++)
                if(combintaion[i]) selected.push_back(vis[i]);
            
            time= spread(selected);
            if(time <min_time && time != -1) min_time=time;
            
            selected.clear();
            selected.resize(0);

        }while(next_permutation(combintaion.begin(), combintaion.end()));

    if(min_time != 999999)    
        return min_time;
    else   
        return -1;
    }

};

int main()
{
    lab l;

    cout<<l.sol();

    return 0;
}