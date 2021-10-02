

[TOC]





# 21.10.02 치킨배달 (15686)

풀이정리

input 값이 너무 작아서 엥간하면 시간초과 안남

next_permutaion 을 써서 조합으로 치킨집을 뽑음





- 1차원 배열에 치킨집 좌표, 집 좌표 넣음

- 거리 계산

  ```c++
      int distance(int a, int b)
      {
          return abs(a%n -  b%n) + abs(a/n - b/n); 
      }        
  ```
  
- 선택된 치킨집을 넣었을때 치킨 거리를 계산해주는 함수
  
  집 루프 안에서 치킨집 루프를 돌림 집으로부터 선택된 치킨집 사이 거리를 계산해 최솟값을 저장

```c++
    int clac( vector<int> c)    //
    {
        int ret = 0;
        for(int i :house)   //각 집에서 가장 가까운 치킨집을 찾음
        {
            int dis_min = 999999999;
            for(int j : c)
            {
                if( distance(i, j) <dis_min) dis_min = distance(i, j) ;
            }
            ret += dis_min;
        }
        return ret;
    }
```

- 치킨집 뽑기

````c++
   int sol()
    {
        input();
        int min_ret=9999999;
        vector<bool> combination;

        for(int i=0; i<m; i++) combination.push_back(1);
        while( combination.size() < chik.size() ) combination.push_back(0);
        sort( combination.begin(),combination.end()); 
        
        do{
            vector<int> buf;
            int ret_buf;
            for(int i=0; i< combination.size(); i++)
            {
                if(combination[i])
                    buf.push_back(chik[i]);
            }

        ret_buf= clac(buf);
        if( ret_buf < min_ret) min_ret = ret_buf;
        buf.clear();
        }while( next_permutation(combination.begin(), combination.end()));

        return min_ret;
    }
````




# 21.10.02 새로운 게임2 (17837)
풀이정리
쌩 쌩 시뮬 노가다

인풋 숫자가 너무 작아 딱봐도 시간복잡도는 큰 문제가 안됨. **진짜 구현 그 자체만 너무 복잡한 문제**

이동을 한번에 해서 풀라고 하지말고, 1회씩 이동하게 함수를 짠 다음 중간 디버깅 하자는 전략



- 주의할 점 벡터로 루프를 돌릴때, 루프가 돌면서 그 벡터 값이 바뀌도록 짜면 에러가 날 확률이 높음

- 게임이 끝나는 조건을 잘 체크 해야됨, 이번 턴의 이동이 다끝날때 조건체크를 하는게 아니고,

  턴 중간중간 모든 이동에서 조건체크를 해야 함

  

  



- 사용한 객체 변수들

  horse에 말 정보들을 넣음.

  칸의 색깔을 기억하는 int 배열, 

  칸별로 말의 목록을 저장할 horse 객체 배열

  말 목록 

```c++
class horse{
    public:
    int y, x; //위치
    int num; //말의 숫자
    int d; //방향
    int n; //내칸에서 내가 몇번쨰인지
};
typedef vector<horse> hh;

class game{
    int n, k;
    vector<int> t;  //보드 칸 색깔 저장
    vector<hh> ht;  //보드 칸에 쌓여있는 말
    vector<horse> h;  // 전체 말 목록
    int turn=0;
    bool end=0;
    public:
  
```



- 말을 1회 이동 하는 함수

  

  1. **말을 하나씩 꺼내서 다음으로 이동할 칸이 어떤 색 칸인지를 확정지음**
     - i 번째 말의 위치와 방향을 기반으로 t변수에서 색깔을 확인
     - 갈 수 있는 색깔이면 다음 이동 좌표를 nx ny에 넣고 색깔을 저장

  ```c++
  for(int i=0; i<h.size(); i++) //말들을 하나씩 옮김
          {
              int my_num;
              int color;
              int x = h[i].x; //옮기려는 말의 위치
              int y = h[i].y; //옮기려는 말의 우치
              int d = h[i].d;
              int num= ht[y*n +x].size(); //움직이려는 칸위에 있는 말의 갯수
  
              //어디로 옮길지, 옮기는 규칙을 정함
              int nx = x+ dx[d];
              int ny = y+ dy[d];
              
              if( t[ny*n+nx] == blue || (nx <0) 
                	|| (nx >= n) || (ny <0) || (ny >=n) ) //옮길수 없거나 파랑
              {
                  color =blue;
                  nx -= 2*dx[d];
                  ny -= 2*dy[d];// 방향을 바꿈
                  if( d == 0)      d++;
                  else if( d == 1) d--;
                  else if( d == 2) d++;
                  else if( d == 3) d--;
                  ht[y*n+ x][h[i].n].d =d;
  
                  if( t[ny*n+nx] == blue || (nx <0) || (nx >= n) || (ny <0) || (ny >=n) ) //한번 더 조사 
                      color = -1;
                  //가만히 
                  else
                      color = t[ny*n+nx];
              }
              else{
                  color= t[ny*n+nx] ;
              }
  ```

  

