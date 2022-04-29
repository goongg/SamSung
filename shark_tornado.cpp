

#include <iostream>
#include <vector>
using namespace std;
//순서는 L부터
int dr[8] = {0,  1, 1, 1,  0, -1, -1, -1   };
int dc[8] = {-1,-1, 0, 1,  1,  1,  0, -1  };

#define L 0
#define D 2
#define R 4
#define U 6

struct tornato
{
    int r;
    int c;
    int d;
    int move_cnt; 
    int direct_cnt; 

    
};

class shark
{
    public:
    int N; 
    int t[500][500];
    tornato w;
    int Call_Cnt;
    int cur_move_cnt;
    int even;
    bool direct_change;

    int init;

    void input()
    {
        cin>>N;
        init=0;
        for(int i=0; i< N; i++)
            for(int j=0; j< N; j++)
                {
                    cin>>t[i][j];
                    init+= t[i][j];
                }
        w.r=  N/2;
        w.c= N/2;
        w.d = L;
        w.move_cnt = 1; //이 방향으로 이동해야하는 횟수
        w.direct_cnt =1;
        // cout <<"시작위치:" << 

        Call_Cnt=0;
        cur_move_cnt=1;
        even=1;        
        direct_change = 1;

    }

    void move() //토네이도의 이동 구현
    {
        w.move_cnt--;
        w.r = w.r + dr[w.d];
        w.c = w.c + dc[w.d];
    
        if(w.move_cnt==0)
        {
            if(even++ %2 ==0)
                cur_move_cnt++;
            w.move_cnt = cur_move_cnt;
            w.d = (w.d+2 ) %8;
        }

        Call_Cnt++;
    }

    void dust(int r, int c, int d)
    {
        r+=dr[d];
        c+=dc[d];
        int y = t[r][c];  //이건범위체크 할필요가 없음. 무조건 갈 수 있기 떄문
        int a = y;
        t[r][c] =0;

        //y기준 d 방향으로 두칸 떨어진 곳
        int nr=  r + 2*dr[d];
        int nc = c + 2*dc[d];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*5)/100;
        a-=(y*5)/100;

        //대각선방향
        nr=  r  + dr[(d+1) %8]; 
        nc = c  + dc[(d+1) %8];; 
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*10)/100;
        a-=(y*10)/100;


        nr =  r + dr[(d-1 +8) %8];
        nc = c + dc[(d-1 +8) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*10)/100;
        a-=(y*10)/100;


        //수직방향 두칸
        nr=  r  + dr[(d-2+8) %8] + dr[(d-2+8) %8];
        nc = c  + dc[(d-2+8) %8] + dc[(d-2+8) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*2)/100;
        a-=(y*2)/100;


        nr=  r  + dr[(d+2) %8] + dr[(d+2) %8];
        nc = c  + dc[(d+2) %8] + dc[(d+2) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*2)/100;
        a-=(y*2)/100;


        //수직방향 한칸
        nr=  r   + dr[(d-2+8) %8];
        nc = c   + dc[(d-2+8) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*7)/100;        
        a-=(y*7)/100;

        nr=  r   + dr[(d+2) %8];
        nc = c   + dc[(d+2) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*7)/100;
        a-=(y*7)/100;


        //대각 뒷쪽
        nr=  r   + dr[(d+3) %8];
        nc = c   + dc[(d+3) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*1)/100;
        a-=(y*1)/100;


        nr=  r   + dr[(d-3+8) %8];
        nc = c   + dc[(d-3+8) %8];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += (y*1)/100;
        a-=(y*1)/100;


        //앞쪽
        nr=  r   + dr[d];
        nc = c   + dc[d];
        if( !(nc >= N || nr >= N || nc <0 || nr<0) ) 
            t[nr][nc] += a;
        

    }
    int solve()
    {
        input();
        while(1){
            static int cnt;
            dust(w.r, w.c, w.d );
            move();

            // print();
            if(w.c==0 && w.r ==0) break;
        }

        for(int i=0; i< N; i++)
            for(int j=0; j< N; j++)
                init -= t[i][j];
    

    return init;
    }

    void print()
    {
        cout<<"------------------------\n";
        
        for(int i=0; i< N; i++){
            for(int j=0; j< N; j++)
                {
                    if(w.r == i && w.c ==j)
                    cout<<'x'<<" ";
                    else
                    cout<<t[i][j]<<" ";
                }

            cout<<endl;
        }

    }


};

using namespace std;

int main()
{
    shark s;
    cout<<s.solve();

    return 0;
}