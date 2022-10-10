#include<iostream>
#include <vector>
using namespace std;

int dr[5] ={0, -1, 1, 0,  0 };
int dc[5] ={ 0, 0, 0, -1, 1 };
#define uu 1
#define dd 2
#define ll 3
#define rr 4


class virus
{
    public:
    int r, c;
    int d;
    int n;
};
vector<virus> vv;
	int test_case;
	int T;
    int N, M, K; //맵, M시간후, K 미생물 갯수

int map[100][100];
int n_map[100][100];
int buf[100][100];

void print()
{

    cout<<"\n미생물 정보\n";
    for(int i =0 ;i<N; i++){
        for(int j =0 ;j <N; j++)                
        {
            cout<< n_map[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"군집 수 \n";
    for(int i =0 ;i<N; i++){
        for(int j =0 ;j <N; j++)                
        {
            if(n_map[i][j] !=0)
            cout<< vv[n_map[i][j]].n<<" ";
            else
            cout<< 0<<" ";

        }
        cout<<endl;
    }

}
int main(int argc, char** argv)
{

	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin>>N>>M>>K;
        virus v;
        vv.clear();
        vv.resize(K+1);
        for(int i=1; i<=K; i++)
        {
            cin>>v.r >> v.c >> v.n >> v.d;
            vv[i]=v;
            map[v.r][v.c]=i;
        }
        int cnt=0;

        while(M-- >0)
        {
            cnt=0;
            for(int i =0 ;i<N; i++)
                for(int j =0 ;j <N; j++)                
                {
                    buf[i][j]=0;
                    n_map[i][j]=0;
                }
            
            //미생물의 이동
            for(int i=1; i<=K; i++)
            {
                if(vv[i].n==0) continue;

                int r = vv[i].r;
                int c = vv[i].c;
                int d = vv[i].d;

                int nr = r+dr[d];
                int nc = c+dc[d];

                if(nr==0 || nc==0 || nc==N-1 || nr ==N-1)
                {
                    if(d == uu) d= dd;
                    else if(d== dd) d=uu;
                    else if(d==rr) d=ll;
                    else d=rr; 
                    vv[i].n/=2;
                    vv[i].d=d;
                }
                if(vv[i].n ==0) continue;

                vv[i].r=nr;
                vv[i].c=nc;
                vv[i].d=d;
                cnt+=vv[i].n;
                if(n_map[nr][nc] == 0)
                    n_map[nr][nc] = i;
                
                else
                {
                    if(vv[n_map[nr][nc]].n > vv[i].n ) //먼저 이동해 있는 군집이 있고 걔가 더 세면
                    {
                        buf[nr][nc] += vv[i].n; //지금 애를 버퍼에 저장
                        vv[i].n=0;   
                    }
                    else //지금 군집이 더 쎼면
                    {
                        buf[nr][nc] += vv[n_map[nr][nc]].n; //원래 있던애를 버퍼에 저장
                        vv[n_map[nr][nc]].n=0;
                        n_map[nr][nc] = i; //더 쎈 지금 애를 마킹
                    }
                }
            }

            for(int i =0 ;i<N; i++)
                for(int j =0 ;j <N; j++)                
                {
                    if(n_map[i][j] !=0 && buf[i][j]!=0)
                    {
                        vv[n_map[i][j]].n+=buf[i][j];
                    }
                }

    	}



    cout<<"#"<<test_case<<" "<<cnt<<endl;
    }
	return 0;

}