2. **색깔별로 실제 이동을 구현하는 부분.**

   - 하얀색이면, 지금 현재 칸에 저장된 말들을 하나씩, 지금 말부터 순서대로 꺼냄

   - 꺼내서 좌표를 위에서 확정한 다음좌표 (nx, ny)로 이동

     `ht[y*n+ x][j].x = nx;` 

	- 다음 위치로 이동할 때, 다음 칸에 사이즈가 그칸에서의  자신 순번이 됨

     `ht[y*n+ x][j].n= ht[ny*n +nx ].size();`
   
   - 꺼낸 갯수를 기억해 놓고 현재위치에서 빠진 갯수만큼 pop_back()
   
   - 빨간색이면 꺼내는 순서를 마지막부터, 지금말의 순서까지로, 루프의 반향만 바꿈
   
     `for(int j= num-1  ; j>= buf; j--)`

```c++
 if(color == -1)
            {
                continue;
            } //아무것도 안함
            else if(color==white)   //순서대로 이동
            {
                int buf = h[i].n;
                for(int j= buf ; j< num; j++) // 이칸의 나를 포함 나보다 위에있는 말을 내 규칙대로 옮김
                {
                    ht[y*n+ x][j].x = nx;
                    ht[y*n+ x][j].y = ny;
                    ht[y*n+ x][j].n= ht[ny*n +nx ].size();
                    ht[ny*n +nx ].push_back(ht[y*n+ x][j]);
                    
                    h[ht[ny*n +nx ].back().num] = ht[ny*n +nx ].back();
                    erase_cnt++;
                }
            }
            
            else if(color==red)   //반대로
            {
                // cout<<"with: ";
                int buf = h[i].n;
                for(int j= num-1  ; j>= buf; j--) // 이칸의 나를 포함 나보다 위에있는 말을 내 규칙대로 옮김
                {
                    ht[y*n+ x][j].x = nx;
                    ht[y*n+ x][j].y = ny;
                    ht[y*n+ x][j].n= ht[ny*n +nx ].size();
                    ht[ny*n +nx ].push_back(ht[y*n+ x][j]);
                    
                    h[ht[ny*n +nx ].back().num] = ht[ny*n +nx ].back();
                    erase_cnt++;
                }

            }
            for(int j=0; j< erase_cnt; j++) ht[y*n+x].pop_back();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (ht[i*n+j].size() >=4) 
            {
                end =1;
                return;
            }
        }
    }   


           #if debug
    cout<<"\n after move\n";
    {
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cout<<ht[i*n+j].size()<<" ";
            }
                cout<<"\n";
        }
    }
    cout<<"\n top horse \n";
    {
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
               if(ht[i*n+j].size() !=0) 
                cout<<ht[i*n+j].back().num +1<<" ";
                else
                cout<<0<<" ";
            }
                cout<<"\n";
        }
    }

```



# 21.10.01 경사로 (14890)

풀이정리

쌩 시뮬 노가다 딱히 특별한 아이디어 없음

조건도 너무 크지않아 시간복잡도도 괜춘 하고, 쉬운 시뮬문제

근데 예외 케이스가 생각보다 많아서 코드가 너무 더럽고... 디버깅이 꽤걸림

 다른사람 코드 보고 깔끔하게 짜는 연습좀 해야될듯



# 21.09.30 낚시왕 (17143)

풀이 정리

시뮬 + **시간복잡도 계산** + **규칙 찾기**

시뮬 구현이랑, 테케 까지는 간단한 문제인데 시간초과 해결이 너무 오래 걸림. 실전이라면 떨어졌을듯 

지금까지는 input조건을 보고 어디서 시간 초과가 날 수 있을지 전혀 고려하지 않고 풀고있는듯

테스트 케이스 다풀고 input 파라미터로 시간복잡도를 계산해보는 습관을 들여야 할듯...



