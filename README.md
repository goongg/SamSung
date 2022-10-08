

[TOC]

## 22.10.08
풀이 정리

시뮬+dfs, 마찬가지로 시험장에서 풀었다면 맞췄을까

이거 한 줄이 왜 결과의 차이를 낼까...
```c++
    else if (next == 63) 
        next =20;
```

알았다.. next값에 누가 있는지를 비교 해야 하는데, 같은 노드를

63 // 20 으로 공용으로 쓸 수는 없는거임.

이거 예제에 이 반례가 있었으니 디버깅 했지 없었으면??

이것도 솔직히 dfs 는 매우 잘 해놓고, 계속 dfs에서의 디버깅만 신경쓰느라 정작 기존적인 go 함수의 오류를 놓쳤다.

이것도 dfs 실력부족이라고 봐야할듯. 무섭다.

bfs dfs 실력 충분하다 시뮬쪽에 오류가 있을지 좀 깊게 고민해보자.

## 22.10.07 어른 상어
풀이 정리

쌩 시뮬 문제, 시험장에서 어떻게 풀까 생각해야 할듯.

자료 구조 잘 고르고 시작 전에 전체적인 풀이 시뮬레이션을 돌려보기

맵에서 기물이 움직이는 코드를 짤때, 기물 중심으로 옮기는게 좋을때도, 맵 중심으로 옮기는게 좋을때도 있음.

이 문제는 맵 중심으로 옮기는 게 편했고, 쌩 시뮬은 대체로 시간초과를 고려하지 않아도 되는듯.

## 22.10.03 사다리 조작.
풀이정리

쉬운문제인것 같기도 한데. 시간초과, 틀렸습니다를 잘 해결해 내지 못했다.
시험장이었으면? 하는 생각이 많이 드는 문제고 피드백 할 것이 많다. 완탐 프로그래머스 level 3는 다 풀어봐야 함.


- 문제 선택 전략
<br>
    사다리를 놓을 수 있는 가지수가 많지 않았다.

    가로선은 10개 세로선은 30 개 이니까, 브루트 포스로 처리

    사다리 놓을 위치를 정하는 것을 dfs '조합'의 개념으로 접근 하기.

- dfs

    여기서 이문제에서 사용한 dfs 인데, dfs 문제 자체를 많이 풀어보고

    표현이나, 방문처리 다음 노드 선택 등 감강을 익혀야할것 같다.

    재귀로 조합을 짤때와 순열을 짤때, 그리고 중복 순열을 짤 때를 비교해서 생각해보면 쉽다.

1) 조합을 짜는 경우는, 다음 노드를 선택할때 현재노드 +1로 짜면 됨.
2) 순열을 짜는 경우는, 다음 노드를 선택할 때, 첫 노드부터 돌 돼, 방문처리를 해줘야함.

- 이 문제에서 실패한 지점.
  
    1. 우선 자기확신이 부족해서 이게 브루트 포스로 가능한 지 계속 의문이 들었다.
    2. dfs의 가장 중요한 핵심은 백트래킹이고, 내가 방문 하지 않아도 될  노드를 또 방문하는지, 그리고 방문 해야할 노르를 빼먹지 않는지가 중요하다. 이것을 위한 방문처리 노하우 가 중요.

```c++
void dfs(int depth, int a, int b)
{
    if(game())
    {
        answer = min(answer, depth);
        return;
    }
    if(depth==3) return;
    for(int j =a; j<=h; j++)
    {
        for(int i =b ; i<n; i++) // 이건 b부터 조사하면 안됐음.
        {
            if(ladder[j][i] == 1 ||
                ladder[j][i-1] ==1 ||
                  ladder[j][i+1] == 1 )
                  continue;
            set_ladder(j,i,1);
            dfs(depth+1, j, 1);
            set_ladder(j,i,0);        
        }
    }
};
```





# 22. 04 30 원판 돌리기
풀이정리

dequeue 문제라고 했는데, 그냥 벡터가 편하다.

기존 맵게임 문제랑 다른건 원판이다보니, r 행 c열에서 각 행의 마지막과 열이 연결되어있는 

구조라는것만 다른듯. 기본적으로 쉬운 문제

~~~c++
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
~~~

~~~c++
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

~~~

# 22.04 30 마법사 상어와 토네이도
풀이정리

예전에 이거 풀었었을떄보다 확실히 실력이 늘었다.

거이 모든 문제에 이중배열을 쓰는게 무저건 유리하고

중간디버깅을 할수있는단위를 생각해서 함수를 짠다는 관점이 중요함.

- 핵심아이디어 무브함수를 먼저 구현
  
~~~c++
  토네이도의 이동은 L D R U 순서로 돌아가고 각각
  1번 1번 2번 2번 3번 3번 돈다.

  즉 이동할거리와 이동하는 방향을 바꿔주는 타이밍을 따로관리하는게 유리하다.
  이걸한번에 관리하려고 하다가 코드가 오래걸렸다.
    void move() //토네이도의 이동 구현
    {
        w.move_cnt--;
        w.r = w.r + dr[w.d];
        w.c = w.c + dc[w.d];
    
        if(w.move_cnt==0)
        {
            if(even++ %2 ==0)
                cur_move_cnt++;
            w.move_cnt = cur_move_cnt;
            w.d = (w.d+2 ) %8;
        }

        Call_Cnt++;
    }
~~~

~~~c++
먼지이동함수는 핵심적인게 현재방향을 기준으로 퍼지는 범위가 바뀐다는데 있음.
그래서 현재방향을 기준으로 시계, 반시계로 돌리며 처리해주는게 훨씬 편함.
여기서 반시계 아이디어가 중요
nr =  r + dr[(d-1 +8) %8];
nc = c + dc[(d-1 +8) %8];


  void dust(int r, int c, int d)
    {
        r+=dr[d];
        c+=dc[d];
        int y = t[r][c];  //이건범위체크 할필요가 없음. 무조건 갈 수 있기 떄문
        int a = y;
        t[r][c] =0;

        //y기준 d 방향으로 두칸 떨어진 곳
        int nr=  r + 2*dr[d];
        int nc = c + 2*dc[d];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*5)/100;
        a-=(y*5)/100;

        //대각선방향
        nr=  r  + dr[(d+1) %8]; 
        nc = c  + dc[(d+1) %8];; 
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*10)/100;
        a-=(y*10)/100;


        nr =  r + dr[(d-1 +8) %8];
        nc = c + dc[(d-1 +8) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*10)/100;
        a-=(y*10)/100;


        //수직방향 두칸
        nr=  r  + dr[(d-2+8) %8] + dr[(d-2+8) %8];
        nc = c  + dc[(d-2+8) %8] + dc[(d-2+8) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*2)/100;
        a-=(y*2)/100;


        nr=  r  + dr[(d+2) %8] + dr[(d+2) %8];
        nc = c  + dc[(d+2) %8] + dc[(d+2) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*2)/100;
        a-=(y*2)/100;


        //수직방향 한칸
        nr=  r   + dr[(d-2+8) %8];
        nc = c   + dc[(d-2+8) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*7)/100;        
        a-=(y*7)/100;

        nr=  r   + dr[(d+2) %8];
        nc = c   + dc[(d+2) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*7)/100;
        a-=(y*7)/100;


        //대각 뒷쪽
        nr=  r   + dr[(d+3) %8];
        nc = c   + dc[(d+3) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*1)/100;
        a-=(y*1)/100;


        nr=  r   + dr[(d-3+8) %8];
        nc = c   + dc[(d-3+8) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*1)/100;
        a-=(y*1)/100;


        //앞쪽
        nr=  r   + dr[d];
        nc = c   + dc[d];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += a;
    }
