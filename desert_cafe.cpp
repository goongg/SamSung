#include <iostream>
#include <vector>

using namespace std;

int T, N;
int map[21][21];
int visit[21][21];
int cur_tour;
int max_length=-1;
vector<int> ret;

int dr[4] ={ 1,  1, -1, -1};
int dc[4] ={-1,  1,  1, -1 };

bool check(int r, int c, int w, int h)
{
    int nr=r;
    int nc=c;
    bool eated[101];
    for(int i =0; i<101; i++) eated[i]=0;
    eated[map[r][c]]=1;
    for(int d=0; d<4; d++)
    {
        int wh;
        if(d==0 || d==2)
            wh =w;
        else if(d==1||d==3)
            wh =h;

        for(int i=0; i<wh; i++)
        {
            nr+=dr[d];
            nc+=dc[d];
            if(nr == r && nc ==c) return 1;

            if(nr<0 || nc <0 || nr>=N || nc >=N) return 0;
            
            if(eated[map[nr][nc]]) return 0;
            
            eated[map[nr][nc]]=1;
        }
    }
    return 1;
}

int main()
{
    cin>>T;
    while(T-- >0)
    {
        cin>>N;
        for(int i =0; i< N ; i++)
            for(int j =0; j<N; j++)
                cin>>map[i][j];
            
        max_length=-1;

        for(int i =0; i<N; i++)
        {
            for(int j =0; j<N; j++)
            {
                for(int ww=1 ; j-ww >=0; ww++)
                {
                    for(int hh=1; i+ww+hh < N; hh++)
                    {
                        // cout<<i<<" "<<j<<"에서" <<ww<<" " <<hh<<"조사\n";
                        if( check(i,j, ww, hh))
                            max_length = max(max_length, (ww+hh)*2);
                        
                    }
                }
            }
        }
        ret.push_back(max_length);
    }

    for(int i=0; i< ret.size(); i++)
    {
        cout<<"#"<<i+1<<" "<<ret[i]<<endl;
    }
    return 0;
}