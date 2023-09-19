[toc]


### 다익스트라 알고리즘?
그리디, 동적 계획법, 우선순위 큐
1) 우선 그래프를 저장함.
2) 초기 상태는 INF 자기노드까지는 0으로 설정
3) 우선순위 큐에, **거리와** 노현재 노드를 넣음.
4) 큐에서 하나씩 꺼내며, 현재 위치에서 뻗어나갈 노드를 찾음.
5) 다음 노드에 최단거리로 기록된 값보다 만약 현재까지 + 다음노드까지의 거리가 짧다면 시간을 업데이트 함.

```c++
priority_queue<pii, vector<pii>, greater<pii>> pq;
int graph[51][51];

void dijk(int start, int N, int K)
{  
    bool visit[51]; // 특정마을까지거리
    int time[51]; //특정 마을까지의 시간
    for(int i=1; i<= N; i++)
    {
        visit[i]=0; time[i]=INF;
    }
    time[start]=0; //시작마을까지 도착시간은 0;
    pq.push(make_pair(0,start));
    
    while(!pq.empty())
    {
        int u = pq.top().second; //현재 마을 위치
        pq.pop();
        if(visit[u]) continue; //이곳이 방문한 마을이면 스킵.

        visit[u]=1;
        for(int v =1; v<=N ; v++)
        {
             //현재까지 v 마을로의 최단거리보다 u에서 v로 이동하는게 더 짧디면            
            if(time[v] > time[u] + graph[u][v])
                time[v] = time[u] + graph[u][v];
            pq.push(make_pair(time[v],v));
        }
    }
    
    for(int i =1 ; i<= N ;i++)
    {
        // cout<<time[i]<<" ";
        if( time[i]<=K) answer++;
    }
}

```




### 22.09.10 파일 정렬
그러진 않겠지만, 정렬문제에 대해서 테크닉이 있다. 이건 분명 삼성 문제에도 유용하게 쓰일것이기 떄문에 공부 해놓자. 게다가, 반전도 하려면 필수적으로 알아야 함.

### 22.09.10 단어 변환
이 문제는 대놓고 bfs문제라 bfs로 풀음.
나는 엘레먼트가 두개밖에 안필요한대도 class로 짜는데... pair가 좋나.

### 22.09.10 압축
이런문제가 좀 중요한 구현 문제인것 같음. 정형화된 페턴이 없고, 출제의도를 잘 파악해서 잘 구현 해내는것. 중간디버깅 및 주석이 중요함.


### 22.09.10 네트워크
이런문제 잘 못풀었던것 같은데, 그래프를 그리고 인접한 영역 크기 찾고
이런건 무조껀 bfs / dfs임 보통 bfs로 풀리는건 dfs로도 다 풀림.


```c++
int solution(int n, vector<vector<int>> computers) {

    for(int i =0; i< computers.size(); i++)
    {
        if(!visit[i])
        {    
            visit[i]=1;            
            dfs(n, computers ,i);
            answer++;            
        }
    }
    return answer;
}
```


### 22.09.10 전화번호 목록.
이거 진짜 빨리 풀었는데 해결 못했다. 백만x백만 은 갯수 처리가 안됨.
중요한게 나는 sort 함수의 수행시간이 그렇게 짧을거라 생각 못했는데,
O(n*logN) 라고 하더라, 소팅을 쓰는게 훨씬 빨리 풀림. 소팅 시간소요 잘 생각해야 함.
<br>
두번째 중요한 개념은 string을 소팅하면 사전순 배열 된다는거... 중요함.

### 22.09.10 주차요금계산
substr이 진짜 중요함. iterator아니고, index부터 몇개 라고 생각해.
        `string num= s.substr(6,4);`




### 22.09.10 k진수에서 소수 고르기
일단 k 진수 만들기 개념이랑 소수 개념, 데이터 크기는 항상 생각해 줘야함.
테케를 다 만족하지 못한다면, 특히 결과뿐 아니라 중간 계산변수까지도 잘 생각이 필요함.
그리고.. 제곱끈까지만 아르키테메스의 체를 쓴다는건 정확히는 이해안됨.

```c++
    string s;
    while(n>0)
    {
        s+=to_string(n%k);        
        n/=k;
        //이렇게 하면 거꾸로 나오는데 이문제에서는 오히려 이걸 활용함.
        //보통은 reverse를 하던데 나는 그냥 stack 개념으로 뒤에서 부터 빼서 넣는게 편한듯.
    }
```

### 22.09.10 프린터
문제의 주어진 조건을 유리한 숫자로 치환하는것이 중요함.
이 문제의 경우, prio가 한자리 수이고, idx 또한 같이 생각해야 했음.
idx는 최대 길이인 100 이기 때문에 prio에 100을 곱하면 숫자 하나로 
idx와 prio가 모두 표현됨,
나중에 이것을 1000 나누거나 모듈러 처리하는 것으로 구분 가능.

