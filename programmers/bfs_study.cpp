#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <map>

#include <algorithm>
using namespace std;

<<<<<<< HEAD
//Test git
=======
//brunch test my idear1
//brunch test my idear1
>>>>>>> my_idear
//아 진짜... 힘이 쭉 빠진다.. 이거 할 수 있을까.. 시팔..

map<string, int> h;
string table;
int next_index;

bool move(string &s, int c)
{
    int zero;
    char temp;
    for(int i=0; i<s.size(); i++)
        if(s[i]=='0')
            zero=i;

    switch(c)
    {
        case 0: //u
            if(zero>=3)
            {
                temp= s[zero-3];
                s[zero-3]= '0';
                s[zero]= temp;
            }
        break;
        case 1: //d
            if(zero<=5)
            {
                temp= s[zero+3];
                s[zero+3]= '0';
                s[zero]= temp;
            }

        break;
        case 2:
            if(zero%3 !=2)
            {
                temp= s[zero+1];
                s[zero+1]= '0';
                s[zero]= temp;
            }

        break;
        case 3:
            if(zero%3 !=0)
            {
                temp= s[zero-1];
                s[zero-1]= '0';
                s[zero]= temp;
            }
        break;    
    }
    if( h.find(s) == h.end())
    {
        h[s]=next_index++;
      return 1;
    }
    else
        return 0;

}


int bfs(string s)
{
    next_index=0;
    class item{
        public:
        int depth;
        string t;
    };
    // memset(check,0, sizeof(bool)* 3862881);
    queue<item> q;
    item v, w;
    v.depth=0;
    v.t=s;    
    q.push(v);
     h[s] =next_index;
     next_index++;
    while(!q.empty())
    {
        v=q.front();
        q.pop();
        w=v;
        string temp;
        // cout<<v.t<<endl;
        //종료조건

        if(v.t == "123456780")
            return v.depth;
       
        for(int i=0; i<4; i++){
            w=v;
            if( move(w.t, i) )  // 안가본 곳이면 q에 넣어
            {
                w.depth+=1;
                q.push(w);
            }
        }
    }

    return -1;

}


int main()
{
int t;
int i=0;

// cout<<i<<endl;
string s;
// move(s,)
// cout<<"hash"<< h[s];

  
    for(int i=0; i<9 ; i++)
    {
        cin>>t;
        s += to_string(t);
    }

    cout<<bfs(s)<<endl;



}


// int n, m;
// char table[100];

// pair <int, int > pos_R;
// pair <int, int > pos_B;

// pair <int, int > ex_R;
// pair <int, int > ex_B;

// void view_table()
// {

//     for(int i=0; i<n; i++)
//     {    for(int j=0; j<m;j ++)
//             cout<< table[i*n+j];
//         cout<<endl;
//     }
// }


// int move(char d)
// {

//     for(int i=0; i<n; i++)
//         for(int j=0; j<m;j ++)
//         {
//             if(table[i*n+j] == 'R')    
//                 pos_R= make_pair(i,j);
//             if(table[i*n+j] == 'B')    
//                 pos_B= make_pair(i,j);
//         }
//     cout<< pos_R.first<<" "<< pos_R.second<<endl;
//     cout<< pos_B.first<<" "<< pos_B.second<<endl;
// switch(d)
// {
    
//     case 'U':

//         while(1)        
//         {   

//             ex_B = pos_B;
//             ex_R= pos_R;
//             if(table[ (pos_R.first-1) * n  + pos_R.second] == '.') //R의 위치를 위로 변경 // #이나 O가 아닐때 까지
//             {       
//                    table[ (pos_R.first-1) * n  + pos_R.second] = 'R';
//                    table[ (pos_R.first) * n  + pos_R.second] = '.';
//                    pos_R.first--;
//             }

//             if(table[ (pos_R.first-1) * n  + pos_R.second] == 'O') //R의 위치를 위로 변경 //O 면 성공했으니 count return
//             {        
//                     table[ (pos_R.first) * n  + pos_R.second] = '.';
//                     return 1;
//             }


//             if(table[ (pos_B.first-1) * n  + pos_B.second] == '.') //R의 위치를 위로 변경 // #이나 O가 아닐때 까지
//             {       
//                    table[ (pos_B.first-1) * n  + pos_B.second] = 'B';
//                    table[ (pos_B.first) * n  + pos_B.second] = '.';
//                    pos_B.first--;
//             }
            
