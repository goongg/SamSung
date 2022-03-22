#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
int A[2001];
pair<int, int> Q[1000001];

int s, e;
bool check(int s, int e)
{   
    if(A[s]== A[e])
    return 1;
    else    
    return 0;
}

bool dp[2001][2001];
int main()
{
    ios::sync_with_stdio(false);
        
    // memset(dp,0,sizeof(bool)*2001*2001);
    cin>>n;
    int a;
    for(int i=0; i<n; i++)
        cin>>A[i];

    cin >>m;
    for(int i=0; i<m; i++)
    {
        cin>>s;
        cin>>e;
        Q[i]=make_pair(s-1,e-1);
    }

    for(int i=0; i<n; i++)
        dp[i][i] =1;
    for(int i=0; i<n-1; i++)    
        dp[i][i+1] = check(i, i+1);
    for(int i=0; i< n-2; i++)
        dp[i][i+2] = check(i,i+2);
    for(int i=0; i<n-3; i++)
        dp[i][i+3]= dp[i+1][i+3-1]&check(i, i+3);


    for(int i=0; i<n; i++)
        for(int j=3; i+j <n; j++)   //4간격차이부터 4간격 차이는
            dp[i][i+j] = dp[i+1][i+j-1]&check(i, i+j);

    // for(int i= 1; i<n-1; i++)     //짝수기준해석
    // {
    //         for(int j=1; i-j >=0 && i+j+1<n; j++ )
    //         {
    //             dp[i-j][i+j+1]= dp[i-j+1][i+j-4]&check(i-j, i+j+1);
    //                 if(dp[i-j][i+j+1] ==0)
    //                     break; 
    //         }
    // }   



    // for(int i= 0; i<n; i++)     //홀수기준해석
    // {
    //         for(int j=2; i-j >=0 && i+j <n; j++ )
    //         {
    //             dp[i-j][i+j]= dp[i-j+1][i+j-1]&check(i-j, i+j);
    //                 if(dp[i-j][i+j] ==0)
    //                     break; 
    //         }
    // }   


    for(int i=0; i< m; i++)
    {
        // printf("%d \n",dp[Q[i].first][Q[i].second] );
        cout<<dp[Q[i].first][Q[i].second]<<'\n';
    }
}


// int t;
// int k;
// int chapter[500];
// int d[500][500]; // i부터 j까지 합친거의 최솟값
// //d[0][4] = min: 2* (d[0][0]+ d[1][4])   
// //               2* ( d[0][1] + d[2][4] )
// //               2* ( d[0][2] + d[3][4])
// //               2* ( d[0][3] d[4][4] )
// //
// int dp()
// {
//     //길이가 0인 두 값을 합치는데 드는비용
//     for(int i=0; i<k; i++)
//         d[i][i]=chapter[i];
//     //길이가 1인경우 두 값을 합치는데 드는 비용
//     for(int i=0; i<k-1; i++)
//     {    d[i][i+1] =( chapter[i]+chapter[i+1]);
//          cout << i << "-" << i+1 <<":"<<d[i][i+1]<<endl;   
//     }
//     // cout<<k<<endl;
//     for(int length=2; length <= k-1; length++)
//     {
//         // cout<<"??"<<endl;
//         for(int i=0; i+length<k; i++)
//         {
//             int m=1000000000;
//             for(int x=1; x< length-1; x++)
//                 m= min( m, 2*(d[i][i+x] + d[i+x+1][i+length]) ); 
//             m =min(m, d[i][i] + d[i+1][i+length]*2);
//             m= min(m, 2*d[i][i+length-1] + d[i+length][i+length]);
//             d[i][i+length]= m;   

//         cout << i << "-" << i+length <<":"<<d[i][i+length]<<endl;
//         }
//     }

//     return d[0][k-1];


// }
// int main()
// {
//     cin>>k;
//     for(int i=0; i<k; i++)
//         cin>>chapter[i];

//     cout<<dp();
    
// }


// 크리보드 점화식 문제 중에는 마지막에 들어오는게 뭔지 이해하는게 중요해!

// int n;
// long long d[101];

