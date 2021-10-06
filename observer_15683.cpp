//6시 50분 2시간컷 해보자!
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define debug 0

int dx[4] = {-1, 0 ,1, 0};
int dy[4] = {0, -1, 0 ,1};


class room
{
    int n ,m;
    vector<int> t;

    vector<int> cctv;       //cctv의 위치 저장
    vector<int> cctv_d;     //cctv의 방향 저장  왼, 위, 오, 아

    int view_num=0;
    vector<bool> visit;

    int blac=0;
public:
    void input()
    {
        cin>>n>>m;
        t= vector<int>(n*m);
        for(int i=0; i< n*m; i++)
        {
            cin>>t[i];
            if(t[i]>=1 && t[i]<=5)
            {
                cctv.push_back(i);
                cctv_d.push_back(0);
            }
            if(t[i] ==0)
                blac++;
            
        }
    }

    void view(int cur, int d)
    {
        int x= cur%m;
        int y= cur/m;
        int nx = x ;
        int ny = y ;
        // cout<<"view"<<endl;
        while(1)
        {
            // cout <<d<<" ";
            nx+= dx[d];
            ny+= dy[d];
            int next =  ny*m + nx;
            if(nx <0 || nx>=m || ny<0 || ny >= n ) break;
            if( t[next] == 6 ) break;
            if(t[next] ==0) visit[next] = 1;
        }
        // cout<<endl;

    }

    int clac()
    {
        visit.clear();
        visit.resize(n*m);
        int ret=0;
        for(int i=0; i< cctv.size() ;i++)
        {
            int cur= cctv[i];
            // cout<<"cur:"<< cur/m <<" " << cur%m  <<" "<< t[cur]<<endl;

            switch(t[cur])
            {
                case 1:
                    view(cctv[i],  cctv_d[i]);
                    break;

                case 2:
                    view(cctv[i], cctv_d[i]);
                    view(cctv[i], (cctv_d[i] +2 )%4 );
                    break;

                case 3:
                    view(cctv[i], cctv_d[i]);
                    view(cctv[i], (cctv_d[i] +1)%4 ) ;
                    break;
                case 4:
                    view(cctv[i], cctv_d[i]);
                    view(cctv[i], (cctv_d[i] +1)%4 ) ;
                    view(cctv[i], (cctv_d[i] +2)%4 ) ;
                    break;
                case 5:
                    view(cctv[i], cctv_d[i]);
                    view(cctv[i], (cctv_d[i] +1)%4 ) ;
                    view(cctv[i], (cctv_d[i] +2)%4 ) ;
                    view(cctv[i], (cctv_d[i] +3)%4 ) ;
                    break;
            }
        }
        for(bool i: visit)
            if(i) ret++;

#if debug
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<m; j++)
                cout<<visit[i*m+j]<<" ";
            cout<<endl;
        }
#endif

        return ret;
    }
    int dfs_min=99999998;

    void dfs(int level)
    {

        if(cctv.size() ==0) {
            dfs_min= blac;
            return;
        }
        if(level == cctv.size()) 
        {
            
            int buf;
            buf= blac- clac();

            #if debug
            cout<<"dfs종료 방향들"<<endl;
            for(int i: cctv_d)
                cout<<i<<" ";
            cout<<"결과:"<<buf<<endl<<endl;
            #endif

            if(buf < dfs_min) dfs_min= buf;

            return ;
        }

        switch( t[cctv[level]] )
        {

            case 1:     //네방향존재
            for(int i=0; i<4; i++)
            {    
                cctv_d[level] = i;
                    dfs(level+1);                    
            }
            break;

            case 2: //두방향 존재
                for(int i=0; i<2; i++)
                {    
                    cctv_d[level] = i;
                        dfs(level+1);                    
                }
            break;

            case 3: //네방향
              for(int i=0; i<4; i++)
                {    
                    cctv_d[level] = i;
                        dfs(level+1);                    
                }
            break;

            case 4: //네방향
                for(int i=0; i<4; i++)
                {    
                    cctv_d[level] = i;
                        dfs(level+1);                    
                }
            break;

            case 5: //한방향
                cctv_d[level] = 0;
                dfs(level+1);                    
            break;
        }


    }


    int sol()
    {
        input();
        dfs(0);

        return dfs_min;
    }

    
};
int main()
{

room r;
cout<< r.sol();
    return 0;
}