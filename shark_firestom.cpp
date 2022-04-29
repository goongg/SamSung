#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = { 0, 1, 0, -1};

class Room
{
    public:
    int t[64][64];
    int N;
    int Q;

    int M;

    queue<int> L;

    void input()
    {

        cin>>N >>Q;
        M=1;
        for(int i=0 ; i<N; i++)
            M*=2;
        
        for(int i=0 ; i<M ; i++)
            for(int j=0; j<M ; j++)
                cin>>t[i][j];

        for(int i=0; i<Q; i++)
        {
            int n;
            cin>>n;
            L.push(n);
        }

        // cout<<M;
    }  
    
    void print()
    {
        cout<<"\nprint\n";
        for(int i = 0 ;i <M; i++ ){
            for(int j=0; j< M ; j++)
                cout<<t[i][j] <<" ";
            cout<<endl;
        }
    }
    void stom(int l)
    {
        int len = 1;
        for(int i=0 ; i<l; i++)
            len*=2;

        for(int i=0; i<M; i+= len)
            for(int j=0; j<M; j+= len)
                rotate(i, j, l);

    }
    void rotate(int r, int c, int l)
    {
        int len = 1;
        for(int i=0 ; i<l; i++)
            len*=2;

        int nt[64][64];
        int tt[64][64];

        for(int i=r; i<r+ len ; i++)
            for(int j=c; j<c +len ; j++ )
                tt[i-r][j-c] = t[i][j];


        for(int i=0; i<len ; i++){
            for(int j=0; j<len ; j++ )
                nt[j][len-1 -i] = tt[i][j];
        }


        for(int i=0; i< len ; i++)
            for(int j=0; j<len ; j++ )
                t[i+r][j+c] = nt[i][j];
    }
    int check(int r, int c)
    {
        if(t[r][c] ==0) return 0;
        int s=0;
        for( int d=0; d<4 ; d++)
        {
            int nr= r+dr[d];
            int nc= c+dc[d];
            if(nr <0 || nr >=M || nc <0 || nc >=M) continue;

            if(t[nr][nc] != 0) s++;
        }

        if(s <3) return -1; 

        else return 0;
    }

    int solve()
    {
        input();
        
        int ice=0;
        int nt[64][64];

        // print();
        while(!L.empty())
        {
            int ll= L.front();
            L.pop();
            stom(ll);
            // print();

            // cout<<"L :" <<ll<<endl;
            for(int i =0 ; i<M; i++)
                for(int j=0; j< M; j++)
                    nt[i][j] = check(i, j);
            

            for(int i =0 ; i<M; i++)
                for(int j=0; j< M; j++)
                        t[i][j] += nt[i][j];

                        // print();
        }
        
            for(int i =0 ; i<M; i++)
                for(int j=0; j< M; j++)
                    {
                        visit[i][j] =0;
                        ice += t[i][j];
                    }
        cout<<ice<<endl;

        max=0;
        // size=0;
        for(int i =0 ; i<M; i++)
            for(int j=0; j< M; j++)
            {   
                if(t[i][j] ==0) continue;
                if(visit[i][j]) continue;

                // cout<<"----------------------\n";
                visit[i][j] =1;
                size=1;
                dfs(i,j);  
                if(max < size) max = size;
            }
        // if(max == -1) max =0;
        return max;
    }

    bool visit[64][64];
    int max ;
    int size;

    void dfs(int r, int c)
    {
        for(int d=0; d <4 ; d++)
        {
            int nr= r + dr[d];
            int nc= c + dc[d];
            if(nr <0 || nr >=M || nc <0 || nc >=M) continue;
            if(t[nr][nc] ==0 || visit[nr][nc]) continue;

            size++;
            visit[nr][nc] =1;
            dfs(nr, nc);
        }
    }

};


int main()
{
Room r;
cout<< r.solve();
    return 0;
}