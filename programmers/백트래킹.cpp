#include <iostream>
#include <cmath>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

//맞춰봐 다시

//     int n;
//     char s[55];
// vector<int> ans;
//     bool isused[21];

// bool ok( vector<int> v)
// {
//     bool result =false;
//     int sum;
//     int cnt=0;
//     for(int i=0; i<n; i++){
//         for(int j=i ; j<n; j++){
//                 sum=0;
//             for(int k= i ; k<=j;k++)
//                 sum+=v[k];                
            
//             if(sum>0 && s[cnt] =='+')
//                 result =true;
//             if(sum<0 && s[cnt] =='-')
//                 result =true;
//             if(sum==0 && s[cnt] =='0')
//                 result =true;
//             cnt++;
            
//             if(result == false)
//             return false;
//         }
//     }

//     return true;
// }

// void go(int index, vector<int> &v)
// {

//     if(v.size()==n) // 20개를 넣었으면 끝
//     {
//         // for(int i: v)
//         //     cout<< i<<" ";
//         // cout<<endl;
    
//         if(ok(v)) // 이 조합이 ok면 정답에 넣고 return;
//             ans= v;
//         return;

//     }

// int start_index= -10;
// int end_index = 10;
// if(s[v.size()*(n+1)] == '-')
// {
//     start_index=-10;
//     end_index=-1;

// }
// else if(s[v.size()*(n+1)] == '+')
// {
//     start_index=1;
//     end_index=10;
// }
// else if(s[v.size()*(n+1)] == '0')
// {
//     start_index=0;
//     end_index=0;
// }
//     for(int i=start_index ; i<=end_index; i++ )   //-10 ~ 10 까지를 넣어
//     {
//         if( isused[i+10] ==false)   //사용된숫자가 아니면
//         {  
//             v.push_back(i);
//             isused[i+10] = true;
//             go(i, v);
            
//             isused[i+10] = false;
//             v.pop_back();
//         }
//     }

// }

// int main()
// {
//     cin>>n;
//     for(int i=0; i< (n*(n+1))/2;i++)
//         cin>>s[i];
    
//     vector<int> v;
//     go(0,v );

//     for(int i: ans)
//         cout<< i<<" ";
//     cout<<endl;

// }


// char s[55];
// vector<int> A;
// ]bool used[21];
// vector<int> ans;
// int howok=0;
// //백트래킹의 사고과정.... 씨발지린다....
// //백트래킹이라는 것은 어떻게 사고해야하는건지...
// //킹우의 수가 작으면 걍풀어
// //숫자가 늘어날 때마다 확정 지을 수 있는 부호가
// //1 3 5 7 개 씩 늘어남
// // 00 01 ...    0n
// //    11 12..   1n
// //       22 ..

// bool ok(vector<int> v, int size)
// {
//     howok++;
//     //  cout<<"ok"<<endl;
//     int cnt =0;
//     for(int i=0; i<=20; i++){
//         for(int j=i;j<=20; j++) 
//         {       //i  와 j가 선택
//             int sum[55];
//             for(int k=i; k<=j; k++) //이 포문의 결과가 i부터 j까지 더한 결과임
//                 sum+=v[k];          
            
//             bool result =false;
//             if(sum>0 && s[cnt] =='+')
//                 result = true;
//             else if(sum<0 && s[cnt] =='-')
//                 result =true;
//             else if(sum==0 && s[cnt] =='0')
//                 result =true;
//             cnt++;
//             if(result ==false)
//                 return false;
//         }
//     }

//     return true;

// }
// int n;

// // 이거... 찾기문제야 앞에서 부터 하나씩 넣어서 풀꺼야
// void go(int index, vector<int> &v)
// {
//     if(v.size()==n)
//     {
//         // cout<<"end!: ";
//         // for(int i: v)
//         //     cout<<i <<" ";
//         // cout<<endl ;
        