```c++
    for(int i =0; i< priorities.size(); i++)
        priorities[i]= i+priorities[i]*1000;
```
### 22.09.10 위장
물론 이런문제는 안나오겠지만 상당히 중요한 문제임.
조합을 다 찾아내야 할때는 dfs를 사용하는게 맞음, 하지만 단순히 조합의 갯수를 찾아내는거라면 수학적인 개념을 사용해야 함.

```c++
int solution(vector<vector<string>> clothes) {
    for(vector<string> s : clothes)
    {
        if(m.find(s[1]) == m.end())
            m[s[1]]=1;
        else
            m[s[1]]++;
        
        if(m[s[1]]==1) 
            cate.push_back(s[1]);
    }
    answer=1;
    for(int i =0; i< cate.size(); i++)
        answer*= (m[cate[i]]+1);
    
    return --answer;
}
```
### 22.09.10 튜플
풀긴 풀었지만 상당히 어려워졌다. 다른사람풀이에서 좋은거 가저오자.

```c++
    st[stoi(tmp)]++, tmp.clear();
    한줄에 쓸때 이게 가능하구나.
```
내가 푼 방식은, 우선 모든 단위를 list라는 vector 안에 넣어놓고,
vector의 길이대로 원소를 찾아서 넣는 방식..
<br>
레퍼런스 코드는, 모든 숫자들의 등장 횟수를 기억한 다음에,
등장 횟수를 기반으로 answer에 넣는다... 이거 개쩌네

<br>
if 문에 0 아님 1을 넣어서 확인했는데 그냥 int 값을 넣으면
0이 아닐떄로 동작하는것 같다. 

### 22.09.07 정수 삼각형
dp 문제 인걸알고 풀었지만, 대충 감이온다 dp어케풀어야할지
이건 좀 쉽긴 한듯.
```c++
#include <string>
#include <vector>
#include <iostream>
using namespace std;

int dp[501][501];
int solution(vector<vector<int>> triangle) {
    int answer = 0;
    int h= triangle.size();

    dp[0][0] = triangle[0][0];

    for(int i =1; i < h ; i++)
    {
        for(int j =0; j<triangle[i].size(); j++)
        {
            int x=0;
            if(j==0 )
                x= dp[i-1][j];         
            else if(j == triangle[i].size()-1 )
                x= dp[i-1][j-1];                            
            else if (dp[i-1][j-1] > dp[i-1][j])
                x=dp[i-1][j-1];
            else
                x=dp[i-1][j];         
            dp[i][j] = triangle[i][j] + x;          
        }
    }
    
    for(int j=0; j<h; j++)
        if(answer < dp[h-1][j]) answer = dp[h-1][j];
    
    return answer;
}
```

### 22.09.06 캐시
개념적으로도 중요한 문제고, 카카오 1차의 레벨2 더 빨리 잘 풀었어야 한다.
실수 없이.
 카카오 문제는 어느정도 '구현'에 난이도가 있다고 생각해야 함.
선입선출을 해야 하지만, 조사도 필요할땐 nq를 쓰는것도 방법인듯



### 22.09.06 멀리뛰기
동전 문제다. dfs로도 쉽게 풀었지만 먼가 쎄한느낌.
dp의 사고방식은 어떻게 되는가?
현재의 답이 이전답과 연관성이 보일때 한다.
dp 가능성을 늘 열어두자 <br>
문제로 큰 답을 나머지 연산해서 요청할때가 있는데,
중간연산에 나머지 넣으면 답 동일하게 나옴 (왠지모름)

```c++
    long long dp[2001];

    long long solution(int n) {
    long long answer = 0;
    dp[0]=1;    dp[1]=1;
    for(int i=2; i<=n; i++)
        dp[i]= (dp[i-1] + dp[i-2] )%1234567;
    
    return dp[n];
    }
```



### 22.09.06 구명보트
Greedy 문제, 완전탐색을 요구하는 문제가 아니란 직감이 쎄게오면 맞음.
교훈을 이야기 하자면, 어지간하면 vector erase를 사용하는 방식으로 풀면 안된다는거.
그리디 문제로 파악이 됐으면 무조건 그리디 조건에 초점을 맞춰야 함.
지금 노드에서의 최선의 선택 말이지.
나는 굳이 제일큰거와 딱 핏하게 맞는걸 찾으려고 했음.
그럴필요가 없었기 때문에 못품.
왜냐면 가장 큰놈이랑 가장 작은놈을 선택해도 답이 같기 때문임.

그치만 이렇게 풀어도 erase를 넣으면 틀린 답이 나오고,
이런 조건을 찾았다면 erase를 넣을 필요가 없다는것을 이해하게 됨.


``` c++
    while(!people.empty())
    {
        int big = people.back();
        people.pop_back();    
        int small_idx=-1;
   
        if(people[0] + big <= limit)
            people.erase(people.begin()+i);
        answer++;        
    };
    for (int i = 0, j = N - 1; i <= j; i++) {
        if (people[i] + people[j] <= limit) {
            j--;
        }
        res++;
    }
```