~~~


# 22.04 29 마법사상어와 파이어스톰
풀이정리

어렵다. 시험은 이것보다 더 어려울거다. 집중하고, 개념을 정리하자.

이문제는 이 간단한 코드가 어려웠고 오래걸렸다.

결국에 생각을 잘 못하겠어서 0,0으로 평행이동해서 풀었다.

한번에 헷갈리고 어려운걸 구현해내려고 시간을 쓰는것 보다, 생각을 심플하게 할 수 있도록 해놓고 보고 개선하는게 좋을 수 있음.

특히 회전과 관련된 문제는 옮길 map을 따로 배열로 두고, 0,0을 기준으로 회전한다고 생각하면  쉬울수 있음.


~~~c++
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
~~~

dfs는 실력이 올랐다고 생각하는데 여전히 불안하다.

중요한 개념은 방문체크를 하는냐 안하느냐인데, 다른 노드에 의해 침범을 허용할 것인지, 

아닌지를 기준으로 판단해야함. 예를들어 마법사상어와 복제처럼, 경로를 찾는 문제의 경우는, 시작 노드가 뭐냐에 따라서 해당노드를 다시 방문할 일이 있을수 있지만,

이문제의 경우 한번만 노드에 들어오면, 이 노드는 절대로 다시 들어올 일이 없기 떄문에, 초기화를 해주지 않아도 되는거임.

알겠는데, 연습 더 해보기


~~~c++
    for(int i =0 ; i<M; i++)
        for(int j=0; j< M; j++)
        {   
            if(t[i][j] ==0) continue;
            if(visit[i][j]) continue;
            visit[i][j] =1;
            size=1;
            dfs(i,j);  
            if(max < size) max = size;
        }

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


~~~


# 22.04 28 마법사상어와 복제
풀이정리

어려웠다. 어려운 문제였고, 이번 시험은 이것보다 어려울 수 있다. 노력하자.

이번시험에서 가장 중요한점은 두가지였다.
1) 중간디버깅
2) 코드 리뷰

지난 시험에서 중간디버깅의 중요성을 강조했는데, 이번 시험에서는 중간디버깅을 했음에도, 코드에 버그가 있어서 최종 디버깅이 1시간이상 걸려서 3시간안에 겨우겨우 풀었다.

3시간안에 겨우푼문제가 이거랑, 새로운게임, 나무재태크 등 정도가 기억나는데

이런문제를 풀때는 조건과 예외처리가 복잡하기 때문에 함수 하나 단위로 한줄한줄 코드리뷰를 해야할것 같다.

~~~c++
자료구조와 map 세팅
  void input()
    {
        KillCnt=0;
        cin>> M >>S;
        for(int i=0; i< M; i++)
        {
            Fish f;
            cin>>f.r>>f.c>>f.d;
            f.d--;
            f.r--;
            f.c--;
            t[f.r][f.c].push_back(f);
        }
        cin>>shark.r>>shark.c;
        shark.r--;
        shark.c--;        
        for(int i=0; i<4 ;i++)
        {
            for(int j=0; j<4; j++)
                smell[i][j]=0;
        }
    };

~~~

나는 저렇게 했는데 이제보니까 간단한 fish나 shark 같은경우는 struct가 낫겠다 싶다.
struct이렇게 초기화 할 수 있는거 확인했으니 다음엔 활용할 수 있으면 활용하자. 근데 기본적으로 나쁘진 않은듯 
- fish f = {x, y, d}; 


- 물고기 이동!
  분명 쉬운함수이고 빠르게 구현했지만 큰 에러가 있었다.

  방향을 돌려가면서 결정하는 상황을 고려했지만,
  
  모든 방향을 돌아도 움직이지 못하는 경우를 면밀히 보지못햇다.

  항상 가능한 모든 케이스에 대해서 고민을 한번은 해보고 넘어가야 한다.

  여덟방향으로 체크를 할떄 시작과 끝조건을 잘 생각해야 함.

  ~~~c++
      void fish_move()
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                for(int ff =0; ff< t[i][j].size(); ff++)
                {
                    Fish f = (t[i][j])[ff];
                    int nr = f.r;
                    int nc = f.c;
                    int nd = f.d;
                    int cnt=0;
                    do{
                        cnt++;
                        nr = f.r + dr[nd];
                        nc = f.c + dc[nd];
                        if(nc <0 || nr <0 || nc>=4 || nr >=4 || smell[nr][nc] !=0 || (nr == shark.r && nc==shark.c) )  
                        {
                            nd= (nd-1 +8)%8;
                            if(nd == f.d) 
                            {
                               nt[f.r][f.c].push_back(f);
                               break;
                            }
                            continue;
                        }     
                    f.r =nr;
                    f.c= nc;
                    f.d= nd;
                    nt[nr][nc].push_back(f);
                    break;
                    }while(1);
                }
            }
        }
  ~~~


- dfs 함수
  다른사람이 푼거 보니까 브루트 포스도 괜찮았겠더라.

  왜냐면 1회 이동은 3이고, 경우는 4씩 4^3; 총 64의 케이스를

  100번 중복해서 뽑으면 (2^6)^6 = 2^36 쫌크긴큰가 근데 걍 dfs도 괜찮았음

  근데 맵이 워낙 많다보니까, 초기화 해줄께 너무 많아서 복잡한것 뿐

~~~c++
map을 다양하게 설정하는 아이디어는 상당히 중요한듯, 그리고 이런문제 이차원 배열로 안했거나 y x를 썼으면 헷갈려서 못풀었을듯, 방식을 바꾼건 잘한것 같고, 이방식으로 새로운게임도 다시 풀어봐야겠다.

void dfs()
    {

        if(move_way.size()==3)
        {
            if( KillCnt >= max_kill)
                max_kill = KillCnt;

            answer_kill.push_back(KillCnt);
            answer.push_back(move_way);

            return;
        }


        int r= shark.r;
        int c = shark.c;
        for(int d=0; d<=6; d+=2) //네방향조사 
        {

            int nr= r + dr[d];
            int nc= c + dc[d];
            if(nc <0 || nr <0 || nc>=4 || nr >=4 )  continue;
            
            //임시저장
            vector<Fish> buf = nt[nr][nc];
            int buf_kill = KillCnt;
            int buf_smell = smell[nr][nc];

            KillCnt += nt[nr][nc].size();   //잡아먹은거 증가
            move_way.push_back(d);  //이동 자취 남김
            nt[nr][nc].clear();     //먹었으니 없어지고
            shark.r= nr; shark.c=nc;

            dfs();

            KillCnt = buf_kill;
            nt[nr][nc]= buf;
            move_way.pop_back();
            shark.r= r; shark.c=c;
            visit[nr][nc] =0;
        }₩

    };

