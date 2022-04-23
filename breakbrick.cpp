#include<iostream>
#include <vector>
using namespace std;

#define debug 1

int dx[4] ={-1, 0, 1, 0};
int dy[4] ={ 0, 1, 0, -1};

class game 
{
    public:
        int N, W, H; //특히 W랑 H가 다른경우
        int t[15][12]; 
        vector<vector<int> > selected;
        void input(){
            cin>>N>>W>>H;
            
            for(int i=0; i<H; i++)
                for(int j=0; j<W; j++)
                    cin>>t[i][j];

            selected.clear();
        }

        void select() //0~ W개 중에서 N개의 순열을 만드는 함수, 결과를 vector< vector<int> > selected; 전역으로 여기 넣음
        {
            vector<bool> visit;
            visit.clear();
                for(int i=0; i< W; i++) visit.push_back(0);
            vector<int> arr;
            permutation(visit, arr);
        }

        void  permutation( vector<bool> visit, vector<int> arr)
        {
            if(arr.size() == N)
            {
                selected.push_back(arr);
                return;
            }

            for(int i = 0; i<W; i++)
            {
                arr.push_back(i);
                permutation(visit, arr);
                arr.pop_back();
            }
        }

        int solve()
        {
            int mmin= 999999;
            int buf;
            input();
            select();
            int tt[15][12]; 
            for( int i=0; i<H; i++)
                for(int j=0; j<W; j++)     
                    tt[i][j] = t[i][j];

            for(vector<int> vv : selected)
            {

                for( int i=0; i<H; i++)
                    for(int j=0; j<W; j++)     
                        t[i][j] = tt[i][j];

                // cout<<"\nfalling :";
                for(int ii : vv)
                {
                    // cout<<ii<< " ";
                    falling(ii);
                    gravity();
                }
                buf= cnt();
                if(buf<=mmin) mmin= buf;
            }

            return mmin;
        }

        void falling(int ball)
        {
            int x = ball;
            int y =-1;
            while(1)
            {
                y+=1;
                if(y>=H) break;
                if(t[y][x] ==0)
                    continue;
                if(t[y][x] !=0)
                {
                    dfs( x,  y);                
                    return;
                }
            }
        }

        void dfs(int x, int y)
        {
            int range = t[y][x];
            t[y][x]=0; //방문처리 역할도 겸
            if(range ==1) return;

            for(int d=0; d< 4; d++)
            {
                int nx= x;
                int ny= y;
                for(int r=1; r< range; r++)
                {
                    ny += dy[d];
                    nx += dx[d];

                    if(nx >= W || ny >= H || nx <0 || ny<0) break;
                    if( t[ny][nx]>1)
                    {
                        dfs(nx, ny);
                    }
                    else if( t[ny][nx] ==1)
                    {
                        t[ny][nx]=0;
                        continue;
                    }
                    else if( t[ny][nx] ==0)
                    continue;                            
                }        
            }
        }

        void gravity()
        {
            for(int i=H-1; i>0; i--)
            {
                for(int j=0; j<W; j++)
                {
                    int nx =j;
                    int ny =i;
                
                    if(t[i][j] ==0)
                    {
                        while(1)//위애 0이 아닌곳을 찾아 일로끌고오기
                        {
                            ny-=1;
                            if(ny<0) break;
                            if(t[ny][nx] !=0)
                            {
                                t[i][j] = t[ny][nx];
                                t[ny][nx]=0;
                                break;
                            }
                        }
                    }
                }
            }
        }
        int cnt()
        {
            int point =0;
            for( int i=0; i<H; i++)
                for(int j=0; j<W; j++)     
                    if(t[i][j] !=0) point++;
            return point;
        }
};


int main(int argc, char** argv)
{
	int test_case;
	int T;

    game g;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cout<<"#"<<test_case<<" "<<g.solve()<<"\n";
       
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}