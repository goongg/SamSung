

[TOC]

# 21.09.24 청소년 상어 (19236)

dfs로 풀었는데
bfs로도 풀어볼 수 있을듯



풀이 정리

- fish 객체를 만들고 4*4 배열에 map을 만들어 삽입

  ```c++
  class fish{
      public:
      int a, b;  // 번호, 방향4
  };
  
  void input()
          {
              map= vector<fish>(16);
              for(int i=0; i<4; i++)
                  for(int j=0; j<4;j++)
                      {
                          cin>>map[i*4 + j].a>>map[i*4 + j].b;
                          map[i*4 + j].b--;
                          if(map[i*4 + j].a >= last_fish) last_fish= map[i*4 + j].a;
                          if(map[i*4 + j].a <= first_fish) first_fish= map[i*4 + j].a;
                      }
              a+=map[0].a;
              b= map[0].b;
              arrive[map[0].a]=0;
              map[0].a =0;
              map[0].b =0;
          }
  
  ```

  

- 특정 번호의 물고기가 살았는지 죽었는지를 판단할 변수 필요 (이게 bfs의 visit 역할)
- 이걸 16으로 풀다가 한참 해맸는데 input 조건이 1 부터 16까지기 때문에(물고기 번호가 1부터 16) 배열 크기는 17이 됐어야 함. (input 범위 체크필수)

  ```c++
          bool arrive[17] ={1,1,1,1 ,1,1,1,1, 1,1,1,1, 1,1,1,1,1 };
  ```



- 반시계방향회전 구현

```c++
int dx[8] = {0,-1,-1,-1,0,1,1,1};
int dy[8] = {-1,-1,0,1,1,1,0,-1};

물고기이동
...
                    else    //못가면 화전
                        from.b = (from.b+1)%8;  
```



- 물고기 이동 함수....

  1. arrive 변수를 통해 살아있는 물고기중 첫번째로 움직일 물고기와, 마지막 물고기를 알아냄

  2. 움직일 물고기를 선택하는 while문을 돌림
  3. 물고기 객체 from과 to 를 만들어서 자리를 바꿈

```c++
void move_fish()
        {
            for(int i=1; i<=16; i++)
                if ( arrive[i]) {
                    first_fish=i; break;
                }

            for(int i=16; i>=1; i--)
                if ( arrive[i]) {
                    last_fish=i; break;
                }
                
            int serch_num=first_fish;
            bool serch_flag=0;
            int c, r;
            fish from, to;
            while(1)
            {
                for(int i=0; i<4; i++){
                   for(int j=0; j<4; j++)
                        if(map[i*4+j].a== serch_num)
                        {
                            serch_flag=1;
                            c=i; r=j;
                            break;
                        } 
                    if(serch_flag) break;
                }

        #if debug
        cout<<"serch" << serch_flag <<" "<< serch_num<<": " <<c<<" " <<r<< " " <<map[ (c)*4+ r ].b <<endl;
        #endif

            if(serch_flag)  //번호의 물고기가 있으면 이동해
            { 
                from= map[ c*4+ r ];
  
                for(int i= 0; i<8; i++)
                {
                    if( c + dy[from.b] >=0 && c + dy[from.b] <4 &&    //움직일수 있으면
                            r + dx[from.b] >=0 && r + dx[from.b] <4 &&
                                !(r + dx[from.b] ==sr && c + dy[from.b] ==sc) )            
                    {
                        to= map[ (c + dy[from.b])*4 + (r + dx[from.b])];
                        map[ (c + dy[from.b])*4 + (r + dx[from.b])] =from;
                        map[ c*4 + r ] = to;
                        
                               #if debug
                               cout<<"to:"<<to.a<<" from:"<<from.a<<endl;
                               #endif

                            break;
                    }
                    else    //못가면 화전
                        from.b = (from.b+1)%8;  
                
                }
            }

        #if debug
        cout<<endl<<"----------------"<<endl;
        for(int i=0; i<4 ;i++){
            for(int j=0; j<4; j++)
                cout<<map[i*4 + j].a<<" ";
            cout<<endl;
        }
        cout<<"----------------"<<endl;
        #endif

            serch_flag=0;
            serch_num++;
            if(serch_num>last_fish)
                break;
        }


        #if debug
        for(int i=0; i<4 ;i++){
            for(int j=0; j<4; j++)
                cout<<map[i*4 + j].a<<" ";
            cout<<endl;
        }
        #endif
    }
```




- dfs

  1. 최대 뻗을 수 있는 노드는 3개 (상어가 특정 위치에서 이동할 수 있는 최대 거리)
  2. for문 3번씩 돌려서 가지치기
  3. arrive 변수가 visit 역할 수행
  4. dfs_ans는 전역변수로 마지막에 return 만, (종료 depth조건 불 필요)
  5. 동일한 물고기 함수로 bfs로도 풀어보기