~~~


# 22.04. 27 프로세서 연결하기
풀이정리
풀이방법을 정확하게 정리하고 들어가면 1시간반컷 가능하다. 

이정도 문제는 중간디버깅중요하고, 초기화 조건을 잘생각해야 함.

- dfs를 효율적으로 짤 수있게 하는 판단 함수, 초기화 함수를 설계하면,
- 중간디버깅이 쉬워지고 논리가 간단해짐.
- 한라인 쭉 검사하는거 while문도 괜찮은것 같음.

~~~c++
    //이방향으로연결가능한지정의
    bool check(int idx, int d)
    {
        _pos next= cores[idx];
        while(1)
        {
            next.r += dr[d];
            next.c += dc[d];

            if(next.r<0 || next.c <0 || next.r >=N|| next.c>=N)
                return 1;
            
            if(visit[next.r][next.c] ==1)
                return 0;
        }
    }

~~~

~~~c++
    int connect(int idx, int d)
    {
        int result=0;
        _pos next = cores[idx];
        while(1)
        {
            next.r += dr[d];
            next.c += dc[d];

            if(next.r<0 || next.c <0 || next.r >=N|| next.c>=N)
                return result;

            visit[next.r][next.c ] = !visit[next.r][next.c];
            result++;
        }
    }
~~~


- dfs의 경우, 원하는 depth에 도달했을때, return 때리고 이때의 결과를 저장
- 만약에 depth까지의 경로가 필요한 문제가 있어도 이런식으로 answer를 설계.
  
~~~c++
 void dfs(int core_idx, int length)
    {
        int cur_length;
        if(core_idx == cores.size())
        {
            int con=0;
            answer_length.push_back(length);

            for(int i=0; i< connected.size(); i++)
                if(connected[i]==1) con++;

            answer_connected.push_back( con);

            if(max_answer_connected < con)
                max_answer_connected= con;
            
            return;
        }

        if(connected[core_idx]) 
        {
            dfs(core_idx+1, length);        
            return;
        }

        for(int i=0; i<5; i++)
        {   
            if(i==4)
                dfs(core_idx+1, length);
            else
            {    
                if(check(core_idx, i))  //이을수 있으면
                {
                    int plus_length = connect(core_idx, i); //그방향으로 잇고
                    connected[core_idx] =1;    //이 코어가 연결됐음을 기록.
                    // print();
                    // cout<<i<<"방향으로 연결! 추가길이: "<<plus_length <<endl<<endl;
                    

                    dfs(core_idx+1, length+plus_length);
                    connected[core_idx] =0;    //초기화
                    connect(core_idx, i);
                }
            }
        }

    };
~~~




# 22.04 27 주사위굴리기2
풀이정리
x, y 너무 헷갈린데, r, c라고 쓰면 절대 안헷갈리는것 같음.

반드시 아래와 같이 풀도록 연습.

그리고 문제를 보면 탐색순서를 정할 수 있을 때가 있는데, 

보통 U R D L 이런식으로 define을 정의해놓으면 편하게 풀 수 있을것 같음
~~~c++
int dr[4]={-1, 0, 1, 0};
int dc[4]={0, 1, 0, -1};

#define U 0
#define R 1
#define D 2
#define L 3
~~~

주사위를 굴리는 함수

단독 객체를 사용해서 풀음.

여기서  int s[6] = {1, 5, 6, 2, 4, 3};  이코드 절대 안됨.

앞으로는 풀때 주의 필요. 저렇게 반드시 선언해야 한다면, 완전히 전역으로 

처리하던지 input에서 초기화 하던지 선택.


~~~c++
class Dice{

    public:
    int r =0;
    int c = 0;
    int s[6] = {1, 5, 6, 2, 4, 3}; //하늘, 앞옆 , 바닥, 뒷옆, 왼옆 우옆
    int d =R;
    void move()
    {

        int buf = s[0];
        r+=dr[d];
        c+=dc[d];
        //3  0 1 2 3  간 순환
        if(d==U) {
            s[0] = s[1]; s[1] = s[2]; s[2]=s[3]; s[3]=buf; 
        }
        // 4 0 5 2 4  순환
        if(d==R){ 
            s[0] = s[4]; s[4] = s[2]; s[2]=s[5]; s[5]=buf;
        }
        if(d==D){ 
            s[0] = s[3]; s[3] = s[2]; s[2]=s[1]; s[1]=buf;
        }
        if(d==L){
            s[0] = s[5]; s[5] = s[2]; s[2]=s[4]; s[4]=buf;
        }
        return;
    }
    void print()
    {
        cout<<"\ndice\n";
        cout<<"  " << s[3] <<"  " <<endl;
        cout<<s[4]<<" " << s[0]<<" " <<s[5] <<endl;
        cout<<"  "<< s[1] <<"  " <<endl;
        cout<<"  "<< s[2] <<"  " <<endl;
        return;
    }
};



그리고 간단한 bfs인데 너무 오래걸린다. dfs / bfs 연습은 꾸준히 해야할듯

이건 bfs로 풀필요는 없을것 같음 dfs가 훨씬 빨리풀렸음 실재로.

왜냐면, 최단거리 찾는문제가 아니라서 그래.

그리고 최단거리라고 하더라도 dfs로 back traking 치는게 낫지 않을까 싶기도  한데, 모르겠다 노력하자


~~~c++
  void bfs(int r, int c)
    {
        if(visit[r][c]) 
            return; //이미 방문한 곳이면 바로 나오기
        
        visit[r][c]=1;
        _pos p;
        p.r = r; p.c = c;
        queue<_pos> q;
        q.push(p);
        vector<_pos> v;//찾은 인접면을 임시저장
        v.push_back(p);

        int area=1;

        while(!q.empty())
        {
            p= q.front();
            q.pop();
            for(int d=0; d< 4 ; d++)
            {
                _pos np;
                np.r = p.r+ dr[d]; np.c= p.c +dc[d];
                if(np.r <0 || np.r >= N || np.c <0 || np.c >=M) continue;
                if(visit[np.r][np.c]) continue;

                if(t[r][c] == t[np.r][np.c] ) 
                {
                    v.push_back(np);
                    q.push(np);
                    visit[np.r][np.c] =true;
                    area++;
                }
            }
        }
        for(int i=0; i< v.size(); i++) point[v[i].r][v[i].c] = t[r][c]*v.size();
    
        return;
    }

~~~



# 22.04 23 벽돌 깨기
풀이정리
현시점 dfs + 시뮬 연습용으로 거이 제일 좋은 문제라고 생각

- 순열 개념 (중복순열, 순열)
   W개중 N 개를 순서를 고려해서 뽑아야 하는 문제

   조합이나, 순서섞이는 next_permutation이 편할수 있지만
   순열은 재귀개념이 확실히 편할것 같음


~~~c++
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
~~~
dfs 는 기본적으로 코드가 심플함