//             if(table[ (pos_B.first-1) * n  + pos_B.second] == 'O') //R의 위치를 위로 변경 // #이나 O가 아닐때 까지       
//             {
//                 table[ (pos_B.first) * n  + pos_B.second] = '.';
//                 return -1;
//             }

//             if( ex_B== pos_B && ex_R==pos_R)    //더이상 움직일 수 없을때 break;
//                 return 0;       
            
//         }
//     break;

//     case 'D':
//         while(1)        
//         {   

//             ex_B = pos_B;
//             ex_R= pos_R;
//             if(table[ (pos_R.first+1) * n  + pos_R.second] == '.') //R의 위치를 위로 변경 // #이나 O가 아닐때 까지
//             {       
//                    table[ (pos_R.first+1) * n  + pos_R.second] = 'R';
//                    table[ (pos_R.first) * n  + pos_R.second] = '.';
//                    pos_R.first++;
//             }

//             if(table[ (pos_R.first+1) * n  + pos_R.second] == 'O') //R의 위치를 위로 변경 //O 면 끝내야제
//             {
//                 table[ (pos_R.first) * n  + pos_R.second] = '.';
//                 return 1;
//             }


//             if(table[ (pos_B.first+1) * n  + pos_B.second] == '.') //R의 위치를 위로 변경 // #이나 O가 아닐때 까지
//             {       
//                    table[ (pos_B.first+1) * n  + pos_B.second] = 'B';
//                    table[ (pos_B.first) * n  + pos_B.second] = '.';
//                    pos_B.first++;
//             }
            
//             if(table[ (pos_B.first+1) * n  + pos_B.second] == 'O') //R의 위치를 위로 변경 // #이나 O가 아닐때 까지       
//             {
//                 table[ (pos_B.first) * n  + pos_B.second] = '.';
//                 return -1;
//             }

//             if( ex_B== pos_B && ex_R==pos_R)    //더이상 움직일 수 없을때 break;
//                 return 0;

//         }


//     break;
    
//     case 'R':

//         while(1)        
//         {   
//             ex_B = pos_B;
//             ex_R= pos_R;
//             if(table[ (pos_R.first) * n  + pos_R.second+1] == '.') //R의 위치를 위로 변경 // #이나 O가 아닐때 까지
//             {       
//                    table[ (pos_R.first) * n  + pos_R.second+1] = 'R';
//                    table[ (pos_R.first) * n  + pos_R.second] = '.';
//                    pos_R.second++;
//             }

//             if(table[ (pos_R.first) * n  + pos_R.second+1] == 'O') //R의 위치를 위로 변경 //O 면 끝내야제
//             {
//                 table[ (pos_R.first) * n  + pos_R.second] = '.';
//                 return 1;
//             }     


//             if(table[ (pos_B.first) * n  + pos_B.second+1] == '.') //R의 위치를 위로 변경 // #이나 O가 아닐때 까지
//             {       
//                    table[ (pos_B.first) * n  + pos_B.second+1] = 'B';
//                    table[ (pos_B.first) * n  + pos_B.second] = '.';
//                    pos_B.second++;
//             }
            
//             if(table[ (pos_B.first) * n  + pos_B.second+1] == 'O') //R의 위치를 위로 변경 // #이나 O가 아닐때 까지       
//             {
//                 table[ (pos_B.first) * n  + pos_B.second] = '.';
//                 return -1;
//             }       

//             if( ex_B== pos_B && ex_R==pos_R)    //더이상 움직일 수 없을때 break;
//                 return 0;

//         }
//     break;
    
//     case 'L':
//         while(1)        
//         {   
//             ex_B = pos_B;
//             ex_R= pos_R;
//             if(table[ (pos_R.first) * n  + pos_R.second-1] == '.') //R의 위치를 위로 변경 // #이나 O가 아닐때 까지
//             {       
//                    table[ (pos_R.first) * n  + pos_R.second-1] = 'R';
//                    table[ (pos_R.first) * n  + pos_R.second] = '.';
//                    pos_R.second--;
//             }

//             if(table[ (pos_R.first) * n  + pos_R.second-1] == 'O') //R의 위치를 위로 변경 //O 면 끝내야제
//             {
//                 table[ (pos_R.first) * n  + pos_R.second] = '.';
//                 return 1;
//             }

//             if(table[ (pos_B.first) * n  + pos_B.second-1] == '.') //R의 위치를 위로 변경 // #이나 O가 아닐때 까지
//             {       
//                    table[ (pos_B.first) * n  + pos_B.second-1] = 'B';
//                    table[ (pos_B.first) * n  + pos_B.second] = '.';
//                    pos_B.second--;
//             }
            