- 1.상어 이동의 시간 복잡도 

이 문제에선 눈에 띄는 인풋 범위가 존재하는데

  1. M= 100 x 100 (R x C)

  2. s = 1000

  3. z=10000 

아래처럼 코드를 짜면 상어의 속력만큼 물고기를 이동 시켜야 하는데, 상어 하나당 1000번 씩 루프를 돌게 됨

그러면 10,000 x 1,000 = 10,000,000 인데, 이게 천만번

이 루프를 게임이 끝날떄까지 돌아야 하므로 또 열의 최댓값 만큼 곱 (100)

총 1,000,000,000 물고기 움직이는데만 10억번 루프를 돌아야 하는게 말이 안됨

```c++
                for(int s=0; s< sharks[i].s; s++) //상어의 속력만큼 반복
                {
                    if( sharks[i].y + ddy >=0 && sharks[i].y + ddy <Y &&
                            sharks[i].x + ddx >=0 && sharks[i].x + ddx <X)  //끝에 닿지 않았으면 이동
                    {
                        sharks[i].x += ddx;
                        sharks[i].y += ddy;
                    }
                    else{
                        cnt++;  //방향을 바꾼횟수를 기억
                        ddy *= -1;
                        ddx *= -1;
                        sharks[i].y += ddy;
                        sharks[i].x += ddx; //방향을 반대로 바꿔서 이동
                    }
                }

                //이 상어의 이동이 다 끝난순간에 방향을 홀수번 바꿨으면
                if(cnt%2 ==1)   
                {
                    if(sharks[i].d ==0 )      sharks[i].d++;
                    else if(sharks[i].d ==1 ) sharks[i].d--;
                    else if(sharks[i].d ==2 ) sharks[i].d++;
                    else if(sharks[i].d ==3 ) sharks[i].d--;
                }
```



-  input 함수에서 시간단축 가능

  하나씩 반복해보면 R 의 크기가 5라는 가정하에,

  속도가 0, 8, 16, 24 인 경우 모두 제자리로 가는것을 확인

  즉 (2*R-2) 만큼 모듈러 연산을하면, 총 연산량이 백배 단위로 줄어들게 되서 해결 되더라...

  

  ```c++
    void input()
      {
          cin>>Y>>X>>M; 
          sharks = vector<shark>(M);
          dead = vector<bool>(M) ;
          t = vector<ss>(X*Y);
  
          for(int i=0; i<M; i++)
          {
              cin>>sharks[i].y>>sharks[i].x>>sharks[i].s>>sharks[i].d>>sharks[i].z; 
              sharks[i].y--;
              sharks[i].x--;
              sharks[i].d--;
              sharks[i].num=i; 
              if(sharks[i].d ==0 || sharks[i].d==1)
                  sharks[i].s %= (2*Y -2);
              if(sharks[i].d ==2 || sharks[i].d==3)
                  sharks[i].s %= (2*X -2);
  
          }
  ```






ㄹㅁㄴㅇㄹㅁㄴㅇㄹ

# 21.09.29 캐슬디팬스 (17135)

풀이정리

쌩 시뮬 입력케이스(궁수 배치) 는 for 문 세번돌려 조합으로 넣음

딱봐도 쉬운 문제인데 문제를 잘못읽어 너무오래걸림 대충 감 잡혀도 문제 똑바로 다시 읽고 시작하기



- 배치된 궁수 위치로 점수를 계산하는 함수
  1. 턴은, 보드의 행 갯수 반복하면 됨 end = n;
  2. 궁수의 배열로 반복을 돌려서, 가장 가까운 거리의 적들을 조사하고, 그중 가장 왼쪽에서 가장 작은 적을 타겟으로 설정
  3. 타겟을 targets 배열에 넣고, 적들의 배열로 반복을 돌려, 제거 타겟목록에 없으면 살리고 한칸전진

