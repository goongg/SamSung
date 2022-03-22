#include <iostream>
#include <cmath>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;



// /*스타트와 링크... 어제 공부한거 잘 써먹어보자*/
// //아무리 그래도 터무니 없이 더 많이 반복하도록 짜면 안되는구나...
// //능숙해진다면, 내가 조사해야하는 경우의 수를 보고
// //브루트 포스를 해야할지 감을 잡아야돼
// //가령 조합하고 순열의 경우의 수 차이는 엄청남
// //순열을 같은것이 있는 순열로 바꿔서 풀면 조합이 가능해 이것도 참고해!!

// int n;
// int S[400];

// int CalcTeamAbility(vector<int> m);
// void setMemeber(vector<int> &m, vector<int> &c );

// int fact(int n)
// {
//     int ret=1;
//     for(int i=1; i<n; i++)
//     {
//         ret*=i;
//     }
//     return ret;
// }

// int main()
// {
//     cin >> n;
//     for (int i = 0; i < n * n; i++)
//         cin >> S[i];
    
//     vector<int> Member(n);
//     vector<int> Combination;

//     for(int i=0; i<n/2; i++)
//     {    
//         Combination.push_back(0);
//         Combination.push_back(1);
//     }
//     sort(Combination.begin(), Combination.end());


//     // int end = fact(n)/2;
//     int cnt =0;
//     int min= 10000000;

//     // cout << fact(20)<<endl;
//     do{

//         setMemeber(Member,  Combination);
//         int def= CalcTeamAbility(Member);
//         if( def<min)
//             min = def;

//     }while ( next_permutation(Combination.begin(), Combination.end()));
    
//     cout <<min;

// }
// void setMemeber(vector<int> &m, vector<int> &c )
// {

// // cout<<endl;
//     int cntF=0;
//     int back=n-1;
//     int cnt=0;
//     for(int i : c)
//     {
        
//         if(i==0)
//         {
//             m[cntF] = cnt;
//             cntF++;
//         }
//         else
//         {
//             m[back]= cnt;
//             back--;
//         }
//         cnt++;
//     }

//     // for(int i: c)
//     // {

//     //     cout<< i<<" ";
//     // }
//     // cout<<endl;
//     // for(int i: m)
//     // {

//     //     cout<< i<<" ";
//     // }
//     // cout<<endl;

// }



// int CalcTeamAbility(vector<int> m)
// {
//     int s=0;
//     int l=0;
//     for(int i =0; i< m.size()/2; i++){
//         for(int j =0; j< m.size()/2 ; j++){    
//             s+=  S[ m[i]*n + m[j] ] ; 
//             l+=  S[ m[n-i-1]*n + m[n-j-1] ]; 
//         }
//     }
//     return abs(s-l);
// }


/*
    단어수학 마스터했다...
배운점 1.
string S
반복문 간지나게 쓰기 이거 개좋다
1. for(char x: S)
{
    cout<< x;
}
배운점 2.
#include <algorithm> 이거 개쩐다.
sort( s.begin(), s.end() ) 이거 개쩐다
소팅할라고 노가다했던거 기억나지?

배운점 3.
s.erase( unique(s.begin(), s.end()), s.end()) 
 erase 는 문법이 진짜 많은데 일단 이것만 기억하자
erase(1, 4); 1번째 부터 4개 삭제
unique(1, 4); 1번째부터 4번쨰까지 중복되는 것들을 뒤로보내버려
두개 섞어서 쓰면 중복되는것만 지울 수 있어
    이거 개쩐다

배운점 4.
next_permutation(begin, end)
이거 개쩐다. 순열 만들라고 개고생했던거 기억나지?

배운점 5.
do
{}while(1);
이거 개쩐다. 두와일 할일 은근 많은거 알지?

배운점 6. 
동.적.할.당.쓰.지.말.고 vector 써 무조건이야
개쩔어 알면알수록 개쩔어


    vector쓰는법.

    vector
    
     쓰는법을 공부 시작..
    vector<char> letters;

    1.sort(letters.beging(), letters(end)); -> 이거 좋아 존나좋아
    2. letters.erase( unique(letters.beging(), letters.end()), letters.end());  
     이거 무슨원리야?
    난생 처음 써봤어... 이거 개쩌러..

    단어수학 코드 스터디부터 하자 이거 씨발 나도 할순있는데 그냥 개쩌는거 같음
*/

// int main()
// {

// int N;
// cin>>N;
// vector<string> V_words(N);
// string letters;

//     for(int i=0; i< N ;i++)
//     {
//         cin>> V_words[i];

//         for(char c: V_words[i])
//         {
//             letters.push_back(c);
//         }
//     }
//     sort(letters.begin(), letters.end());
//     letters.erase(  unique(letters.begin(), letters.end()) , letters.end() );

//     vector<int> V_num;
//     int r = letters.size();
//     for(int i =0; i< r; i++)
//     {
//         V_num.push_back(9-i);
//     }
//     sort(V_num.begin(), V_num.end());
//     int k=0;

//     // for(int i : V_num)
//     // {
//     //     cout<<i  <<endl;

//     // }
//     // for(char c : letters)
//     // {
//     //     cout<<c<<endl;
//     // }
//     // cout<<endl;

//     int max=0;

//     do{
//         int result=0;

//         for(string s: V_words)
//         {
//             int word2num =0;
//             for(char c: s)
//             {

//                 word2num +=  V_num[letters.find(c)];
//                 // cout<<word2num<<endl;
//                 word2num *=10;

//             }
//             // cout<<endl;
//             word2num/=10;
//             result += word2num;
//         }