//         bool a= ok(v, 20);
//         // cout<<a;
//         if (a == true )
//         {
//             ans = v;
//             return;
//         }
//         return;
//     }
//     //어떤숫자든지 막 집어넣어
// // for(int l=1; l<5; l++){
//    if(s[0] =='-')
//     for(int i=-10; i <=10; i++)
//     {
//         if(used[i+10] == true)
//         continue;

//             used[i+10]=true;
//             v.push_back(i);

//             go(i, v);
            
//             used[i+10]=false;
//             v.pop_back();
        
//     }

//     else   
//     for(int i=10; i >=-10; i--)
//     {
//         if(used[i+10] == true)
//         continue;

//             used[i+10]=true;
//             v.push_back(i);
//             if(ok(v, v.size()) ==true)
//                go(i, v);
            
//             used[i+10]=false;
//             v.pop_back();
        
//     }
// // }
// }

// int main()
// {

//     cin>>n;
//     for(int i=0; i< (n*(n+1))/2 ; i++)
//         cin>>s[i];

//     vector<int> v;
//     go(-20, v);
//     for(int i : ans)
//     {
//         cout<<i<<" ";
//     }

//     // cout<<endl<<howok<<endl;
// }



//다시한번 풀어본당... 쿵쿵따 쿵쿵따
    // int k;
    // char d[10];
    
//백트래킹 쥰내 어렵네 시발꺼!!
//return 타입은 중요하지 않아.
//중요한건 일단 인풋인자로 다음 노드로 가기 위해 뭘 넣을지! 랑
//어디에 넣을지 두개만 인풋인자야 단건 생각하지마 진짜!
// 그리고 엔드조건! 마지막으로 호출된 시점이야
// 와 진짜 어렵다.. 근데 알겠어 더 익숙해지면 이게 더 쉬울수도 있을 수도 있다는거
//쉽게 생각하기로는 마지막에 체크할지 중간에 체크할지를 보면 돼

// vector<string> ans;
// bool used[10] ={false,false,false,false,false,false,false,false,false,false};
// bool ok( string);

// void go(int index, string num)
// {
//     if( index ==k+1)   //앞으로 더 넣을건 없어, 여기서 리턴해
//     {
//         if (ok(num) )  //넣을 수 있는지를 조사하는 함수를 만들면 편혀!
//         {   ans.push_back(num);  //그럼 다 끝난겨 정답 후보에 넣어
//             return;
//         }
//     }
//     for(int i=0; i<10; i++)
//     {
//         if(used[i]==false)
//         {
//             used[i]=true;
//             go(index+1, num + to_string(i));
//             used[i]=false;
//         }
//     }
// }
    //더 넣을게 있어? 그럼 넣어 뭘?
    


// int main()
// {

//     cin>>k;
//     for(int i=0; i<k; i++)
//         d[i];
    
//     vector<int> usingNum;
//     vector<bool> isUsed ;

//     for(int )
//     vector<int> num;

// }
    // cout<< char(1+ '0');
    // vector<int> v;
    // string A("HELLO");
    // cout <<A.find('H');
    // cout <<go(9, v)<<endl;
    // string m =go_min(0);


//부등호 (순열)
//세상에 안중요한 문제는 없어
//단위감각의 중요성을 알게 해줌.
//int 형의 최댓값은 21억정도야
//그래서 보통은 10억으로 잡지만
//얼마든지 넘을 수 있다는 감각이 있어야 함
// 10억으로 표현할 수 있는 숫자는 딱 10자리야 명심해

//   char d[100];
//    int k;
// long long possible(vector<int> pp);

// int main()
// {
 
//     cin>>k;    
//     for(int i=0 ; i<k; i++)
//         cin>>d[i];

//     vector<int> p;
//     for(int i=0; i<k+1; i++ )
//         p.push_back(9-i);
//     sort(p.begin(), p.end());
//      long long max =0;
//     long long ret=0;
//     do
//     {   
//         ret =possible(p); 
//         if(max <= ret) max =ret;

