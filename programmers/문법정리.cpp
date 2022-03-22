#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <map>

#include <algorithm>
using namespace std;
using namespace std;

// 지금 돌리고 있는 포문에 원소를 buf에 +연산으로 넣는 방식
// 다중 포문 사용시 주의점 초기화 시점을 잘 생각해야 돼
// answer[iidex].insert(0, insertname +"님이 "); // 인서트 중요해 위치 + 무엇
// Hash 사용 매핑해야할 때가 있을꺼야 분명히

//stack의 사용이야. 연속된 두 문자를 찾아낼때, 스택의 개념을 활용하면 되게 좋아
//나는 vector가 익숙하니까 stack을 벡터로 선언해 논다음에 top에있는걸 (back) 비교하는 방식으로 구현하는거야

//부르트포쓰로 문제 풀때, 순열의 개념을활용하면 되게 좋아
// 그리고 스트링 투 인트 stoi 이런 아름다운 STL이 있어
// to_string(int) 이런 아름다운 STL도 있고

//침착하게 풀자 준혁아 제발....
// letters.erase( unique(letters.begin(), letters.end()), letters.end()); 

//자리수 빨리 알아내기 to_string

//탐색 문제는 내가 지금 어디고, 어디로 뻗어야 하지? 로 모델링할 수 있는 문제에 대한 해결법이야

//BFS DFS 에서 중요한것은 방문체크와 그 방법이야
//만약 방문체크 할 것들이 지나치게 너무 많은 경우에는 map을 활용해야 돼
//
/* map 사용법 정리
map<string, int> m;
int next_index;
m["aaa"] = next_index; 로 등록. // 이게 bool check[xxx] =1 로 하는것과 같은 행위야
if( m.find("bbb") = m.end()} // 이거 벡터나 string도 되나?
이게 없을때야 그떈 다시 등록하면 돼
*/

//bfs는 그중에서도 최단거리 문제를 풀때 유리해 무조건 최단거리가 먼저 찾아지기 때문이야.
//중요한것은 q에 무엇을 넣을지가 중요해 우선, item에 무엇이 들어갈 지를 고민해, 그리고 거기엔 depth는 있어야 대
//현재 노드의 정보를 가지고 다음 노드를 만들어서 큐에 넣는거야. 그러면 노드의 정보를 표현할 수 있는 자료구조를 item으로 만들어주면돼
//종료조건 // 삽입조건 큰 틀에서만 생각해

//DFS 풀때 마음가짐은 나는 지금 어디고, 어디로 뻗고 싶은거야? 이게 중요해 일단 답부터 풀어내고 Back traking 할 수 있다는 측면에서 더 좋은 풀이 같아.
//visit cout을 해서 디버깅 할수도 있고
//종료조건 // 뻗기조건을 나눠서 풀면 돼

//for문을 돌릴때, index가 필요하면 걍 고전적인 방식으로 돌려 깝치지말고
//for문 돌릴때, 돌아가고잇는건 냅둬야 할 떄 가 많아, 그 때는 string buf등 만들어서 다른데에 넣어주면 좋아

//dp문제는 일단 바로 생각 안나면넘어가랑..

//문제를 봤는데 수단이 보여.. 근데 그 수단이 구현하기에 너무 복잡해 보이면 걍 넘겨....도대...
//
class a{
public: 
static int b;

     static void aaa()
    {
       static  int b;
        cout<<b;
    } 

};

int main()
{
// a a;
// a.aaa();
cout<<(char) ('A' +32);

}

// #include <string>
// #include <vector>
// #include <iostream>
// using namespace std;

// string calc(string &expression, char oper)
// {
//     string num;
//     string ret;
//     char ex_oper ='X';
//     vector<int> num_stack;
//     int index=0;
//     for(int i=0; i< expression.size() ; i++)
//     {
//         char c= expression[i];
//         if(c >= '0' && c <= '9')
//         {    
//             num+= c;
//             if(i== expression.size()-1)
//             {
//                 // if(ex_oper= 'X')
//                 // {
//                 //     return num;
//                 // }
                
//               if(ex_oper != oper) 
//                 ret+= to_string(num_stack.back()) + ex_oper + num;
              
//                 else    
//                  {
//                     if(oper =='+')
//                      ret+= to_string( num_stack.back() + stoi(num) );
//                      if(oper =='-')
//                      ret+= to_string( num_stack.back() - stoi(num) );
//                      if(oper =='*')
//                      ret+= to_string( num_stack.back() * stoi(num) );
//                      if(oper =='/')
//                      ret+= to_string( num_stack.back() / stoi(num) );

//                 }         
                    
//                     return ret;
//             }
        
//         }
//         else
//         {
//             if(num_stack.empty())
//             {     
//                 num_stack.push_back( stoi(num) );
//                 num.clear();
//                 ex_oper =c;
//                 continue;
//             }
//             if(ex_oper != oper) //전에 들어있던 oper 가 해야될 연산이 아니면 스택에 들어있는것을 그대로 ret에 넣기
//                 ret+= to_string(num_stack.back()) + ex_oper;
//             else    //전에 들어있던 oper가 해야될 연산이면 연산을 해서 넣어
//             {
//                 if(oper =='+')
//                 ret+= to_string( num_stack.back() + stoi(num) )+ex_oper;
//                 if(oper =='-')
//                 ret+= to_string( num_stack.back() - stoi(num) )+ex_oper;
//                 if(oper =='*')
//                 ret+= to_string( num_stack.back() * stoi(num) )+ex_oper;
//                 if(oper =='/')
//                 ret+= to_string( num_stack.back() / stoi(num) )+ex_oper;

//             }
//             //지금 만들어진 숫자는 스택에 넣어
//             num_stack.push_back( stoi(num) );
//             num.clear();
//             ex_oper =c;
//         }

//     }
    

// }

// long long solution(string expression) {
//     long long answer = 0;
//     string ex_oper, end_oper;
//     ex_oper = expression;
  
//     end_oper= calc(ex_oper , '+');
//     cout <<end_oper<<endl;
//     ex_oper= end_oper;
    
//     end_oper= calc(ex_oper , '-');
//     cout <<end_oper<<endl;
//         ex_oper= end_oper;
    
//     end_oper= calc(ex_oper , '*');
//     cout <<end_oper<<endl;
    
//     ex_oper= end_oper;
//     end_oper= calc(ex_oper , '/');
//     cout <<end_oper<<endl;
    
        


//     return answer;
// }