### 22.09.05 메뉴 리뉴얼
이문제 리얼 대박임. 여러번 풀어볼 필요가 있는듯.

- comination
  <br>
  이젠 dfs가 익숙해지고 쉬워졌으니 dfs로 조합 처리할 필요가 있음.
  머리만 조금 쓰자면, 조합, 순열, 중복순열 다 어렵지 않게 가능할듯
  ```c++
    void combination( string all_orders, string s, int depth, int idx){
    if(s.size() == depth)
    {
        combi.push_back(s);
        return;
    }
    
    if(idx >= all_orders.size()) return;
    for(int i =idx; i<all_orders.size(); i++)
    {
        s.push_back(all_orders[i]);
        combination(all_orders, s, depth ,i+1);
        s.pop_back();
    }
    };
```


- check
  <br>
    특정 문자열에서 char를 찾는 함수. find stl 사용
    찾는게 없을 경우 (size_t -1) 을 return 함
  ```c++
    int check(vector<string> orders, string new_coures)
    {
    int ret=0;
    
    for(string s : orders)
    {
        bool no_found=0;
        for(char c :new_coures )
        {
            if (s.find(c) == (size_t)(-1) )
            {    
                no_found=1;
                break;
            }
        }
        if(!no_found) ret++;
    }
        return ret;   
    }
```



    
  




### 22.09.04 짝지어 제거하기
Stack


### 22.09.04 타겟 넘버
dfs 고수 됐음 dfs는 level3이상은 필요할듯

### 22.09.04 더 맵게
문제 자체는 쉽게 풀었는데, 시간초과를 해결하지 못했음.
기본적으로 이 문제는 우선순위 큐를 쓰라고 나온 문제임.
우선순위 큐를 언제써야하지? 알고리즘으로 소팅하는것 보다 훨씬 편하게 쓸 수 있음. 

우선순위 큐
priority_queue<int> pq;
priority_queue<int, vector<int>, greater<int>> pq;
 int x = pq.top()
 pq.pop();


### 22.09.04.기능 개발
이전 값을 참조해야할때 stack의 back 개념 활용


### 22.09.04 124 나라의 숫자
개 쉬운건데... 진짜 답답하게도 못한다.
10진수에서 k 진수로 바꾸기 --> 끝의 자리수만 나머지 연산하면 됨.
이 문제의 특이한 점은 0이 없다는것... 아무튼 너무 오래걸렸다.
while(n>0)
{
    answer+= to_string(n%k);
    n/=k;
}



### 22.09.04 두 큐 합 같게 만들기
이건 다시 복습좀 하자. Level 2인데 자꾸 실수가 난다.
다시 풀자 level2는 조금더 쉽게 접근할 필요가 있어 보인다.

1. erase 함수 와 insert 함수 복습 첫번 째 파라미터로는 iterator가 들어가야함.
   arr.begin()+ N 을 쓰는 등, erase는 두개 쓰면 어디부터 어디까지 제거하는거고
2. bfs / dfs 판단 인데 걍 dfs로 하면 되나 싶긴 하네...



### 22.09.03 신규 아이디 추천
stack 개념을 사용한, 중복 제거 개념.
erase 가 잘생각이 안나긴 했음.
근데 적어도 배열의 끝 값을 맞추기 위해 while문 back쓰는건 좋은것 같음.
string의 0번이 가장 좌측번호, 제일 먼저 넣은거니까 익숙해지고있는듯


### 22.09.03 성격 유형 검사하기
풀이전략
약 18분 정도. level 1은 10분컷 하도록 노력하자

다시 c++ 문법이 어색하다. 빨리 익숙해져야겠다. 프로그래머스에 적응필요
map 사용 : 특정 문자에 점수를 매길때 사용
string 문법 push_back('a'); 은 char에만 쓸 수 있음
문자열을 넣고 싶으면 insert를 **써야함**

이거 맨날 헷갈리는데 string에서 0번이 뭘까?
문제 풀면서 간단히 주석다는 습관을 들이자. 이거 주석단다고 빨리풀어서 한문제 더 푸는거 절대 아니다.




### 1. map

방문체크를 많이 해야할때?

방문체크 뿐만 아니라, 몇번 방문했는지까지 체크해야할때



\#include <map>

map<string, int> m; // string 과 int 를 매핑한다.

int next_index;

m["aaa"] = next_index; 

if(m.find("bbb" == m.end()) ) // 매핑정보가 없는지 체크





### 2. sort

#include <algorithm>

Sort 는 많이썼으니까. 역방향 sort (아직 역방향 소트 문제를 못봄)



### 3. 중복삭제

​    sort(answer.begin(), answer.end());

​    answer.erase( unique(answer.begin(), answer.end()), answer.end()) ;

 --> 중요한게 이거 중복삭제 제대로 할라면 sort쓰고 해야함 ㅋ

# 풀이 아이디어 정리

# 



### 