기계적으로 dfs짤 수 있도록 반복 숙달 되야하고, 중요한 정보는

1. 어떻게 뻗을지 : 조건문
2. 방문처리 어떻게 할지: visit 을 쓸지, 아니면 t에 바로 체킹할지
3. end조건을 어떻게할지? : 이건 depth가 정해져 있는거면 필요하고, 아니면 안필요
4. back tracking을 어떻게 할지 : 조건이 큰지 먼저 체크해야함


dfs: 폭발 구현

여기서 맵 자체에 0을 처리해서 방문조건을 처리했음.

중요한게 dfs하다보면, 방문처리를 안에서 dfs하기전에 처리 하는게 편할지

dfs안에서 처리하는게 편할지, 나뉘는데 이 경우, 맵자체가 방문처리도구로 사용되고

맵의 정보를 이용해야해서 dfs안에서 처리하도록 했음.


+ 라인으로 쭉 퍼져서 원하는 지점까지 찾아낼때, 실수 많이한다.
+ 현재정보초기화 -> 반복문안에서 ++ 처리 하도록 해야함
+ 그리고 제일중요한게 index 이중배열로 하는게 편할수있다는거 무조건 인식해야함.
+ 처음에 풀때 쉬워보였는데 복잡하게 오래걸린이유가 1중배열을 써서그런것 같음.
+ 시험전에 dfs, 순열 연습할겸 다시한번 풀어보면 좋은문제

~~~c++
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
~~~



# 22.0423 핀볼 게임
풀이 정리

100% 전형적인 시뮬 문제
핀볼의 정리를 vector에 넣고, 끝날때까지 시뮬 돌리기

풀이 1시간 + 디버깅 1시간 벽에서 튕기는거 짤때, 현재위치에서 방향만 바꾸기

이 경우 자료구조를 vector를 썼던적이 많은데,

하나씩 시퀀셜하게 확인해도 되는데, 중간에 요소가 사라질 가능성이 많은 경우

이 풀이처럼 queue를 쓰는것도 괜찮은 것 같다.

`cd = (cd +2 )%4`

`int dx[4] ={-1, 0, 1, 0};`

`int dy[4] ={0, 1, 0, -1};`





# 22.0422 줄기세포배양
풀이정리

테이블의 갯수가 정해져 있지 않은 새로운 유형

100% 시뮬 문제로, 탐색 알고리즘 개념은 없음

cell 위치를 vector에 넣어놓고 1시간이 지날때마다, push back 하기


- #define zero 200

테이블을 이런식으로 설정하면, 0,0을 기준으로 퍼지는 무한 크기의 테이블을 작성할 수 있음.

~~~c++
bool visit[2*zero +1][2*zero +1];
int power[zero*2+1][zero*2+1]; // 400, 400을 0,0으로 약속
int state[zero*2+1][zero*2+1]; // 400, 400을 0,0으로 약속
int max[zero*2+1][zero*2+1]; // 400, 400을 0,0으로 약속
~~~

~~~c++
  void TimeGo()
    {
        K--;
        vector<cell> new_cells;
        vector<cell> live_cells;
        vector<int> new_power;
        int cell_idx=0;
        for(int i=0; i< cells.size(); i++)
        {
            int x = cells[i].x;
            int y = cells[i].y;
            if( state[x][y]<0 ) // 비 활성화 된 세포라면,
            {
                state[x][y]++; //상태하나 늘림
                if( state[x][y] != power[x][y]);
                live_cells.push_back(cells[i]);
            }

            else if( state[x][y] >=0 && state[x][y] < power[x][y]) //활성화 된 세포라면
            {
                state[x][y]++; //상태하나 늘림
                if(state[x][y] != power[x][y])
                    live_cells.push_back(cells[i]);
                for(int d=0; d<4; d++) //네방향으로 퍼트림
                {
                    int nx= x + dx[d];
                    int ny= y + dy[d];

                    if(power[nx][ny] == 0) // 아직 안퍼진 곳이면?
                    {
                        cell cc;
                        cc.x= nx;
                        cc.y= ny;
                        if(!visit[nx][ny])
                        {
                            new_cells.push_back(cc);
                            new_power.push_back(power[x][y]);
                            visit[nx][ny]=1;
                        }
                        else 
                        {
                            for(int ii=0; ii<new_cells.size(); ii++)
                            {
                                if(nx== new_cells[ii].x && ny==new_cells[ii].y)
                                {
                                    if(new_power[ii] < power[x][y])
                                        new_power[ii] = power[x][y];
                                }
                            }
                        }
                    }
                }
            }
            else    //아무것도 안함
            {
                // cout<<"dead:"<<x -zero <<" " << y -zero<<endl;

                continue;
            }
        }
        cells.resize(0);
      //  cout<<K<<"-------------------\n";
        int iiii=0;
        for(cell ccc: new_cells)
        {

            cells.push_back(ccc);
            power[ccc.x][ccc.y] = new_power[iiii++];
            state[ccc.x][ccc.y] = power[ccc.x][ccc.y] * (-1);
        }
        for(cell ccc: live_cells)
        {
            cells.push_back(ccc);

        }
        
    }

~~~

# 22.0323 메뉴 리뉴얼

풀이정리

map vector sort permutatiom 다쓰는 좋은 문제

c++ 알고리즘을 복습하고 싶으면 무조건 찾아서 다시 풀어봐야 할 문제

- 모든 조합의 갯수를 찾는 함수 (Permutation)

  ~~~c++
          sel.clear();
          for(char c : s)
          {
              if(course > i)    //선택해야하는 코스 갯수만큼 1
                  sel.push_back(1);
              else
                  sel.push_back(0);
              i++;
          }
          sort(sel.begin(), sel.end());
  
          cout<< idx <<"의 조합: ";
          do
          {
              string buf;
              buf.clear();
              for(int j=0; j< s.size(); j++)
                  if(sel[j])
                      buf.push_back(s[j]);
              
              all_combi.push_back(buf);
              cout << all_combi.back()<<" ";
          } while (next_permutation(sel.begin(), sel.end()));
  ~~~

- 모든 조합에서 map 을 활용 그 조합이 나온 갯수를 세고, 최고 많이나온 횟수를 찾아 답에 추가

  ~~~c++
  vector<string> solution(vector<string> orders, vector<int> course) {
      vector<string> answer;
  
      
      vector<string> odrers_sorted;
      for(string s: orders)
      {
          sort(s.begin(), s.end());
          odrers_sorted.push_back(s);
      }
      map <string, int> m;
      vector<string> buf;    
      
      for(int i : course)
          search_comination(odrers_sorted,i);
      
  int MaxOder[1000]; //각 코스별 최대 사이즈
  memset(MaxOder, -1, 1000);
  
      for (string s :all_combi)
      {
          if(m.find(s) == m.end())
              m[s]=1;
          else
              m[s]= m[s]+1;
  
          if(MaxOder[s.size()]< m[s]) MaxOder[s.size()] =m[s];
      }
  
      for (string s :all_combi)
      {
          if(m[s]>=2 && MaxOder[s.size()] == m[s])
          {
              answer.push_back(s);
          }
      }
      
      sort(answer.begin(), answer.end());
      answer.erase( unique(answer.begin(), answer.end()), answer.end()) ;
  return answer;
  
  }
  ~~~

  