//             if(table[ (pos_B.first) * n  + pos_B.second-1] == 'O') //R의 위치를 위로 변경 // #이나 O가 아닐때 까지       
//             {
//                 table[ (pos_B.first) * n  + pos_B.second] = '.';
//                 return -1;
//             }           

//             if( ex_B== pos_B && ex_R==pos_R)    //더이상 움직일 수 없을때 break;
//              return 0;
//         }
//     break;
// }

// }

// int bfs()
// {
//     class item
//     {
//         public:
//         pair<int, int> pos_R;
//         pair<int, int> pos_B;
//         int count;
//     };

//     queue<item> q;
//     item  V, W;
//     V.pos_R = pos_R;
//     V.pos_B = pos_B;
//     V.count=0;


//     q.push(V);

//     while(1)
//     {
//         W= q.front();
//         q.pop();
        
//         move('U');

//     }

// }



// int main()
// {
// cin>>n>>m; 
// for(int i=0; i<n; i++)
//     for(int j=0; j<m;j ++)
//         cin>>table[i*n+j];

// int count=0;

// // char com;
// // while(1)
// // {
// //     cin>>com;
// //    count= move(com);
// // view_table();
// // }

// cout<<count<<endl<<endl;
//    count= move('L',  count);
// view_table();
// cout<<count<<endl<<endl;

//    count= move('U',  count);
// view_table();
// cout<<count<<endl<<endl;

//    count= move('D',  count);
// view_table();
// cout<<count<<endl<<endl;




// int T;
// int A, B;
// bool check[10000];

// int calc(char a, int A)
// {
//     int d[4];
//     string S_A=to_string(A);
    
    
//     d[3]=S_A[0] - '0' ; //1000의 자리수
//     d[2]=S_A[1] - '0' ;
//     d[1]=S_A[2] - '0' ;
//     d[0]=S_A[3] - '0' ; //1의 자리수

//     int buf;
//     switch(a){

//         case 'D': 
//             if(A*2 >9999)
//             return 2*A;
//             else
//             return 2*A % 10000;
//         break;


//         case 'S': 
//             if(A==0)
//                 return 9999;
//             else
//                 return A-1;    
//         break;


//         case 'L':
//             buf = d[3];
//             d[3]=  d[2];
//             d[2] = d[1];
//             d[1] = d[0];
//             d[0] = buf; 
//            return  d[3]*1000 + d[2]*100 + d[1]*10 + d[0];
//         break;


//         case 'R': 
//             buf = d[0];
//             d[0] = d[1];
//             d[1] = d[2];
//             d[2] = d[3];
//             d[3] = buf; 
//            return d[3]*1000 + d[2]*100 + d[1]*10 + d[0];
//         break;

//     }

// }

// string bfs(int A, int B)
// {
//     queue<pair< int, string>> q;
//     string S;

//     q.push( make_pair(A,S) );

//     memset(check, 0, sizeof(bool)*10000);
//     check[A]=1;
//     pair<int, string> V;
// int temp;
//     while(1)
//     {        
//         V= q.front();
//         q.pop();

//         if( V.first == B)
//             return V.second;

//         else
//         {
//             temp =  calc('D',V.first);
//             if(check[temp]==0)
//             {      
//                 q.push(make_pair( temp, V.second+'D' ) );
//                 check[temp]=1;
//             }
            
//             temp =  calc('S',V.first);
//             if(check[temp]==0)
//             {      
//                 q.push(make_pair( temp, V.second+'S' ) );
//                 check[temp]=1;
//             }

//             temp =  calc('L',V.first);
//             if(check[temp]==0)
//             {      
//                 q.push(make_pair( temp, V.second+'L' ) );
//                 check[temp]=1;
//             }

//             temp =  calc('R',V.first);
//             if(check[temp]==0)
//             {      
//                 q.push(make_pair( temp, V.second+'R' ) );
//                 check[temp]=1;
//             }
//         }
//     }
// }
// vector<string> ans;

// int main()
// {

//     // cout <<calc( 'L',1000);
//     // cin>>T;
//     // for(int i=0; i<T; i++)
//     // {   
//     //     cin>>A>>B;
//     //     cout<<bfs(A,B)<<endl;
//     //     // ans.push_back( bfs(A,B));
//     // }

//     // for(string s :ans)
//     // cout<<s<<endl;
// }