```c++
    int clac_score(vector<int> bow)
    {

        if(enemy.size()==0) return 0;
        vector<int> nt=t;    
        vector<int> nenemy = enemy;
        vector<int> targets;
        int score=0;
        int end= end_time;

        while(end >0)
        {
            end--;
            //궁수 공격 턴, 새 타겟을 찾음
            if(nenemy.size()==0) break;
            targets.clear(); 

            for(int i: bow)
            {
                int target;
                int dis_min=999999999;
                int dis;
                int x_min=m+1;
                
                for(int e : nenemy) //거리가 가장 가까운 적 후보들 정리
                {
                    dis=distance(i, e); 
                    if(dis <= d && dis <=dis_min)
                        dis_min= dis;
                }
                if(dis_min != 999999999) //적을 하나라도 찾은 경우
                {
                  //거리가 가장 가까운 애들 중에서 가장 왼쪽에 있는애를 타겟으로 결정
                    for(int e : nenemy) 
                    {
                        dis=distance(i, e); 
                        if(dis == dis_min)
                            if(e % m < x_min){
                                x_min = e % m;
                                target = e;
                            }
                    }
                    targets.push_back(target);  // 타겟을 넣음
                }
            }

            vector<int> nnenemy;
            for(int i: nenemy)//타겟이 된 적들을 제거
            {
                bool check=0;
                for(int j: targets){
                    if(j==i)  check = 1;      //이 적이 타겟이 된 적이 있는 적인지 조사        
                }
                if(!check) nnenemy.push_back(i+m);          //타겟이 아닌 적들의 위치를 전진시켜서 넣음
                else score++;   //타겟이 된 적 있는 적이면 스코어 ++;
            }
            nenemy.clear();
            for(int i : nnenemy)
                if( i < n*m) nenemy.push_back(i);
        }

        return score;
    }

```

  

- sol 함수

```c++
  int sol()
    {
        int ret;
        int ret_max= -1;
        input();

        //궁수 위치 조합 세개 뽑음
        for(int i=0; i<m-2; i++)
            for(int j=i+1; j<m-1; j++)
                for(int k= j+1; k<m; k++)
                {
                    bowman.clear();
                    bowman.push_back(n*m+ i);
                    bowman.push_back(n*m+j);
                    bowman.push_back(n*m+k);
                    ret= clac_score(bowman);
                    if(ret_max < ret) ret_max= ret;
                }
    
        return ret_max;
    }
```





# 21.09.28 다리만들기 (17472)

풀이정리

1각자 다리를 구분해서 저장하는것은 bfs로

2.다리를 연결 하는 과정은 dfs로 풀 다가 실패함

3시간 넘어 4시간 넘게 풀어봤는데 못풀겠음. 문제 난이도가 너무 높은듯

주말에 다른사람 풀이 찾아서 다시 풀어보기



- land 객체를 만들어서, 자신의 땅 정보, 땅 이름(index) 를 저장한다

  ```c++
  class land
  {
      public:
      int num; //섬의 이름
      vector<int> eirth;
      vector<int> connected; //연결된 섬의 index를 넣음
      vector<int> b;// 다리의 갯수를 계산할때 필요
  };
  ```



- 땅을 구분하는 함수 search_land()

  전체 맵을 돌려서, 땅이 나오면 (1), 그 주변에 연결되어있는 땅들을 찾음

  ```c++
  
  void serch_land()
  {
      queue<int> q, v;
      land ll;
      int index=0;
      visit= vector<bool>(n*m);
      for(int i=0; i< n; i++)
      {    
          for(int j=0; j<m; j++)
          {
              if( t[i*m+ j] != 0 &&  !visit[i*m+ j]) 
                //섬을 찾았으면, 이곳을 기준으로 bfs를 돌려서 섬을찾음
              {
                  q.push(i*m+ j);
                  visit[i*m+j]=true;
                  ll.num = index++;
                  ll.eirth.push_back(i*m+ j);    
                  while(!q.empty())
                  {
                      int ii = q.front();
                      int x=ii%m;
                      int y=ii/m;
                      q.pop();
                      for(int d=0; d<4; d++) //네방향 조사
                      {
                          if(y+dy[d]>=0 && y+dy[d]<n &&
                              x+dx[d]>=0 && x+dx[d]<m)
                              if(t[(y+dy[d])*m +x+dx[d]] !=0 
                                  && !visit[(y+dy[d])*m +x+dx[d]])
                              {
                                  q.push( (y+dy[d])*m +x+dx[d] );
                                  visit[(y+dy[d])*m +x+dx[d] ]=1;
                                  ll.eirth.push_back( (y+dy[d])*m +x+dx[d]);
                              }
                     }
                  }
                  //주변 섬을 다 찾았으면
                  l.push_back(ll);
  #if debug
                  cout<<endl<<index-1 <<"'s eirth:"; 
                  for(int i: ll.eirth)
                      cout<<i<<" ";
                  cout<<endl;
  #endif                
                  ll.eirth.clear();                
              }
          }
      }
      visit.clear();
  }
  ```

  