# 21.10.03 미세먼지 안녕! (17144)

풀이정리 

쌩 시뮬 노가다

진짜 복잡하다. 다른문제에서도 그랬는데 회전하도록 루프 짤때, 경계값이 너무 헷갈린다. 다른사람은 이럴때 어떻게 짤지 비교해봐야겠다.

시간조건도 엄청 널널헤서 그냥 시뮬만 잘 짜면 되는 문제



- 퍼트리는 함수

  ```c++
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
          
  
  ```

  

  - 바람 부는 함수
  
    다른사람 코드 중 직관적으로 잘짠거 찾아보기
  
```c++
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



   for(int i=0; i<n*m; i++)
    {
        if( nt[i] != -1)
            ret += nt[i];
    }

    return ret;

}
```

​    



# 21.10.07 감시 (15683)

풀이정리

간단한 완탐 + 시뮬



- 특정 위치에서 방향으로 view 처리를 해주는 함수

```c++
    void view(int cur, int d)
    {
        int x= cur%m;
        int y= cur/m;
        int nx = x ;
        int ny = y ;
        // cout<<"view"<<endl;
        while(1)
        {
            // cout <<d<<" ";
            nx+= dx[d];
            ny+= dy[d];
            int next =  ny*m + nx;
            if(nx <0 || nx>=m || ny<0 || ny >= n ) break;
            if( t[next] == 6 ) break;
            if(t[next] ==0) visit[next] = 1;
        }
        // cout<<endl;

    }
```





- 입력된 방향대로 view 함수를 콜해서 사각지대를 게산하는 함수

  int dx[4] = {-1, 0 ,1, 0};

  int dy[4] = {0, -1, 0 ,1};

  로 잡아두면 방향을 잡기가 편함

  1의 경우에는 저 4개중 한 방향으로 돌리면 되고

  2의 경우에는 저장된방향과 2차이나는 방향을 같이 돌려주면 됨

  'view(cctv[i], cctv_d[i]);' //저장된 방향

  'view(cctv[i], (cctv_d[i] +2 )%4 );' //저장된 방향과 반대 방향

  

  ```c++
      int clac()
      {
          visit.clear();
          visit.resize(n*m);
          int ret=0;
          for(int i=0; i< cctv.size() ;i++)
          {
              int cur= cctv[i];
  
              switch(t[cur])
              {
                  case 1:
                      view(cctv[i],  cctv_d[i]);
                      break;
  
                  case 2:
                      view(cctv[i], cctv_d[i]);
                      view(cctv[i], (cctv_d[i] +2 )%4 );
                      break;
  
                  case 3:
                      view(cctv[i], cctv_d[i]);
                      view(cctv[i], (cctv_d[i] +1)%4 ) ;
                      break;
                  case 4:
                      view(cctv[i], cctv_d[i]);
                      view(cctv[i], (cctv_d[i] +1)%4 ) ;
                      view(cctv[i], (cctv_d[i] +2)%4 ) ;
                      break;
                  case 5:
                      view(cctv[i], cctv_d[i]);
                      view(cctv[i], (cctv_d[i] +1)%4 ) ;
                      view(cctv[i], (cctv_d[i] +2)%4 ) ;
                      view(cctv[i], (cctv_d[i] +3)%4 ) ;
                      break;
              }
          }
          for(bool i: visit)
              if(i) ret++;
  
          return ret;
      }
  ```

  

- Dfs

  ```c++
      int dfs_min=99999998;
  
      void dfs(int level)
      {
  
          if(cctv.size() ==0) {
              dfs_min= blac;
              return;
          }
          if(level == cctv.size()) 
          {
              
              int buf;
              buf= blac- clac();
  
              #if debug
              cout<<"dfs종료 방향들"<<endl;
              for(int i: cctv_d)
                  cout<<i<<" ";
              cout<<"결과:"<<buf<<endl<<endl;
              #endif
  
              if(buf < dfs_min) dfs_min= buf;
  
              return ;
          }
  
          switch( t[cctv[level]] )
          {
  
              case 1:     //네방향존재
              for(int i=0; i<4; i++)
              {    
                  cctv_d[level] = i;
                      dfs(level+1);                    
              }
              break;
  
              case 2: //두방향 존재
                  for(int i=0; i<2; i++)
                  {    
                      cctv_d[level] = i;
                          dfs(level+1);                    
                  }
              break;
  
              case 3: //네방향
                for(int i=0; i<4; i++)
                  {    
                      cctv_d[level] = i;
                          dfs(level+1);                    
                  }
              break;
  
              case 4: //네방향
                  for(int i=0; i<4; i++)
                  {    
                      cctv_d[level] = i;
                          dfs(level+1);                    
                  }
              break;
  
              case 5: //한방향
                  cctv_d[level] = 0;
                  dfs(level+1);                    
              break;
          }
  
  
      }
  
  ```

  

# 21.10.06 상어 중학교 (21609)

풀이정리

진짜  조건이 너무너무 복잡한 시뮬 + dfs  

나무재태크나 새 게임2 과 비슷한 유형인듯 시뮬의 단계의 구분이 아주 명확하고 

조건이 엄청 많은 문제

이런 종류의 문재들은 나중에 모아서 한번 더풀어봐야 할듯

+테케 다 맞추고 나서 제출 이후 디버깅 할때는 되도록 코드리뷰 측면에서 진행해야 에러를 찾는듯



- dfs 를 써서 블록 그룹들을 만들고 배열에 저장하도록 짬
- 문제의 단계가 명확한데, 단계별로 함수 구현 해서 각 단계별 디버깅 하자는 전략
  1. dfs로 그룹핑을 하는 함수
  2. 그룹중 파괴할 것을 찾아 파괴하는 함수
  3. 중력을 가하는 함수
  4. 90도 회전하는 함수





- 그루핑을 하는 함수

1. dfs 에서 사용할 전역 변수들을 초기화 

2. dfs는 전체 칸들을 돌면서 방문 처리되지 않은, 일반 블록일때 시작

`if( t[i*n +j] >0 && t[i*n +j] <=m && !visit[i*n+j]  )`

3. dfs를 시작하기 전에 dfs안에서 사용할 전역변수를 초기화

   Answer 역할을 할 dfs_ret 와, 노드를뻗을지 판단할 des_num

4. dfs수행.

   여기서 다른 문제와 다른건 방문 해제는 무지개 블록만 수행한다는 점이 다름

   그리고 다른 dfs 전역변수들 초기화