```c++

int dfs(  shark s)
{

    if( dfs_ans < s.a) dfs_ans= s.a;
    
        for(int i=1; i<=3; i++) //많이 가봐야 최대 3칸
        {
            shark ns=s;
            ns.posible=0;
            if( s.sc + dy[s.b]*i >=0 && s.sc + dy[s.b]*i <4 &&
                 s.sr + dx[s.b]*i  >=0 && s.sr + dx[s.b]*i <4 &&
                    s.arrive[s.map[ (s.sc + dy[s.b]*i)*4+  s.sr + dx[s.b]*i].a] ) // 절로 갈 수 있으면       
            { 
                ns.posible=1;
                ns.sc= s.sc + dy[s.b]*i;
                ns.sr= s.sr + dx[s.b]*i;            //상어 위치 이동
                ns.a += s.map[ ns.sc*4+  ns.sr].a;  //잡아먹고
                ns.b = s.map[ ns.sc*4+  ns.sr].b;   //방향 저장 
                ns.map[ ns.sc*4+  ns.sr].a=0; 
                ns.map[ ns.sc*4+  ns.sr].b=0;
                 
                ns.arrive [ns.map[ ns.sc*4+  ns.sr].a] =0;

                ns.move_fish();


                dfs(ns);
            }
        }

    return dfs_ans;

}
```



# 21.09.24 마법사 상어와 파이어볼 (20056)

풀이 정리

쌩 시뮬

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





# 21.09.23 마법사 상어와 비바라기 (21610)

풀이 정리

쌩 시뮬 문제



- 양 끝 열 , 양 끝 행 연결 되어 있는 경우

  그냥 이동 해버리고, n만큼(배열 사이즈)을 더하거나 뺌

  ```c++
              c[i].first  += dy[d]*s;
              c[i].second  += dx[d]*s;
  
                 
              while(!(c[i].first>=0))    c[i].first +=n;
              while(!(c[i].second>=0))   c[i].second +=n;    //구름 이동
  
              
              while(!(c[i].first<n))    c[i].first -= (n);
              while(!(c[i].second<n))   c[i].second -=(n);    //구름 이동
  ```

  

  

- 구름 vector를 만들어서 생겨나고 없어지는 것 관리

  객체 정보로는 좌표만 필요하므로 pair 만들어서 벡터 처리

  ```c++
  typedef pair<int,int> pos;
  vector<pos> c; 
  ```

  





# 21.09.23 마법사 상어와 블리자드 (21611)

풀이 정리

쌩 시뮬 문제

이거 너무 복잡하게 풀은것 같음.

풀이가 너무 길어 300 라인 이상.

실전에서 절대 이렇게 못 풀듯.. 타 풀이 찾아서 내꺼랑 비교해 보기



달팽이 큐랑 테이블 벡터랑 옮기는 함수가 너무 길다.

아래 반복문을 4개로 나눠서 하는게 아니고 하나로 처리하도록 하면 줄어들듯

- 달팽이 큐의 경우 L D RR UU L L L 순으로 반복됨.

```c++
 void toQ()
        {    
            q.clear();        
            int cnt=1;
            int cx, cy, nx, ny;
            cx= sx; cy= sy;
            // cout<<"asdfasdf" <<cx<<" "<<cy<<endl<<endl;
            while(1)
            {

                for(int i=0; i< cnt; i++)
                {
                    nx= cx -1;
                    ny= cy;
                    q.push_back(t[ny*n + nx]);
                    // cout<< "L:"<< nx <<" " <<ny<<" "<<t[ny*n + nx]<<endl;
                    cx = nx;
                    cy = ny;
                    if(cx==0 && cy==0)
                        return;
                }//L

                for(int i=0; i< cnt; i++)
                {
                    nx= cx;
                    ny= cy +1;
                    q.push_back(t[ny*n + nx]);
                    // cout<< "D:"<< nx <<" " <<ny<<" "<<t[ny*n + nx]<<endl;
                    cx= nx;
                    cy =ny;
                }//D

                cnt++;
                for(int i=0; i< cnt; i++)
                {
                    nx= cx +1;
                    ny= cy ;
                    q.push_back(t[ny*n + nx]);
                    // cout<< "R:"<< nx <<" " <<ny<<" "<<t[ny*n + nx]<<endl;
                    cx= nx;
                    cy =ny;
                }//R

                for(int i=0; i< cnt; i++)
                {
                    nx= cx ;
                    ny= cy -1;
                    q.push_back(t[ny*n + nx]);
                    // cout<< "U:"<< nx <<" " <<ny<<" "<<t[ny*n + nx]<<endl;
                    cx= nx;
                    cy =ny;
                }//U
                cnt++;
            }
            
        }
```