- 땅끼리 연결하는 함수

```c++

int connect(int cur, int ex)
{
#if debug
cout <<"\n cur:"<<l[cur].num <<" visit_land_cnt:"<<visit_land_cnt <<" bridge size:"<<bridge_size <<endl<<endl;
#endif
    for(int i=0; i< visit.size(); i++)
        visit[i]=0
    visit[cur]=1;   //자 자신이랑 지나온 곳은 미 포함
    visit[ex]=1;   //자 자신이랑 지나온 곳은 미 포함

    if(visit_land_cnt == l.size()) //모든 땅을 돌았을 때,
    {
        if(bridge_size<mmin) 
            mmin=bridge_size;
        cout<<"-----------------end!---------------------"<<endl;
        cout<<"bridge size:"<<mmin<<endl;
        return mmin;
    }

       //현재 땅에서 갈 수 있는 섬을 조사
        int x, y;
        int nx, ny;
        for(int ii : l[cur].eirth)//땅 주변 바다를 찾아
        {
            x= ii%m; y= ii/m;
            nx=x; ny=y;
            cout<<"find from"<<ii <<" "<<x<<" "<<y<<endl;
            
            vector<int> bridge;   
            for(int d=0; d<4; d++) //네방향 조사
            {                
                if(y+dy[d]>=0 && y+dy[d]<n &&
                    x+dx[d]>=0 && x+dx[d]<m &&
                        t[(y+dy[d])*m +x+dx[d]] ==0 )   //바다를 찾았을 경우,
                    {
                        bool throuing=0;
                        while(1)                        //루프를돌아 바다 건너편에 다른 땅을 찾아
                        {
                            nx+= dx[d]; ny +=dy[d];
                            if(!(nx >=0 && nx<m && ny>=0 && ny<n))  //땅을 못찾고, 범위를 넘어간 경우 break;
                            {
                                nx=x; ny=y;
                                bridge.clear();
                                break;
                            }
                            if(t[ny*m + nx]==0)                     //바다를 건너는 중이면 인덱스를 넣어
                            {
                                cout<<"throu: "<<ny*m + nx<<" "<<x<<" "<<y<<endl;
                                throuing=1;
                                bridge.push_back(ny*m + nx);
                                continue;
                            }

                            else if(t[ny*m + nx]==1 && throuing)  //섬을 찾은 겨우        //바다를 건너 땅을 찾은 경우
                            {
                                throuing=0;
                                cout<<"is visited?:" <<ny*m + ny<<endl;
                                for(land ll : l)                    //내가 찾은 땅이 몇번째 땅인지를 조사
                                {
                                    bool is_find=0;
                                    for(int iii: ll.eirth)
                                    {
                                        if(iii==ny*m+nx)
                                        {
                                            if(!visit[ll.num])      //방문한 적 없는 땅이면
                                            {
                                                cout<<"find land:"<<nx*m + ny<<" " <<ll.num<<" bridge_size:" <<bridge.size() <<endl;
                                                for(int i: bridge) cout<< i<<" ";
                                                cout<<endl;
                                                if(bridge.size()>=2)
                                                {
                                                    bridge_size += bridge.size();
                                                    visit[ll.num]=1;          //이 땅을 방문처리                                                
                                                    visit_land_cnt++;
                                                    connect(ll.num);        //찾은 땅에서 다시 연결 시도
                                                    visit_land_cnt--;
                                                    bridge_size -= bridge.size();
                                                    bridge.clear();
                                                    visit[ll.num]=0;
                                                }
                                                is_find=1;
                                                break;
                                            }
                                        }
                                    }
                                    if(is_find)
                                        break;
                                }
                            }
                        }

                    }        
            }
        }

    

if(mmin!=init_num)
return mmin;
else
return -1;

}
```



# 21.09.27 상어 초등학교 (21608)

풀이정리

쌩쌩 시뮬... 아이디어 없음 걍 노가다





# 21.09.26 드래곤 커브 (15685)

풀이정리

쌩 시뮬 규칙찾기? 



- 규칙 찾기 90도 회전

도형(선)을 90도 돌릴라고 생각하지말고, 점을 90도 돌려야 댄다고 생각함

다음세대로 뻗기 전에, 그 전 세대의 마지막 점 (end_point) 를 기준으로 90도 시계방향 으로 돌려야 함.



기준점을 기준으로 특정 점을 90도를 돌리는 함수 만듬