//     }while(next_permutation(p.begin(), p.end()) );

//     vector<int> q;
//     for(int i=0; i<k+1; i++ )
//         q.push_back(i);

//     sort(q.begin(), q.end());

//     long long min = 10000000000;
//     do
//     {   
//         ret =possible(q); 
//         if(ret >= 0)
//             if(min >= ret) min =ret;

//     }while(next_permutation(q.begin(), q.end()) );


// // cout<< max<<endl<<min<<endl;

// string maxS = to_string(max);
// string minS = to_string(min);

//     if (maxS.size() != k+1)
//         maxS.insert( 0, 1, '0' );

//     if (minS.size() != k+1)
//         minS.insert( 0, 1, '0' );

//     cout <<maxS <<endl <<minS;
// }



// long long possible(vector<int> pp)
// {
//     for(int i=0; i<k; i++ )
//     {
//         if (d[i] == '<')
//         {
//             if( pp[i] >pp[i+1] )
//                 return -1;
//         }
//         else
//         {
//             if( pp[i] <pp[i+1] )
//                 return -1;
//         }
//     }
// long long ret=0;
//     for(int i: pp)
//     {   
//         ret *=10;
//         ret += i;
//     }

// // cout<<ret;
// return ret;

// };





// //빽트래킹 확실히 어렵다. 근데 논리적으로 접근하기는 쉬워 디버깅이 어렵고
// //재귀 간지... 재귀쓰다가 즉 함수를 호출하기 전에 호출할지 말지를 판단하면 돼!
// //재귀 간지나게 쓰고싶으다...
//     int n;
//     int s[400];
//     int Min= 1000000000;

// int go(int index, vector<int> &first, vector<int> &second)
// {
  
//     int ans =-1;
//     int t1=-1;
//     int t2=-1;
//     if(index == n)
//     {    

//         t1=0;
//         t2=0;
//         if(first.size() != n/2 || second.size() != n/2) 
//             return -1;
   
//         for(int i=0; i< n/2; i++){
//             for(int j=0;  j<n/2 ;j++ ){            
//                 t1+=s[ first[i]*n + first[j] ];
//                 t2+=s[ second[i]*n+ second[j] ];
//             }
//         }
//         // cout<< abs(t1-t2)<<endl;
//         return abs(t1-t2);
//     }   //끝났으면 -1 혹은 찾아낸 값을 리턴함.

//     ans = -1;
//     t1 = -1;
//     t2 = -1;
//     // 아직 안끝났어. 그러면 넣어야지
//     if(first.size() <= n/2 -1) //넣을 수 있는지를 조사해
//     {                        //넣을 수 있으면
//         first.push_back(index); //인덱스에 사람을 넣고
//         t1 = go(index+1 ,first, second); //다음번째로 고     
//         first.pop_back();
//     }
    
//     if(second.size() <= n/2-1) //넣을 수 있는지를 조사해
//     {                        //넣을 수 있으면
//         second.push_back(index); //인덱스에 사람을 넣고
//         t2 = go(index+1 ,first, second); //다음번째로 고     
//         second.pop_back();
//     }

//     //만약 두 시행중 정답이 있었어 그러면 그 값중 작은거 리턴
//     if(t1 != -1 || t2 != -1)
//     {
//         if(t2 ==-1) //t2 는 정다야
//             return t1; //그럼 t1만 정답
//         else if(t1 ==-1)    //t1은 정답이 아니야  
//             return t2;      //그럼 t2만 정답
//         else            //둘다정답이야
//         {
//             if (t1 <t2)
//             return t1;

//             else
//             return t2;
//         }
//     } 
//     //아니여써 그러면 -1 리턴
//     else
//         return -1;


// }

// int main()
// {
//     cin>>n;
//     for(int i=0; i<n*n; i++)
//         cin>> s[i];
//     vector<int> F, S;

//     cout<< go(0, F, S) <<endl;
    
// }

