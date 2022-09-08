[toc]


## 22.09.06 구명보트
Greedy 문제, 완전탐색을 요구하는 문제가 아니란 직감이 쎄게오면 맞음.
교훈을 이야기 하자면, 어지간하면 vector erase를 사용하는 방식으로 풀면 안된다는거.
그리디 문제로 파악이 됐으면 무조건 그리디 조건에 초점을 맞춰야 함.
지금 노드에서의 최선의 선택 말이지.
나는 굳이 제일큰거와 딱 핏하게 맞는걸 찾으려고 했음.
그럴필요가 없었기 때문에 못품.
왜냐면 가장 큰놈이랑 가장 작은놈을 선택해도 답이 같기 때문임.

그치만 이렇게 풀어도 erase를 넣으면 틀린 답이 나오고,
이런 조건을 찾았다면 erase를 넣을 필요가 없다는것을 이해하게 됨.


'''c++
    잘못된 그리디
   while(!people.empty())
    {
        int big = people.back();
        people.pop_back();    
        int small_idx=-1;
   
        if(people[0] + big <= limit)
            people.erase(people.begin()+i);
        answer++;        
    }

    잘한 그리디 
    for (int i = 0, j = N - 1; i <= j; i++) {
        if (people[i] + people[j] <= limit) {
            j--;
        }
        res++;
    }
~



## 22.09.05 메뉴 리뉴얼
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
~


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
~



    
  




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