90도 회전은 기준점을 (0,0)으로 평행이동 시키면

(x',y') = (-y, x) 로 바뀜

수학에서 x축 y축으로 보면 -90도 만큼 회전 변환인데.. y축 방향이 반대라 헷갈림

```c++
    p lotate(p d, p z)
    {
        int dif_x= 0- z.first;
        int dif_y= 0- z.second;
        // 0,0으로 이동시킴
        d.first += dif_x;
        d.second += dif_y;
        int buf= d.first;
        d.first = -1*d.second;
        d.second = buf;

        d.first -= dif_x;
        d.second -= dif_y;
    return d;
    }
```



- 현재의 세대와 점들을 벡터로 정보를 저장하는 curve객체를 만듬

```c+++
class curve
{
    int g=0;
    int dest_g;//여기까지 진화해야댐
    p end_point; 
public:
    vector<p> line;

```



- end 포인트를 기준으로 자신의 모든 점을 90도 회전 시키면 다음 세대가 됨

```c++
    //다음 세대로 진화하는 함수
    void evolution()
    {   
        //모든 점을, end point 를 기준으로 돌리고,
        //돌린점을 next_line에 넣어,
        //현재 line에 next_line을 다 넣고
        //겹친걸 제거 g를 하나 키움
        vector<p> next_line;        
        p new_end_point= lotate(line[0],end_point);
        for(p i: line) 
            next_line.push_back(lotate(i ,end_point));
        // next_line.pop_back();
        for(p i: next_line)
            line.push_back(i);
        g++;
        end_point= new_end_point;   
#if debug
    cout<<endl;
        for(p i : line)
           cout<<"g:"<<g<<" x,y:" <<i.first<<","<<i.second<<endl;
    cout<<endl;
#endif

    }

```



- 최종 도형 f (curve 객체의 모든 점) 을 한곳에 모음

```c++
for(int i=0; i<n; i++)
{    c[i].init(x[i],y[i],d[i],g[i]);
    for(int j=0; j<g[i]; j++)
        c[i].evolution();
        c[i].uni();
    for(p ii: c[i].line)
    f.push_back(ii);
}
    f.erase(unique(f.begin(), f.end()),f.end());//겹치는 점 제거
    // f.erase(unique(f.begin(), f.end()),f.end());

```



- f 객체에서 맵에 점을 찍고 점이 4개 정사각형 되면 answer++;

```c++
    for(p i: f)
    {
#if debug
        cout <<cnt++<<":"<<i.first<<" "<<i.second<<endl;
#endif
        visit[i.second*101 +i.first ]= true;
    }
    int answer=0;
    for(int i=0; i<100; i++)
        for(int j=0; j<100; j++)
            if(visit[i*101 +j] &&  visit[(i+1)*101 +j] && 
                    visit[i*101 +j+1] &&  visit[(i+1)*101 +j+1])
                        answer++;

```









# 21.09.26 연구소3 (17142)

풀이 정리

쉬워보이고 연구소 1이랑 매우 비슷한데... 3시간안에 디버깅 실패

78%에서 시간초과가 나는걸 시간안에 해결 못했음. 어디가 코드가 무거운 듯

실전이었으면 떨어졌을 문제



우선 풀이는, 바이러스 m개 선택은 순열 써서 만들었고

바이러스 퍼트리는건 BFS를 변형해서 풀음



바이러스 선택 코드

- 바이러스의 최대 갯수는 N*N : 2500 개 그중 최대로 뽑아야 하는 갯수는 10개

  그려면 2500 C 10 이 최대 

  이 갯수만큼 BFS를 돌린다

  -> 이게 너무 큰 숫자 인듯

   -> 그러면 바이러스 덩어리를 만들어서 문제를 풀어야 했나?

  

```c++

    int sol()
    {
        int min=1000000;
        input();
        int check=0;

        for(int k=0; k< n*n; k++) {
            if(t[k]==0)
                check = 1;
            }
        if(check==0) return 0;

        vector<int> Combination;
        vector<int> vi, vii;

        for(int i=0; i <n*n ; i++)
            if(t[i]==2) vi.push_back(i);
        
        for(int i=0; i<m; i++) Combination.push_back(1);
        while(Combination.size() < vi.size()) Combination.push_back(0);
        sort(Combination.begin(), Combination.end());

        // cout<<"------------------------------"<<endl;
        do
        {
            vii.clear();
            for( int i =0; i< Combination.size(); i++)
                if(Combination[i]==1)
                {    
                    vii.push_back(vi[i]);
                    // cout<<vi[i]<<" ";
                }
            ret= spread(vii);
            cout<<endl<<"ret:"<<ret<<endl;;
            if( ret!=-1 && ret<min) min= ret;
            ret =min;

        }while( next_permutation(Combination.begin(), Combination.end()));
        

            if(min == 1000000) return -1;
        return min;
    }

```



