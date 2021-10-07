//5시 40분
#include <iostream>
#include <vector>
#include <queue>
#define debug 0


using namespace std;

int u_dx[4]= {1, 0, -1, 0}; //오, 위, 왼, 아
int u_dy[4]= {0, -1, 0, 1};

int d_dx[4]= {1, 0, -1, 0}; //오, 아, 왼, 위
int d_dy[4]= {0, 1, 0, -1};

class room
{
    int n, m, T;
    vector<int> t;
    vector<int> cleaner;

    vector<int> dust;

    public:
    void input()
    {
        cin>>n>>m>>T;
        t = vector<int>(n*m);
        for(int i=0; i<n*m; i++)
        {
            cin>>t[i];
            if(t[i] == -1)
                cleaner.push_back(i);

            else if(t[i] != 0)
                dust.push_back(i);
        }
    }
    void spread()
    {

        vector<int> nt(n*m);
        for(int i : dust)
        {
            int x = i%m;
            int y = i/m;
            int cnt=0;
            for(int j=0; j<4; j++)//네방향 조사
            {
                int nx= x+ u_dx[j];
                int ny= y+ u_dy[j];
                int next= ny*m +nx;
                if(nx < 0 || nx >=m || ny <0 || ny >=n) continue;
                if(t[next]==-1) continue;

                cnt++;
                nt[next] += t[i]/5;    
                // cout<<t[i]<<endl;
            }

            nt[i] -= (t[i]/5)*cnt;

        }
        for(int i=0; i<n*m; i++)
            if(t[i] !=-1) t[i] += nt[i];
        

#if debug
cout<<"\nspread"<<endl;
    for(int i=0; i< n; i++)
    {
        for(int j=0; j<m ; j++)
            cout<< t[i*m+j] <<" ";
        cout<<endl;
    }
    cout<<endl;
#endif
    }

    int blow()
    {
        int ret=0;
        int x = 0;

        int up_y = cleaner[0]/m;
        int down_y = cleaner[1]/m;

        vector<int> nt(n*m);

        nt[cleaner[0]]= -1;
        nt[cleaner[1]]= -1;
        
        nt[up_y*m + 1] =0; 

        for(int j= +1; j<m-1; j++)
            nt[up_y*m + j+1] =t[up_y*m +j];

        nt[(up_y-1)*m + m-1] = t[up_y*m + m-1];

        for(int i=up_y-1; i>=1; i--)    //위 이동
            nt[(i-1)*m + m-1]= t[i*m + m-1];

        nt[(0)*m + m-2] = t[0*m + m-1];

        for(int j= m-1; j>=1; j--)
            nt[0*m + j-1] =t[0*m +j];


        for(int i=0; i<= up_y -2 ; i++)    //위 이동
            nt[(i+1)*m + 0]= t[i*m + 0];



        nt[down_y*m + 1] =0; 

        for(int j= 1; j<m-1; j++)
            nt[down_y*m + j+1] =t[down_y*m +j];

        nt[(down_y+1)*m + m-1] = t[down_y*m + m-1];

        for(int i=down_y; i<n-1; i++)    //아래 이동
            nt[(i+1)*m + m-1]= t[i*m + m-1];

        nt[(n-1)*m + m-2] = t[(n-1)*m + m-1];

        for(int j= m-1; j>=1; j--)
            nt[(n-1)*m + j-1] =t[(n-1)*m +j];

        for(int i=n-1; i> down_y +1 ; i--)    //위 이동
            nt[(i-1)*m + 0]= t[i*m + 0];




for(int i=1; i< up_y; i++)
{
    for(int j =1; j< m-1; j++)
       nt[i*m+j] = t[i*m+j];
}

for(int i=down_y+1; i< n-1; i++)
{
    for(int j =1; j< m-1; j++)
       nt[i*m+j] = t[i*m+j];
}


t= nt;

dust.clear();
dust.resize(0);
for(int i =0; i<n*m; i++)
if( t[i] !=0 && t[i] != -1) dust.push_back(i);


#if debug
cout<<"\nblow"<<endl;
    for(int i=0; i< n; i++)
    {
        for(int j=0; j<m ; j++)
            cout<< nt[i*m+j] <<" ";
        cout<<endl;
    }
    cout<<endl;
#endif
   

   for(int i=0; i<n*m; i++)
    {
        if( nt[i] != -1)
            ret += nt[i];
    }

    return ret;

}
    int sol()
    {
        int ret;
        
        input();

        for(int i=0; i<T; i++){
            spread();
            ret = blow();
        }
        return ret;
    }
};  
int main()
{
    room r;
    cout<< r.sol();

    return 0;
}