```c++

    void search_group() //bfs
    {

        //한칸씩 돌면서 dfs를 수행.. 이미 그룹핑이 되어있는거면 노드 진행 안함
        //돌면서 방문하지 않은 일반 블록이 나오면 dfs 시작
        visit.clear();
        visit.resize(n*n);
        groups.clear();
        groups.resize(0);

        max_group_size=1;
        end=1;
        for(int i=0; i<n ; i++){
            for(int j=0; j<n ; j++)
            {
                if( t[i*n +j] >0 && t[i*n +j] <=m && !visit[i*n+j]  )
                {
                    dfs_num= t[i*n +j];
                    visit[ i*n +j] = 1;
                    dfs_ret.clear();
                    dfs_ret.resize(0);
                    dfs_ret.push_back(i*n +j );
                    dfs(i*n +j);

                    if(dfs_ret.size() >= 2 )
                    {
                        end=0;
                        groups.push_back(dfs_ret);
                        if(max_group_size < dfs_ret.size())
                            max_group_size = dfs_ret.size();
               
                    }
                    for(int ii=0; ii<n*n; ii++)
                        if(t[ii]==0) visit[ii]=0;

                    dfs_ret.clear();
                    dfs_ret.resize(0);
                }
            }
        }
    }

```


​    Dfs

```c++
    void dfs(int cur) // cur로 부터 주변에 자기와 같은 숫자가 있는지 체크 있다면
    {
        for(int i=0; i<4 ; i++)
        {
            int nx = cur%n + dx[i];
            int ny = cur/n + dy[i];
            int next = ny*n + nx;
            if( nx<0 || nx>=n || ny<0 || ny>=n) continue;
            if( t[next] == -1 ) continue;

            if( ( t[next] == dfs_num || t[next] ==0 ) && !visit[next]) 
            {

                visit[next]= 1; //방문처리 하고
                dfs_ret.push_back(next);
                dfs(next);
            }
        }

    }
```



- 위에서 생긴 groups 중 삭제할 groupd을 정하는 함수

나무재태크와 동일한 방법으로 진행 했음. 하지만 나무재태크와 달리

1회 수행이고, 아무리 많아봐야 배열의 갯수는 200을 넘기 힘들기 때문에 시간복잡도가 낮다고 판단. 그런데  코드가 진짜 너무 너무 길어짐

​	 --> 이 부분을 다른사람들은 어떻게 구현했을지 궁금 코드 찾아보기

```c++
   int sol()
    {
        input();
        while(!end)
        {
            search_group();
            if(end) break;
            delete_block();
            gravity();
            lotate();
            gravity();
        }
        return score;

    }
```






# 21.10.05 나무재태크 (16235)

풀이정리

쉬운문제 같은데 시간초과를 시간안에 해결못했다.





- 시간초과가 난 원인 1.

배열에서 최솟값이 여러개 존재하는 경우, 그것들을 찾아낼 때, 아래처럼 전체 for문을 두번 돌리는 방식을 많이 사용했었다.

1. 최솟값 자체를 찾는 for문

2. 그 최솟값과 같은 값을 갖는 index들을 찾는 for문



근데 한번 찾아내는것 정도로 하자면 그 배열의 최대크기 x2 만큼의 반복문이 돌게되서 배열이 작은경우 큰 문제는 되지 않았었는데

이건 근본적으로 한번 찾는게 아니라 sorting 에 가까움, 가장 작은 순서대로 돌려야 하니까. 이 두번의 for문을 전체 소팅이 될 때까지 while로 반복해야만 함



이 방법으로 하자면, 너무 비효율적인 sorting 코드를 도는거나 마찬가지가 된다. 배열크기가 큰 문제라면 무조건, 시간초과가 날것

 이 코드를 그나마 효울적으로 바꿔보자면, 처음 dead가 나온 이후에는, 이후 루프를 계산할 필요가 없음. 그 이후는 무조건 dead이기 때문.

하지만 다음부턴 이런 경우에는 (최소, 혹은 최대의 순서대로 배열의 원소 처리를 해야 하는데, 그 배열의 크기가 꽤 큰 경우)

 반드시 sort 함수를 사용할 수 있도록 구조체를 구성하려고 노력하던지, 나중에 다풀어 놓고 이쪽에서 back traking을 어떻게 할지를 생각 하려고 해야함 

```c++
                    while(!end)
                    {
                        end=1;
                        int min_age=100000;
                        //1.가장 어린 나이를 찾아
												for(int k=0; k< t[i*n+j].size(); k++)
                            if( t[i*n+j][k].age <min_age && !t[i*n+j][k].aging && !t[i*n+j][k].dead )
                            {
                                min_age=t[i*n+j][k].age;
                                end=0;
                            }
                        //2.그 나이를 가진 나무를 찾아
                        for(int k=0; k< t[i*n+j].size(); k++)
                        {
                            if( t[i*n+j][k].age == min_age && !t[i*n+j][k].aging && !t[i*n+j][k].dead )
                            {
                                if( f[i*n +j] >=  t[i*n+j][k].age)
                                {
                                    f[i*n +j]-= t[i*n+j][k].age;
                                    t[i*n+j][k].age++;
                                    t[i*n+j][k].aging=1;
#if debug
cout<<"aging:" << t[i*n+j][k].age << " 양분:"<< f[i*n +j]<<endl;
#endif
                                }
                                else
                                {
                                    t[i*n+j][k].dead=1;
#if debug
cout<<"dead:" <<endl;
#endif
                                }
                            }
                        }
```



개선코드

```c++
                               
																else //dead가 최초 등장하면, while 루프를 끝내고, 이 for 역시 break;
                                {
                                    t[i*n+j][k].dead=1;
                                    end=1;
                                    break;
#if debug                           
cout<<"dead:" <<endl;
#endif
                                }
```





- 시간초과가 난 원인 2

  벡터를 초기화 할때 queue에서 하던것 처럼 `while(nt.size()!=0) nt.pop_back();` 로 초기화 하는 습관이 있는데, 이개 은근히 시간을 많이 잡아 먹는듯

  아래처럼 하니 시간이 많이 줄었음 이렇게하도록 습관 들이기

  근데 가끔 resize만 하면 나중에 배열크기가 늘어났을때, 쓰래가 변수들이 들어가 있는 경우가 있어서 pop 하는 방법을 썼는데

  그런경우를 대비하기 위해서 clear()도 반드시 처리해주기

  

  추가 벡터 문법들

```c++
                    nt.clear();
                    nt.resize(0);
                    // while(nt.size()!=0) nt.pop_back(); 이거 개느려


vector<int> v = {1, 2};
v.resize(10, 1);
 => [ 1 2 1 1 1 1 1 1 1 1 ]
//------------------------------------------------//   
   vector<int> v = {1, 2};
v.resize(10);
 벡터의 v의 size가 10이되게 0을 push_back() 한다. 

=> [ 1 2 0 0 0 0 0 0 0 0 ]
//------------------------------------------------//
vector<int> v = { 1, 2 };
v.assign(10,2);
 벡터 v에 2을 10만큼 채워넣는다. 기존의 v에 있는 숫자들은 제거된다. 

=> [ 2 2 2 2 2 2 2 2 2 2 ]
   

```



- 시간초과가 난 원인 3

  근본적으로 이문제는 spring 함수랑 summer 함수가 구분될 필요가 없고, fall과 winter가 구분될 필요가 없다. 최적화가 가능함.







# 21.10.04 등산로 조성

풀이 정리