// long long dp(int k)
// {
//     d[1]=1;
//     d[2]=2;
//     d[3]=3;
//     d[4]=4;
//     d[5]=5;    
//     d[6]=6;

//     for(int i=7; i<=100;i++)
//     {
//         long long M=0;
//         for(int j=1; j<=i-3; j++)
//         {
//             M =  max(M, d[i-j-2]*(j+1) ); 
//         }
//         d[i]= M;
//     }

//     return d[k];
// }

// int main()
// {

//     cin>>n;
//     dp(n);
//     cout<<d[n];

// // cout<<endl;
// //     for(int i=1; i<=100;i++)
// //     cout<<i<<" "<<dp(i)<<endl;
// return 0;
// }
// 동전 1, 2, 3 더하기 논리 제대로 정리하기 노트에


// //범위... 라는것... 조건 이라는것을,... 잘 생각해보아야 한다....
// int n, k;
// int val[101];

// long long d[10001];

// void dp()
// {
//     d[0]=1;

//     for(int i=1; i<val[0]; i++)
//     {
//         if(i > k)
//             break;
           
//         d[i]=0;
//     }
//     for(int i=1; i<=k ; i++)
//     {
//         d[i]=0;
//     }
//     for(int ii=0; ii<n; ii++){
//         for(int i=val[ii]; i<=k;i++){
//            if(i > k)
//             break;
//            d[i] += d[i-val[ii]];
//         }
//     }
// }
// int main()
// {
//     cin>>n>>k;

//     for(int i=0; i<n; i++)
//         cin>>val[i];

// dp();
// // cout<<endl;
// //     for(int i=0; i<k ;i++)
// //     {
// //         cout <<i<<" " <<d[i]<<endl;
// //     }
//     cout<<d[k]<<endl;
// }

// vector<int> n;


//어떤수를 1또는 2 또는 3의 합으로 나타내는법
//d[2] =  1+1       // 2                            무리 2개
//d[3] =  1+ 1 + 1  // 2 +1 // 3                     무리 3개
//          1           2       1  
//d[4] =  1+1+1+1   // 1+ 1 + 2  //  2+2// 1+3//     무리 4개 
//          1           3           1       2
//d[5] =  1+1+1+1+1 // 1+1+1+2  // 2+2+1 // 3+2 // 3+1+1   무리 5개
//          1           4           3       2       3
//d[6] =  1....1    // 1+....+2 // 2+2+2 // 3+3 // 3+2+1 // 3+1+1+1   무리6개
//            1          5           1         1    6          4
//d[7] =      1         6           4         3       3         5        

        // 11 11 22
// int main()
// {
//     int t;
//     cin>>t;

//     for(int i=0; i<t; i++)
//     {   int a;
//         cin>>a;
//           n.push_back(a);
//     }
// }














// #include <iostream>
// #include <cmath>
// #include <string>
// #include <queue>
// #include <vector>
// #include <algorithm>
// using namespace std;

// int n;
// int num[2000];
// int s[1000000],e[1000000];
// int cent[1000000];

// bool d[2001][2001] ;

// bool check(int s, int e)
// {
//     if(num[s] == num[e])  
//         return 1;
//     else   
//         return 0;
// }

// void dp()
// {

//     for(int i=0; i<n-1; i++)
//     {
//         d[i][i]=1;
//         d[i][i+1]=check(i, i+1); 
//     }
//     d[n-1][n-1]=1;
    
//     for(int i=0; i<n; i++)
//     {
//         for(int j=1 ; (i-j >=0 && i+j <n) ; j++ )
//         {   
//              if(check(i-j,i+j))
//                 d[i-j][i+j] = 1 ;
//             else
//               break;
//         }

//         if(d[i][i+1] !=0)
//         for(int j =1; (i-j>=0) && (i+j+1<n) ; j++ )
//         {
//             if(check(i-j,i+1+j)) 
//               d[i -j][i+1 +j] = 1;
//             else 
//                 break;
//         }
//     }
// }

// int m;


// int main()
// {
//     cin>> n;

