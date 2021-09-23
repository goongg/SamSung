#include <iostream>
#include <vector>
using namespace std;

#define debug 0

int dx[8] ={ 0, 1, 1, 1, 0,-1,-1,-1};
int dy[8] ={ -1,-1,0, 1, 1, 1, 0, -1};

class fireball
{
    public:
    int r, c, m, s, d;
};

class shark
{
    int N,M,K;
    vector<vector<fireball>> map;
    public:
        void init()
        {
            fireball f;
            cin>>N>>M>>K;
            map=vector< vector<fireball>>(N*N);
            for(int i=0; i<M; i++)
            {
                cin>> f.r >> f.c >> f.m >> f.s >> f.d; 
                f.c--;
                f.r--;
                map[f.r*N + f.c].push_back(f);
            }

            #if debug
            cout<<"init()----------------"<<endl;
            for(int i=0;i <N; i++)
            {
                for(int j=0;j <N; j++)
                    if(map[i*N + j].size()!=0) 
                        cout<< map[i*N + j][0].m << " ";
                    else 
                        cout<<0<<" ";
                cout<<endl;
            }
            cout<<"init()----------------"<<endl<<endl;
            #endif

        }
        int sum()
        {
            int ret=0;
            for(int i=0; i<N; i++) 
                for(int j=0; j<N; j++)
                    for( fireball f : map[i*N+j])
                        ret+= f.m;
                
            
            return ret;
        }

        int sol()
        {
            init();
            for(int i=0; i<K; i++)
            {   
                #if debug
                cout<<i<<i<<i<<i<<endl;
                #endif

                magic();
        
           }
            return sum();
        }
        

        void magic()
        {
            vector<vector<fireball>> nmap(N*N);    //다음의 맵

            for(int i=0; i<N; i++) //move
            {
                for(int j=0; j<N; j++)
                {
                    for( fireball f: map[i*N+j])
                    {
                        f.r += dy[f.d]*f.s;
                        f.c += dx[f.d]*f.s;
 
                        while(f.r <0)  f.r+=N;
                        while(f.r >=N)  f.r-=N;

                        while(f.c <0)  f.c+=N;
                        while(f.c >=N)  f.c-=N;

                       #if debug
                        cout<< "d:"<<f.d<<" dy dx: "<<dy[f.d]*f.s<< " " <<dx[f.d]*f.s<<endl;
                        cout<< "r: "<<f.r<< " c:"<<f.c<<endl<<endl; 
                       #endif

                        nmap[f.r*N+f.c].push_back(f);
                    }
                }
            }

            #if debug
            cout<<"move()----------------"<<endl;
            for(int i=0;i <N; i++)
            {
                for(int j=0;j <N; j++)
                    if(nmap[i*N + j].size()!=0) 
                        cout<< nmap[i*N + j][0].m << " ";
                    else 
                        cout<<0<<" ";
                cout<<endl;
            }
            cout<<"move()----------------"<<endl<<endl;
            #endif

            for(int i=0; i<N; i++) // 새 파이어볼 생성
            {
                for(int j=0; j<N; j++)
                { 
                    if(nmap[i*N+j].size()>=2)   //이칸에 2개 이상이면
                    {
                        // cout<<"!!"<<endl;
                        fireball ff;    //나눠질 파이아볼
                        ff.m=0;
                        ff.s=0;
                        bool flag_odd=0;
                        bool flag_even=0;
                        for( fireball f: nmap[i*N+j])   //2 개 이상인 이 칸의 파이어볼 정보 조사
                        {
                            ff.m += f.m;
                            ff.s += f.s;
                            ff.c = f.c;
                            ff.r = f.r;
                            if(f.d % 2) flag_odd=1;
                            else flag_even=1;
                        }
                        // cout<< ff.m<<endl;
                        ff.m /=5; 
                        ff.s /= nmap[i*N+j].size();

                        #if debug
                        cout<< "m:"<< ff.m << " s:" <<ff.s<<endl;
                        #endif

                        nmap[i*N+j].clear();
                        if(ff.m ==0) continue;  //질량이 0이면 무시
                        
                        if( flag_odd==0 || flag_even ==0 ) //전부 홀수이거나 짝수
                        {
                           for(int k=0; k<=6 ; k +=2)
                           {
                               ff.d= k;
                               nmap[i*N+j].push_back(ff);
                           }
                        }
                        else{
                            for(int k=1; k<=7 ; k +=2)
                            {
                               ff.d= k;
                               nmap[i*N+j].push_back(ff);
                            }
                        }
                    }

                }
            }   
            
            map= nmap;
            

        }

};

int main()
{
shark s;

cout<< s.sol();
}