- 바이러스 퍼트리기
- 

```c++
    int spread(vector<int> vi)     //바이러스 위치를 입력으로 받음
    {
        bool check=0;

        queue<int> v;
        queue<int> nv;
        vector<int> nt=t;
        time=0;
        for(int i: vi)
        {   
            v.push(i);
            nt[i]=4;
        }

        int cnt=0;
        bool flag=0; // 이 단계에서 바이러스를 찾았는지?
while(!v.empty())
        {
            int vv= v.front();
            v.pop();

            for(int d=0; d<4; d++)
            {
                if( (vv/n) + dy[d] >=0 && (vv/n) + dy[d] <n &&
                    (vv%n) + dx[d] >=0 && (vv%n) + dx[d] <n &&
                        (nt[ ((vv/n)+dy[d])*n+  (vv%n) + dx[d]] == 2 || nt[ ((vv/n)+dy[d])*n+  (vv%n) + dx[d]] == 0)
                ) // 퍼질수 있는게 있으면 퍼트림
                {
                    nt[ ((vv/n)+dy[d])*n+  (vv%n) + dx[d]]=4;   //활성 바이러스는 4로 표시
                    nv.push( ((vv/n)+dy[d])*n+  (vv%n) + dx[d] ); //새로 추가된 바이러스 목록
                    flag=1;
                }
            }

            if(v.empty())     //현재 조사한게 마지막 바이러스 였다면,
            {
                time++; //시간을늘리고
                if(ret!=-1 && time>=ret)
                    return -1;

                v= nv;  //새로 추가한 바이러스들을 다시 큐에 넣어
                while(!nv.empty()) nv.pop();    //nv는 클리어


                check=0;
                for(int k=0; k< n*n; k++) {
                   if(nt[k]==0)
                   check = 1;
                }
                if(check==0) return time;
            }
        }

        return -1;

    }
```









# 21.09.25 연구소 (14502)

풀이 정리

바이러스 퍼트리는건 bfs로

벽 3개 세우는건 부르트포스로 넣음



- 바이러스 퍼트리기

  input과정에서 바이러스 위치를 큐에 저장.

  바이러스를 하나씩 꺼내면서 그 곳을 기준으로, 4방향을 조사해 퍼트릴 곳이 있으면 큐에 넣음

  map에 퍼트린곳에 2 처리를 하니까 따로 visit처리 할 필요는 없음

- 퍼트리는 작업은 여러번 해야 하니까, 실 작업은 바이러스 큐랑, 맵 버퍼를 따로 만들어서 처리(nt, w)

```C++
   int spread() //퍼짐, 안전영역 계산
    {
        vector<int> nt =t;
        queue<p> w=v;
        int ret=0;
        p cr;
        
        while(!w.empty())
        {
            cr = w.front();
            w.pop();
            for(int i=0; i<4 ; i++) //4방향 조사
            {
                if( cr.first+dy[i] >=0 && cr.first+dy[i] <n &&
                        cr.second +dx[i]>=0 && cr.second+dx[i] <m &&
                            nt[ (cr.first+dy[i])*m + cr.second+dx[i] ]==0 )  //범위안이고 0이면 가지치기
                        {
                            w.push(make_pair(cr.first+dy[i], cr.second+dx[i] ));
                            nt[ (cr.first+dy[i])*m + cr.second+dx[i] ]=2;       //방문 처리
                        }
            }
        }
        for(int i=0; i<n*m; i++) if(nt[i]==0) ret++;    //안전영역만큼 ++

#if debug
cout<<endl;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++)
                cout<<nt[i*m+j]<<" ";
        cout<<endl;
        }
cout<<endl;       
#endif

        return ret;
    }
```



- 벽 3개 넣기

1차원 배열로 맵을 만들었으니까 걍 전체에서 3개 조합으로 만들면 됨,

조합(다음 for문 이전꺼 다음차례부터 돌리기)

순열(다음 for문 처음부터 돌리기)

