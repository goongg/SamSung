//1시 40분
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define debug 0

//찾는 순서는 행번호가 가장 낮고, 그중 열번호가 가장 낮고
int dx[4]={0 ,-1 ,1 ,0 };
int dy[4]={-1, 0 ,0 ,1 };

class man
{
    public:
    int y, x, d_y, d_x; ///위치와 도착지
};

class taxi
{
    int fuel; //연료
    vector<int> t; // 맵
    int n, m;
    int t_x, t_y; //택시 위치 
    vector<man> mans;   //승객 정보

    int next_dest=0;

    public:

    void input()
    {
        cin>>n>>m>>fuel;
        t= vector<int>(n*n);
        mans= vector<man>(m);
        for(int i=0; i<n*n; i++) cin>> t[i];
        cin>>t_y>>t_x;

        t_y--; 
        t_x--;

        for(int i=0; i<m; i++){
            cin>> mans[i].y >>mans[i].x >> mans[i].d_y >> mans[i].d_x;
            mans[i].y--;
            mans[i].x--;
            mans[i].d_y--;
            mans[i].d_x--;
        }
    }

    int search_min(int from, int to)
    {
        queue<int> q;
        vector<bool> visit(n*n);
        vector<int> dis(n*n);

        q.push(from);
        visit[from]= 1;

        if(from == to) return 0;

        while(!q.empty())
        {
            int cur= q.front();
            q.pop();
            //4방향 조사
            for(int d=0; d<4; d++)
            {
                int nx= cur % n + dx[d];
                int ny= cur / n + dy[d];

                if( nx <0 || nx >=n || ny <0 || ny >=n ) continue;
                if(t[ny*n + nx] ==1 || visit[ny*n + nx]) continue;
                
                visit[ny*n + nx]=1;
                dis[ny*n + nx] = dis[cur] +1;
                if(ny*n + nx == to )
                    return dis[ny*n + nx];
                
                q.push(ny*n + nx);
            }
        }
        return -1;
    }

    int search_man()
    {
        int dis_min= 999999;
        vector<int> dis_buf;
        int min_x= 999999;
        int min_y= 999999;
        
        vector<man> nmans;
        //현재위치에서 승객과의 최소 거리 찾기
        for(int j =0 ; j< mans.size(); j++)
        {   
            dis_buf.push_back( search_min(t_y*n + t_x,  mans[j].y*n + mans[j].x ) );
            if(dis_buf.back() != -1 && dis_min > dis_buf.back() )
                dis_min = dis_buf.back();
            
        }

        for(int j =0 ; j< mans.size(); j++)
            if(dis_buf[j] == dis_min)
                if(min_y > mans[j].y) min_y= mans[j].y;

        for(int j =0 ; j< mans.size(); j++)
            if(dis_buf[j] == dis_min && min_y == mans[j].y)
                if(min_x > mans[j].x) min_x= mans[j].x;

#if debug
cout<<"\ndis_min:" << dis_min  <<" " << min_y+1<<" "  <<min_x+1 <<endl;
#endif
        if(dis_min == 999999)   //모든 승객에게 도달할 수 없는 경우
            return -1;
        

        //최단 거리 승객 중, 가장 행이 낮고 열이 낮은 승객 찾기     
        for(int j =0 ; j< mans.size(); j++)
        {
            if(mans[j].x== min_x && mans[j].y==min_y && dis_buf[j]==dis_min)
            {
                next_dest= mans[j].d_y*n + mans[j].d_x;
                t_x= mans[j].x;
                t_y= mans[j].y;
                fuel -= dis_min;
            }
            else
                nmans.push_back(mans[j]);            
        }
        mans= nmans;

#if debug
cout<<"search man r c fuel:" <<t_y+1 <<" "<< t_x+1<<" "<<fuel<<endl;
#endif
if(fuel>=1)
        return fuel;
else
        return -1;
    }

    int search_dest()
    {
        int dis_min= 999999;
        int dis_buf;

        //현재위치에서 목적지 까지 거리 찾기
        dis_buf= search_min(t_y*n + t_x,  next_dest);
        if(dis_buf ==-1 || fuel - dis_buf <0) return -1;
        else
            fuel += dis_buf;

#if debug
cout<<"\ndis:" << dis_buf  <<endl;
#endif

        t_x= next_dest % n;
        t_y= next_dest / n;

#if debug
cout<<"search dest r c fuel:" <<t_y+1 <<" "<< t_x+1<<" "<<fuel<<endl;
#endif

        return fuel;
    }

    int sol()
    {
        input();
        int ret;
        for(int i=0; i<m ;i++)
        {
            ret= search_man();
            if(ret == -1) return -1;
            ret= search_dest();
            if(ret == -1) return -1;
        }
        return ret;
    }

};


int main()
{
    taxi tt;

    cout<<tt.sol();
    
    return 0;
}