//         // cout<< endl<<result<<endl;
//         if(max< result) max= result;
//         // cout<<result<<endl;
//     }while(    next_permutation(V_num.begin(), V_num.end()));

//     cout<<max;
// }
// }
// char alpha[256];
// int calc(vector<string> &a, vector<char> &letters, vector<int> &d)
// {
//     int m = letters.size();
//     int sum = 0;
//     for (int i = 0; i < m; i++)
//     {
//         alpha[letters[i]] = d[i];
//     }
//     for (string s : a)
//     {
//         int now = 0;
//         for (char x : s)
//         {
//             now = now * 10 + alpha[x];
//         }
//         sum += now;
//     }
//     return sum;
// }
// int main()
// {
//     int n;
//     cin >> n;
//     vector<string> a(n);
//     vector<char> letters;
//     for (int i = 0; i < n; i++)
//     {
//         cin >> a[i];
//         for (char x : a[i])
//         {
//             letters.push_back(x);
//         }
//     }
//     sort(letters.begin(), letters.end());
//     letters.erase(unique(letters.begin(), letters.end()), letters.end());
//     int m = letters.size();
//     vector<int> d;
//     for (int i = 9; i > 9 - m; i--)
//     {
//         d.push_back(i);
//     }
//     sort(d.begin(), d.end());
//     int ans = 0;
//     do
//     {
//         int now = calc(a, letters, d);
//         if (ans < now)
//         {
//             ans = now;
//         }
//     } while (next_permutation(d.begin(), d.end()));
//     cout << ans << '\n';
//     return 0;
// }

//걍 수녈을 만들어봐써... bfs로 이게 의미가 있는지는 몰겠어...

// class PC
// {
//     public:
//     bool isUsed[10]= {false,false,false,false,false,false,false,false,false,false };
//     int r=0;
//     int p[10] ={-1,-1,-1,-1,-1,-1,-1,-1,-1, -1 };
// };

// queue<PC>PQ;
// int main()
// {
//     int rr;
//     cin >>rr;
//     PC V;
//     // V.r =0;
//     V.p ;

//     PQ.push(V);
//     while(1)
//     {
//         bool flag=false;
//         PC W;
//         W = PQ.front();
//         if(W.r ==rr)
//             break;
//         PQ.pop();
//         cout<<W.r<<endl;
//         for(int j=0; j<10; j++)
//         {
//             V=W;

//            if (V.isUsed[j]== false)
//             {
//                 V.p[V.r] = j;
//                 V.isUsed[j] =true;
//                 if(V.r != rr)
//                 {
//                     V.r++;
//                     PQ.push(V);
//                 }
//             }
//         }
//     }
//         int cnt =1;
//     while(!PQ.empty())
//     {
//         PC WW;
//         WW= PQ.front();
//         PQ.pop();

//         cout<< cnt++ <<" :" ;
//         for(int i=0 ; i< rr; i++)
//         {
//             cout<< WW.p[i] <<" ";

//         }
//             cout<<endl;
//     }
// }

//수 이어쓰기... 이거슨... 너무나 쉬워버렸어
// 하지만 자리수 빨리 알아내는 개쩌는 스킬을하나 배웠다.
// to_string
// int main()
// {
// int N;
// cin>> N;
// int length=0;

// for(int i=1; i<=N; i++)
//     length+= to_string(i).length();

// cout << length;
// }

// int main()
// {
// int N;

// cin>>N;
// int cnt =1;

//  int i=N;
// while(i>0)
// {
//     if( i / 10 != 0)
//         cnt++;

//     i/=10;
// }

// // cout <<cnt<<endl;

// int result=0;

// for(int k=1; k<cnt; k++)
// {
//     result +=  9* pow(10, k-1) *k;
// }
// result += (N- pow(10, cnt-1) +1 ) * cnt;

// cout<< result;
// }

/*
부르트포쓰.. 카잉달력 05 02... 씨팔...
*/
/*
int N, M;
int x, y;
int T;


int main()
{
cin >> T;
    while(T--)
    {
        cin >> M>> N>> x >> y;
        x-=1;
        y-=1;
        bool ok = false;

        for(int k=x ; k <N*M; k+=M)
        {
            if(k%N ==y){
            cout<< k+1<<"\n";
            ok=true;
            break;
            }
        }
        if(!ok)
        {   cout<<-1<<'\n';
        }
    }
}

*/

/*리모콘... 05 02/ 부르트포쓰.. ---------------------------------------*/
/*
int N;
int M;
int Try= 100000000;
bool broken[10];
int possible( int c);




int main()
{
    cin>>N;
    cin>>M;

    for(int i=0; i<M; i++)
    {
        int n;
        cin>>n;
        broken[n] =true;
    }

int i;
// cin>>i;
    for(int i=0; i<=1000000; i++)
    {
        int c = i;
        int len;
        len= possible(c);
// cout<< "len:" <<len <<endl << "c:" <<c<<endl;;
        if(len >0)
        {
            if(Try > len + abs(c -N))
            Try =   len + abs(c -N);
        }
    }
    cout << Try;
}
// for check
// for(int i=0; i <10 ; i++)
// cout << broken[i] << " "<<endl;   

int possible( int c)
{
    int len=0;
    if (c==0)
    {   if( broken[c] == 1) 
            return 0;
        else
        {
            return 1;
        } 
    }
    while(c>0)
    {
        if(broken[c%10] == true)  //가장끝자리 고장났으면
        {                          //0 
             return 0;
        }
        else                    //고장난거 아니면 
        {
            len+=1;
            c/=10;
        }
    }
    return len;
}

*/