//     for(int i=0; i<n; i++)
//         cin>>num[i];
//     cin>>m;
//     for(int i=0; i<m; i++)   
//         cin>> s[i] >> e[i];
    
//     dp();

//     // for(int i=0; i< n; i++){
//     //     for(int j=0; j<n; j++){
//     //         cout<<d[i][j]<<" ";
//     //     }
//     //     cout<<endl;
//     // }
//     for(int i=0; i<m; i++)
//         cout<< d[s[i]-1][e[i]-1] <<" " <<endl;    
// }

// 점프 지린다 dp라고하는 거슨...
// 먼저 dp -> 다른방법 생각이 맞는듯
// DP로 풀수 있는지 없는지를 판별하는게 중요하네
// 출제자의 의도를 생각할 수 있는 레벨로 올라가면 돼

//     int n;
//     int t[10000];
//     long long d[10000] ={1}; //d까지 가는 경로의 수

// long long dp() //현재 위치에서 a, b로 가는 경로의 수
// {
//       for(int i=0; i<n; i++){
//         for(int j=0; j<n; j++){
        
//             if(i !=0){   //맨 윗줄이 아닐때만 위를 조사
//                 for(int k=1; k<=i ;k++){
//                     if(t[ (i-k)*n+j] == k){
//                         d[i *n+j ] += d[(i-k)*n+j];
//                     }
//                 }
//             }

//             if(j!=0){
//                 for(int k=1; k<=j ;k++){
//                     if(t[ i*n+j-k] == k){
//                         d[i *n+j ] += d[i*n +j-k];
//                     }
//                 }
//             }
//             // cout<< d[i *n+j ]<< " ";
//         }
//         // cout<<endl;
//     }
//     //   cout<<endl;
   
//     return d[n*n-1];
// }

// int main()
// {
//     cin>>n;
    
//     for(int i=0; i<n; i++)
//         for(int j=0; j<n; j++)
//             cin>>t[i*n+j];
//     //   cout<<endl;

//     cout<< dp();
// }


// //아아.. 디피라는방식으로 푸러보자..
// //아아.. 디피라는것은 존나게 아름다운 거구나
// //코딩속도... 생각 다 존나 완벽한 알고리즘이다.
// int n, m;
// int t[1001][1001];
// int d[1001][1001];  // i*m+j 까지 갈때까지의 최댓값
// // 

// int dp(int a, int b)
// {

//     for(int i=1; i<=n; i++)
//         for(int j=1; j<=m; j++)
//             d[i][j] = max( d[i-1][j] + t[i][j], d[i][j-1] + t[i][j] ) ;
//     return d[a][b];
// }

// int main()
// {
//     cin >> n >> m;
//     for(int i=1; i<= n; i++)
//         for(int j=1; j<=m; j++)
//             cin >> t[i][j];

//     cout<<dp(n, m);

//     // cout<<endl;
//     // for(int i=1; i<= n; i++){
//     //     for(int j=1; j<=m; j++)
//     //       cout<<  dp(i,j)<< " ";
//     //       cout<<endl;
//     // }
// }


/*
int n, m;
int table[1000000];

int dfs(int i); //현위치 i에서 이동하는 dfs
int bfs(int i); //현위치 i에서 이동하는 bfs
int cur;
int max;

int main()
{
    cin >> n >> m;
    for (int i = 0; i < n * m; i++)
        cin >> table[i];

    cout << dfs(0); //0으로 이동

    return 0;
}

int result;
int M;
int cnt;
int dfs(int i)
{

    if (i == 0)
        result += table[0];
    // cout<< "call :"<<i <<" " <<cnt++<<endl;
    
    if( i>= m*n)
        return M;

    if (i == n * m - 1) //현위치가 도착점이면 끝내고
    {
        if (M < result)
            M = result;
        return M;
    }

        if ((i + 1) % m != 0)
        {
            result += table[i + 1];
            dfs(i + 1);
            result -= table[i + 1];
        }
        //하로이동 할 수 있으면
        if ((i + m) <= n * m)
        {
            result += table[i + m];
            dfs(i + m);
            result -= table[i + m];
        }
    

    return M;
}
*/
