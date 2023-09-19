#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct how
{
    int x;
    int d;
    int k;
};

int dr[4]= {-1, 0, 1, 0};
int dc[4]= { 0, 1, 0, -1};

class Board
{   
    public:
    int N, M, T;
    vector<vector<int> > cir;
    queue<how> q;
    void rotate(int n, int d) // n 번쨰 원판을 d만큼
    {
        vector<int> nn;
        if(d==0)
        {
            nn.push_back(cir[n][ cir[n].size() -1]);
            for(int i=0; i<cir[n].size()-1; i++)
                nn.push_back(cir[n][i]);
        }
        else
        {
            for(int i= 1; i<cir[n].size(); i++)
                nn.push_back(cir[n][i]);
            nn.push_back(cir[n][0]);
        }
        cir[n]= nn;
    }

    void print()
    {
        int n=1;
        cout<<"print\n";
        for(vector<int> v : cir)
        {
            cout<<endl;
            cout<<n++<<"번째: ";
            for(int i : v)
                cout<<i<<" ";
        }
    }

bool visit[100][100];
bool is_delete;
    int solve()
    {
        int up_down;
        float result;
        float aver;
        input();
        int cnt=1;
        while(!q.empty()){
            how h = q.front();
            q.pop();

            for(int n = h.x; n<=N ; n+=h.x )
            {
                for(int k=0; k< h.k; k++)
                    rotate(n-1, h.d);
            }
            // cout<<cnt++<<" 회전후-----------------------\n";
            // print();

            for(int i= 0; i<N; i++)
                for(int j=0; j<M; j++)
                    visit[i][j] =0;
            is_delete=0;
            for(int i= 0; i<N; i++)
                for(int j=0; j<M; j++)
                {
                    // cout<<"\ndfs start"<<i+1<<" "<<j+1<<"------------------\n";
                    if(cir[i][j] !=0)
                        dfs(i, j, cir[i][j] );
                    
                }

            result=0;
            aver=0;
            for(int i= 0; i<N; i++)
                for(int j=0; j<M; j++)
                {
                    if(cir[i][j] !=0)
                    {
                        aver++;
                        result+=cir[i][j];
                    }
                }

             up_down=0;
            if(is_delete==0)
            {

                // cout<<"\n이케이스에 삭제없었\n";
                for(int i= 0; i<N; i++)
                    for(int j=0; j<M; j++)
                    {
                        if(cir[i][j] ==0) continue;
                        if((float)cir[i][j] > result/aver)
                        {
                            cir[i][j]--;
                            up_down--;
                        }
                        else if ((float)cir[i][j] < result/aver)
                        {
                            cir[i][j]++;
                            up_down++;
                        }

                    }
            }
            // cout<<"\n후처리\n";
            // print();
// 
            // cout<<"\n\n";


        }

        return result+up_down;
    }

    void dfs(int r, int c, int num) //r이 원판번호, c가 숫자번호
    {
        int nr;
        int nc;   
            // cout<<r+1<<", "<<c+1 <<" serch \n";
        for(int d=0; d<4 ;d++ )
        {
            if(r==0 && d==0) continue; // 0번의 경우 자기안쪽 원판 조사할필요없음
            if(r==N-1 && d==2) continue; // 마지막원판 경우 자기밖쪽 원판 조사할필요없음
            nr = (r + dr[d] + N)%N;
            nc = (c + dc[d] + M)%M;

            if(visit[nr][nc]) continue;

            if( cir[nr][nc] !=0 && cir[nr][nc] == num)
            {
                // cout<<nr+1<<", "<<nc+1 <<"과 동일\n";
                visit[nr][nc] =1;

                cir[nr][nc] =0;
                is_delete=1;
                dfs(nr, nc, num );
            }
        }
    }

    void input()
    {
        cin>> N>>M>>T;
        for(int i =0; i<N; i++)
        {
            vector<int> v;
            v.clear();
            for(int j=0; j <M ; j++)
            {
                int a;
                cin>>a;
                v.push_back(a);
            }
            cir.push_back(v);
        }
        for(int i=0; i< T ; i++)
        {
            how h;
            cin>>h.x>>h.d >>h.k;
            q.push(h);
        }

    }

};

int main()
{
    Board c;
    cout<<c.solve();
    return 0;



}