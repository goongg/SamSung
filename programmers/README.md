[toc]

주요 문법 정리



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



# 풀이 아이디어 정리

# 



### 