```c++
    int sol()
    {
        // 0 ~ n*m-1 중 3개를 뽑으면 됨, 순서 상관x
        input();
        int max = -1;
        int ret;
        for(int i=0; i<n*m-2; i++)
            for(int j=i+1; j<n*m-1; j++)
                for(int k=j+1; k<n*m; k++)
                    if(t[i] == 0 && t[j] == 0 &&  t[k] == 0)    //세개 다 빈칸인 경우에 벽세우고 퍼트리기
                    {  
                        t[i]=1; t[j]=1; t[k]=1;
                        ret= spread();
                        if(max < ret) max= ret;
                        t[i]=0; t[j]=0; t[k]=0;
                    }
        return max;
    }
```







# 21.09.25 게리멘더링2 (17779)

풀이 정리

부르트포스 로 품

선거구 나누는게 경계값 조건이 진짜 너무 복잡

중간 디버깅하면서 풀도록 연습하기



- 부르트 포스

  d1, d2, x, y의 가능한 총 경우의수는 각 50개로 모두 곱해도 625, 0000 백만 단위 이므로 모든 조건을 다 돌려도 괜찮다고 판단.

```c
int sol()
        {
            input();
            int a;
            int min=100000000;
            for(int d1 =1; d1<=n; d1++){
                for(int d2= 1; d2<=n; d2++){
                    for(int x =1; x<=n; x++){
                        for(int y =1; y<=n; y++){
                            if ( (x+d1+d2 <=n) && (d1 + 1 <=y) && ( y+d2 <=n) )   
                            {
                                a = calc(x, y, d1, d2);
#if debug
                                cout<< x<<" " << y<<" "<< d1<<" "<<d2<<" "<<endl;
                                cout <<a <<endl;
#endif
                                

                                if(min > a) min=a;
                            } 
                         }
                    }
                }
            }
```



- 경계선 긋기

  x, y 부터 시계방향으로도 면서 경계값 그리기 (5로 입력)

  (여기서 보통 행을 y라고하고 열을 x라고 하는데... 문제에서 x, y가 각 행, 열로 주어져서 너무 헷갈림  다음부터는 그냥 r,c 로 통일해서 풀던지 해야할듯)

  ```c++
            v.clear();
              v = vector<int>((n+1)*(n+1));  //선거구
              vector<int> p(6);
              int cnt =0;
              bool f=0;
                  
                  int c, r;
                  c=x; r=y;
                  int dc[4]= {1, 1, -1, -1}; 
                  int dr[4]= {1, -1, -1, 1};
                  int dd[4]= {d2, d1, d2,d1};
  
                  for(int j=0; j<4; j++)  //경계선 긋기
                      for(int i=0; i< dd[j]; i++)
                      {
                         v[c*n+ r] =5;
                         c+=dc[j]; r+=dr[j];
                      }  
  ```

  

- 나머지 선거구 정하기

  경계선에 닿기 전까지 각자 범위 내에서 선거구 범위를 지정

  여기 경계값을 자꾸 틀려서 풀이가 길어졌는데... 이건 대놓고 경계값 헷갈리게 낸 문제인것 같음

  ```c++
                  // //경계선에 닿기 전까지 1
                  for(int i=1; i<x+d1; i++)
                      for(int j=1; j<= y; j++)
                      {
                          if(v[i*n+j] ==5)
                              break;
                          else v[i*n+j]=1;
                      }
  
                   for(int i=1; i<=x+d2; i++)
                      for(int j=n; j> y; j--)
                      {
                          if(v[i*n+j] ==5)
                              break;
                          else v[i*n+j]=2;
                      }
  
                  for(int i=x+d1; i<=n; i++)
                      for(int j=1; j< y-d1+d2; j++)
                      {
                          if(v[i*n+j] ==5)
                              break;
                          else v[i*n+j]=3;
                      }
  
  ```



- 선거구 대로 인구수 입력하기

  ```c
                  for(int i=1; i<=n; i++){
                      for(int j=1; j<=n; j++)
                      {
                          if(v[i*n+j] == 1)   p[1] += t[i*n+j];
                          if(v[i*n+j] == 2)   p[2] += t[i*n+j];
                          if(v[i*n+j] == 3)   p[3] += t[i*n+j];
                          if(v[i*n+j] == 4)   p[4] += t[i*n+j];
                          if(v[i*n+j] == 5 ||v[i*n+j] == 0) p[5] += t[i*n+j];
  ```

  







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