평범한 dfs + 시뮬 문제인데 문제의 애매한 설명 때문에 시간을 너무 잡아먹음

- 문제 설명 중 에바인점

  - 등산로를 만드는 규칙은 다음과 같다.

    ① 등산로는 가장 높은 봉우리에서 시작해야 한다.

  -> 이거 진짜 개에바인게,, 가장 높은 봉우리를 깍은 경우에도 이 봉우리를 포함해서 등산로를 찾아야 함. 가장 높은 봉우리를 깍으면, 가장 높은 봉우리가 아니게 되는거 아닌가?

  - 7. 필요한 경우 지형을 깎아 높이를 1보다 작게 만드는 것도 가능하다.

    ->이것도 진짜 애매한게, 음수도 될수 있다는건지 제한이 있어야 했던것 아닌가..

    음수면... 산이 아니게 되서 안되는거라 생각해야 하나



- 가장 높은 봉우리를 찾고, dfs를  봉우리부터 시작하게 해주는 함수

  dfs 시작 전에 시작하는 곳의 등산로 길이를 1로 설정

  dfs 시작하기 전에 시작하는곳을 방문처리

  ```c++
     int search_load()   //가장 높은 봉우리를 찾아서 등산로를 결정하는 함수 /dfs
      {
          vector<int> highst; // 가장 높은 봉우리를 저장하는 벡터
          int high_max= -1;
          int load_max = -1; // 가장 긴 등산로
  
          for(int i=0; i< n*n; i++)
              if(high_max < init_map[i]) high_max = init_map[i];
  
          for(int i=0; i< n*n; i++)
          {
              if(high_max  == init_map[i])
                  highst.push_back(i);
          }
  
          for(int i=0; i< highst.size(); i++)
          {
              for(int j=0; j<n*n; j++)
                  visit[j]=0;
  
              for(int j=0; j<n*n; j++)
                  load_length[j]=0;
  
              visit[highst[i]]=1;
              load_length[highst[i]]=1;
  
              dfs_max = -1;       
              int buf = dfs(highst[i]);
              if(load_max< buf) load_max= buf;
          }
  
          return load_max;
      }
  
  ```



- dfs

  현재위치로부터 네방향 조사

  다음 방향이 지금보다 작을 때, 노드에 추가

  노드에 추가할 때는,  등산로의 길이 와 방문처리를 해주고 나간다

```c++
   int dfs(int cur)
    {
        int mmax= -1;
        int buf;

        for(int d=0 ; d<4 ; d++)
        {
            int x = cur % n;
            int y = cur / n;
            int nx = x +dx[d];
            int ny = y +dy[d];

            if( nx <0 || nx >=n || ny <0 || ny >=n) continue;
            if( visit[ny*n + nx ]) continue;

            if( map[ny*n + nx] < map[cur]  ) //다음이 더 작으면 노드 뻗기
            {
                load_length[ny*n + nx] = load_length[cur] + 1;
                visit[ny*n + nx]=1;
                if(dfs_max < load_length[ny*n + nx])
                    dfs_max= load_length[ny*n + nx];

                dfs(ny*n + nx);
                visit[ny*n + nx]=0;
                load_length[ny*n + nx] -= load_length[cur] + 1;
            }
        }
        return dfs_max;
    }
```





- 깍을 칸을 결정하는 부분

```c++
    int sol()
    {
        int ret;
        int ret_max= -1;
        input();

        for(int kk= 1; kk<=k ; kk++)   //k 개만큼 깍으면서 구하기
        {
            for(int i=0; i< n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    map[i*n +j] -=kk;  //k만큼 깍은 맵
                    if(map[i*n +j] >=0)
                    	ret = search_load(); // 그맵에서 결과 내기
                    map[i*n +j] += kk; //원상복귀
                    if(ret_max < ret) ret_max= ret;
                }
            }
        }
        return ret_max;
    }
```





# 21.10.03 테트로미노 (14500)

풀이정리

쉬운 쌩쌩 시뮬 노가다

- static으로 가능한 모양 (19)개를 다 그려놓기

   범위 주의해서 반복문 돌리기

  이중배열 오랜만에 쓰는데, 너무 헷갈렸다. 주의해서 쓰기

  `s[a][b]` 는 s[b] 짜리를 a개 만들때 쓰는거

```c++
    int s[19][2]={ //각 모양의 행, 열 사이즈
        {4, 1}, // 0
        {1, 4}, // 1

        {2, 2}, // 2
        
        {2, 3}, // 3
        {2, 3}, // 4
        {3, 2}, // 5
        {3, 2}, // 6
...
    };
    int tetrio[19][6] =
    {
        {1, //0
         1,
         1,
         1},

        {1, 1, 1, 1}, //1

        {1, 1,
         1, 1},

        {1, 1, 1,
         0 ,1 , 0},
        
        {0, 1, 0,
         1 ,1 , 1},
        
        {1, 0,
         1, 1,
         1, 0},
...
    };
```



- 범위를 주의하며 반복문 돌리기

  ````c++
  
      int sol()
      {
          input();
          long long ret_max =-1;
          int ret_buf=0;
  
          for(int tt=0; tt<19 ; tt++)
          {
              for(int i=0; i<=n-s[tt][0]; i++)
                  for(int j=0; j<=m-s[tt][1]; j++)
                  {
                      ret_buf=0;
                      for(int ii= 0; ii< s[tt][0]; ii++){
                          for(int jj= 0; jj< s[tt][1]; jj++)
                          {
                              ret_buf += t[(i+ii)*m +j+ jj] * tetrio[tt][ ii*s[tt][1] + jj];
  
                          }
  
                      }
                      if(ret_max < ret_buf) ret_max =ret_buf;
                  }
          }
          return ret_max;
      }
  ````

  



# 21.10.03 스타트 택시 (19238)

풀이정리

신경쓸게 참 많은 bfs + 시뮬 문제

너무 조건을 다 고려해서 한번에 bfs를 짤라고 하지말고 모듈로 나눠서 중간 디버깅하면서 푸는게 날듯



- **잘못된 풀이 전략**

가장 거리가 짧은것을 찾고, 그 중에 가장 낮은 행을 찾고, 그 중에 가장 낮은 열을 찾을때,

그냥 bfs를 위, 왼, 오른 ,아래 로 돌리면 알아서 찾아 질 꺼라 생각했다.

왼 왼 왼

오른 오른 위

같은 반례가 있었고, bfs 에서 이런식으로 접근하는게 잘못된 발상인걸 알게됐음

처음부터 문제 조건처럼 최단거리를 먼저찾고, 그중에 최저 행을 찾고, 그 이후, 최저 열을 찾도록 코드가 변경 하니 해결 됨



- 거리를 찾는 함수 bfs

  가장 기초적인 bfs 함수형태를 사용, 여기서 굳이 연료양을 계산하진 않음
  
  만약 그곳에 갈 수 없다면 -1 을 리턴 (벽에 막혀있거나 등)

