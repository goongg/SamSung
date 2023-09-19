#include <iostream>
#include <queue>
#include <map>
using namespace std;


int dr[4] ={-1, 0, 1, 0};
int dc[4] ={0, 1, 0, -1};

#define uu 0
#define rr 1
#define dd 2
#define ll 3

typedef pair <int ,int> pii;
typedef pair<pii,  pii> piiii;
int N, M;
char m[11][11];

map<piiii, int> visit;
class ball
{
    public:
    int Red_r;
    int Red_c;
    int Blue_r;
    int Blue_c;
    int depth;
    int ex;
};
int Holl_r;
int Holl_C;
    ball b;

void print(ball u)
{
 
 cout<<endl;
    for(int i =0 ; i< N; i++)
    {
        for(int j =0 ;j<M; j++)
        {
            if(i==Holl_r && j==Holl_C)
            cout<<"O";

            else if(i==u.Blue_r && j== u.Blue_c)
             cout<<"B";

            else if(i==u.Red_r && j== u.Red_c)   
                cout<<"R";
            
            else cout<<m[i][j];
        }
        cout<<endl;
    }
}
//공을 이동시키는 함수
ball move(int d, ball v)
{

    bool red=0;
    switch(d)
    {
        case uu:
            if(v.Red_r < v.Blue_r)
                red=1;

                for(int i = v.Blue_r-1;  m[i][v.Blue_c] =='.' || m[i][v.Blue_c] =='O' ; i--)
                {
                    v.Blue_r=i;
                    if(m[i][v.Blue_c] =='O') break;
                }
                for(int i = v.Red_r-1; (m[i][v.Red_c] =='.' || m[i][v.Red_c] =='O' ) ; i--)
                {
                    v.Red_r=i;
                    if(m[i][v.Red_c] =='O') break;
                }

            if(v.Red_r==v.Blue_r && v.Red_c == v.Blue_c && red &&  m[v.Red_r ][v.Red_c] != 'O') // 빨간알이 더 위에있으면 
                v.Blue_r++;

            if(v.Red_r==v.Blue_r && v.Red_c == v.Blue_c && !red &&  m[v.Red_r ][v.Red_c] != 'O') 
                v.Red_r++;

        break;

        case rr:
            if(v.Red_c > v.Blue_c)
                red=1;

                for(int j = v.Red_c+1; m[v.Red_r][j] =='.' || m[v.Red_r][j] =='O' ; j++)
                {
                    v.Red_c=j;
                    if(m[v.Red_r][j] == 'O') break;
                }
                for(int j = v.Blue_c+1;  (m[v.Blue_r][j] =='.' || m[v.Blue_r][j] =='O')   ; j++)
                {
                    v.Blue_c=j;
                   if(m[v.Blue_r][j] == 'O') break;
                }
                      

            if(v.Red_r==v.Blue_r && v.Red_c == v.Blue_c && red &&  m[v.Red_r ][v.Red_c] != 'O') // 빨간알이 더 오른쪽에 에있으면 
                v.Blue_c--;

            if(v.Red_r==v.Blue_r && v.Red_c == v.Blue_c && !red &&  m[v.Red_r ][v.Red_c] != 'O') // 빨간알이 더 위에있으면 
                v.Red_c--;
         
        break;
        case dd:

            if(v.Red_r > v.Blue_r) //red 가 더 아래
                red=1;

                for(int i = v.Red_r+1; (m[i][v.Red_c] =='.' || m[i][v.Red_c] =='O') ; i++)
                {
                    v.Red_r=i;
                    if(m[i][v.Red_c] =='O') break;
                }

                for(int i = v.Blue_r+1;  (m[i][v.Blue_c] =='.' || m[i][v.Blue_c] =='O')   ; i++)
                {
                    v.Blue_r=i;
                    if(m[i][v.Blue_c] =='O') break;
                }


            if(v.Red_r==v.Blue_r && v.Red_c == v.Blue_c && red &&  m[v.Red_r ][v.Red_c] != 'O') // 빨간알이 더 오른쪽에 에있으면 
                v.Blue_r--;

            if(v.Red_r==v.Blue_r && v.Red_c == v.Blue_c && !red &&  m[v.Red_r ][v.Red_c] != 'O') // 빨간알이 더 위에있으면 
                v.Red_r--;

        break;
        case ll:
            if(v.Red_c < v.Blue_c)
                red=1;

                for(int j = v.Red_c-1; (m[v.Red_r][j] =='.' || m[v.Red_r][j] =='O') ; j--)
                {
                    v.Red_c=j;
                    if(m[v.Red_r][j] == 'O') break;
                }

                for(int j = v.Blue_c-1;  (m[v.Blue_r][j] =='.' || m[v.Blue_r][j] =='O') ; j--)
                {
                    v.Blue_c=j;
                    if(m[v.Blue_r][j] == 'O') break;
                }

            if(v.Red_r==v.Blue_r && v.Red_c == v.Blue_c && red &&  m[v.Red_r ][v.Red_c] != 'O') // 빨간알이 더 오른쪽에 에있으면 
                v.Blue_c++;

            if(v.Red_r==v.Blue_r && v.Red_c == v.Blue_c && !red &&  m[v.Red_r ][v.Red_c] != 'O') // 빨간알이 더 위에있으면 
                v.Red_c++;

        break;
    }

return v;
}

int bfs()
{
    ball u = b;
    u.ex=-1;
    queue<ball> q;
    q.push(u);
    int answer=99999;
    while(!q.empty())
    {
        u =q.front();
        q.pop();
    
        // print(u);
        // break;
        if(u.Red_r == Holl_r && Holl_C ==u.Red_c && !(u.Blue_r == Holl_r && Holl_C ==u.Blue_c) )
            return u.depth;

        else if(u.Blue_r == Holl_r && Holl_C ==u.Blue_c)
            continue;
        
        if(u.depth > answer) break;
        if(u.depth >10) break;

        for(int d =0; d<4 ;d++)
        {
            if(d != u.ex)
            {
                ball v= move(d, u);
                piiii check = make_pair( make_pair(v.Red_r, v.Red_c), make_pair(v.Blue_r, v.Blue_c) );
                if(visit.find(check)==visit.end())
                    visit[check] =1;   
                else
                    continue;

                v.depth++;
                q.push(v);
            }
        }

    }
if(answer==99999) answer=-1;

return answer;
}


int main()
{

    cin>> N>>M;
    for(int i =0; i<N; i++)x
    {
        for (int j =0 ; j< M; j++)
        {
            cin>>m[i][j];
            if(m[i][j]=='R')
            {
                b.Red_r=i;
                b.Red_c=j;
                m[i][j]='.';
            }
            else if(m[i][j]=='B')
            {
                b.Blue_r=i;
                b.Blue_c=j;
                m[i][j]='.';
            }
            else if(m[i][j]=='O')
            {
                Holl_r=i;
                Holl_C=j;
            }
        }
    }

// while(1)
// {
//     int d;
//     cin>>d;
//     b= move(d,b);
//     print(b);
// }
    cout<<bfs();
    return 0;
}