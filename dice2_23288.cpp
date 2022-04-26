#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dr[4]={-1, 0, 1, 0};
int dc[4]={0, 1, 0, -1};

#define U 0
#define R 1
#define D 2
#define L 3


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

class _pos {
    public:
    int r; int c;
};
class Board{
public:
    int N, M ,K;
    int t[21][21];
    int point[21][21];
    bool visit[21][21];
    Dice d;
    void input()
    {
        cin>>N>>M>>K;
        for(int i=0; i< N; i++)
            for(int j=0; j<M; j++)
                cin>>t[i][j];

        for(int i=0; i< N; i++)
            for(int j=0; j<M; j++)
            {    
                visit[i][j]=0;
                point[i][j]=0;
            }
    }
    void make_point()
    {
        for(int i=0; i< N; i++)
            for(int j=0; j<M; j++)
            {
                // cout<<i<<","<<j<<" : 인접면 조사:";
                bfs(i, j);  //목표는 i,j와 인접한 면을 찾아서 값을 쓰고, 방문처리를함            
            }
    }
    void print()
    {
        cout<<endl<<endl;;
        for(int i=0; i< N; i++)
        {   
            for(int j=0; j<M; j++)
                cout<<point[i][j]<<" ";
            cout<<endl;
        }
    }
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


    int solve()
    {
        int result=0;
        input();
        make_point();
        // print();
        
        while(K-- >0)
        {
            if(d.r +dr[d.d] <0 || d.r +dr[d.d]  >= N || d.c +dc[d.d] <0 || d.c +dc[d.d] >=M)
                d.d= (d.d+2) %4; //이동못하면 방향바꿈

            // cout<<"move (U0 R1 D2 L3) :"<< d.d<<endl;            
            d.move();
            // d.print();
            result += point[d.r][d.c];
            int A = d.s[2];
            int B = t[d.r][d.c];
            
            if(A>B) d.d = (d.d+1)%4;
            else if(A<B) d.d = (d.d -1 +4)%4;


        }
        return result;
    }
};


int main()
{
Board b;  
cout <<b.solve()<<endl;
    return 0;
}