```c++
    int search_min(int from, int to)
    {
        queue<int> q;
        vector<bool> visit(n*n);
        vector<int> dis(n*n);

        q.push(from);
        visit[from]= 1;

        if(from == to) return 0;

        while(!q.empty())
        {
            int cur= q.front();
            q.pop();
            //4방향 조사
            for(int d=0; d<4; d++)
            {
                int nx= cur % n + dx[d];
                int ny= cur / n + dy[d];

                if( nx <0 || nx >=n || ny <0 || ny >=n ) continue;
                if(t[ny*n + nx] ==1 || visit[ny*n + nx]) continue;
                
                visit[ny*n + nx]=1;
                dis[ny*n + nx] = dis[cur] +1;
                if(ny*n + nx == to )
                    return dis[ny*n + nx];
                
                q.push(ny*n + nx);
            }
        }
        return -1;
    }

```



- 승객을 찾는 함수
  1. 현재 위치에서 최단거리를 조사(위 함수 사용)
  2. 최단거리 인 것중 최소 행을 조사
  3. 최단거리 인 것중 최소 행 인것중 최소 열을 조사

조건을 모두 만족하는 승객 위치로 이동하고, 연료량을 그 거리값만큼 뺌,

만약 거리값이 음수가 된다면 -1 을 리턴

```c++
    int search_man()
    {
        int dis_min= 999999;
        vector<int> dis_buf;
        int min_x= 999999;
        int min_y= 999999;
        
        vector<man> nmans;
        //현재위치에서 승객과의 최소 거리 찾기
        for(int j =0 ; j< mans.size(); j++)
        {   
            dis_buf.push_back( search_min(t_y*n + t_x,  mans[j].y*n + mans[j].x ) );
            if(dis_buf.back() != -1 && dis_min > dis_buf.back() )
                dis_min = dis_buf.back();
            
        }

        for(int j =0 ; j< mans.size(); j++)
            if(dis_buf[j] == dis_min)
                if(min_y > mans[j].y) min_y= mans[j].y;

        for(int j =0 ; j< mans.size(); j++)
            if(dis_buf[j] == dis_min && min_y == mans[j].y)
                if(min_x > mans[j].x) min_x= mans[j].x;

        if(dis_min == 999999)   //모든 승객에게 도달할 수 없는 경우
            return -1;
        

        //최단 거리 승객 중, 가장 행이 낮고 열이 낮은 승객 찾기     
        for(int j =0 ; j< mans.size(); j++)
        {
            if(mans[j].x== min_x && mans[j].y==min_y && dis_buf[j]==dis_min)
            {
                next_dest= mans[j].d_y*n + mans[j].d_x;
                t_x= mans[j].x;
                t_y= mans[j].y;
                fuel -= dis_min;
            }
            else
                nmans.push_back(mans[j]);            
        }
        mans= nmans;

if(fuel>=1)
        return fuel;
else
        return -1;
    }

```



- 목적지로 가는 함수

```c++
  int search_dest()
    {
        int dis_min= 999999;
        int dis_buf;

        //현재위치에서 목적지 까지 거리 찾기
        dis_buf= search_min(t_y*n + t_x,  next_dest);
        if(dis_buf ==-1 || fuel - dis_buf <0) return -1;
        else
            fuel += dis_buf;
        t_x= next_dest % n;
        t_y= next_dest / n;

        return fuel;
    }
    int sol()
    {
        input();
        int ret;
        for(int i=0; i<m ;i++)
        {
            ret= search_man();
            if(ret == -1) return -1;
            ret= search_dest();
            if(ret == -1) return -1;
        }
        return ret;
    }

```





# 21.10.03 연구소3_re (17142)

풀이 정리

**bfs** +  시뮬

전에 실패요인은 bfs 이해 부족으로 불필요한 루프가 너무 많아 시간이  많이 부족했던 듯 // bfs 문제 많이 풀어 보기

-   바이러스 퍼트리는 함수 (bfs)

  이전노드의 레벨을 기억하고 있다가, 다음으로 뻗어갈 때, 레벨을 +1 시켜주는 방식으로 시간을 구현했어야 함.

  bfs에서 노드의 레벨이 이 문제에서는 그 칸에 퍼진 시간이라고 생각

  전체 퍼진 시간의 경우, 0 인 곳으로 퍼진 시간중 최댓값을 찾으면 그게 최대 시간

  추가로 모두 퍼졌는지를 체크할 때도, 루프를 돌 필요 없이, 원래 빈칸의 갯수를 기억했다가 빈칸의 갯수만큼 0으로 노드가 뻗어진 숫자를 비교하면 

  코드가 훨씬 라이트 해짐

  ```c++
     int spread(vector<int> selected)
      {
          vector<int> nt =t; //퍼진 후 멥
          queue<int> q_vis;
          vector<int> sp_t(n*n); //각 칸에 퍼진 시간을 기록
          int spread_time=0;
          int sp_area=0;
          }
  
          while(!q_vis.empty())
          {
              int cur = q_vis.front();
              q_vis.pop();
              int x = cur%n;
              int y = cur/n;
  
              for(int j=0; j<4 ;j++)//현재 위치를 기준으로 4방향 조사
              {
  
                  int nx= x+dx[j];
                  int ny= y+dy[j];
  
                  if(nx>=n || nx<0 || ny>=n || ny<0 ) continue; //큐에 넣을 필요 없는놈들
                  if(nt[ny*n+nx]==1 || nt[ny*n+nx]==4) continue;
  
                  if(t[ny*n+nx]==0) sp_area++;    
                  sp_t[ny*n+nx] = sp_t[cur]+1; // 이 칸에 최초로 퍼진 시간은, 이칸을 퍼트린 놈의 시간 +1 
                  if( spread_time < sp_t[cur]+1  && t[ny*n+nx]==0 ) spread_time = sp_t[cur]+1 ;       
  
  
                  // 저 조건들을 제외하면 0 또는 2(비 활성 바이러스) 
                  nt[ny*n+nx] = 4; //활성 시켜주고
                  q_vis.push(ny*n+nx); //다음에 여기서부터 뻗어가도록 추가
              }
          }
      
          if(sp_area == blac)
              return spread_time;
          else
              return -1;
  
      }
  ```

  



- 바이러스를 선택 하는 부분

  순열 사용

```c++
    int sol()
    {
        input();

        // if(vis.size()==0 && blac !=0) return -1;
        if(blac ==0) return 0;

        //vis 중에 m개를 선택
        int min_time=999999;
        int time;
        vector<int> selected;
        vector<bool> combintaion;
        for(int i=0; i<m; i++)
            combintaion.push_back(1);
        while(combintaion.size() < vis.size()) combintaion.push_back(0);

        sort(combintaion.begin(), combintaion.end());
        do
        {
            for(int i=0; i<combintaion.size(); i++)
                if(combintaion[i]) selected.push_back(vis[i]);
            
            time= spread(selected);
            if(time <min_time && time != -1) min_time=time;
            
            selected.clear();
            selected.resize(0);

        }while(next_permutation(combintaion.begin(), combintaion.end()));

    if(min_time != 999999)    
        return min_time;
    else   
        return -1;
    }
```



# 21.10.02 치킨배달 (15686)

풀이정리

기본적인 시뮬, 조합으로 케이스 뽑는 문제

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





