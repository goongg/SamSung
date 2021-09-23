

[TOC]



# 21.09.24 마법사 상어와 파이어볼 (20056)

풀이 정리



- fireball 객체를 만들고, N*N 배열 map을 만들어 fireball 객체들을 삽입

```c++
class fireball
{
    public:
    int r, c, m, s, d;
};

vector<vector<fireball>> map;

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
        }
```



- map을 조사하여 fireball 객체가 들어있으면 이동 
- 이동 후, 맵을 따로 만들어 처리

```c++
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

                        nmap[f.r*N+f.c].push_back(f);
                    }
                }
            }
```





- 이동 후, 맵에 2개 이상의 객체가 있으면, 지우고 새 객체 4개 생성 (fire ball 합쳐졌다가 4개로 분리됨)

```c++
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
                        for( fireball f: nmap[i*N+j]) //2 개 이상인 이 칸의 파이어볼 정보 조사
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
```

