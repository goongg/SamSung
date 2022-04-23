#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int dx[4] = { 0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
//상, 우, 하, 좌

#define U 0
#define R 1
#define D 2
#define L 3


#define debug 0

class ball {
    public:
        int init_p; //초기위치
        int p;  //위치 기억
        int d;  //방향 기억
        int point; //점수 기억
        bool is_first;
};
class hole
{
    public:
    int a; 
    int b;
    bool v;
};
    queue<ball> q;

class Game{

    public:

    int N;
    vector<int> t;
    hole h[11] ; //idx 6~10 만씀
    int d;  //현재 도는 핀볼의 방향을 기억
    int Max;
    ball b;

    void input()
    {
        cin>>N;
        t.resize(N*N);
        for(int i=0; i< N*N; i++)
        {
            cin>> t[i];
            if(t[i]==0) //빈곳을 기준으로 ball 추가
            {
                b.p =i;
                b.point=0;
                b.init_p= i ;
                for(int d=0; d<4; d++)
                {
                    b.d= d;
                    b.is_first=1;
                    q.push(b);
                }
            }
            if(t[i] >=6 || t[i] <=10 )
            {
                if (!h[t[i]].v)
                {
                    h[t[i]].a=i;
                    h[t[i]].v=true;
                }
                else
                    h[t[i]].b=i;
            }
        }
        Max=0;
#if debug
while(!q.empty()) q.pop();
                b.p =2*N+3;
                b.point=0;
                b.init_p=2*N+3;
                b.d= R;
                q.push(b);

cout<<" ball:" << 0 <<", "<< 0 <<endl;
cout<<" direct: down" <<endl;;

#endif


    }

    void play()  //볼을 넣고 다음 요소에 닿을때까지 진행
    {
        ball b;
        b = q.front();
        q.pop();
        int cx = b.p % N;
        int cy = b.p / N;
        int cd = b.d;
        int nx = cx;
        int ny = cy;
        int cp =  b.p;
#if debug
    cout<<"ball(" <<cy <<","<< cy<< ") start! \n";
#endif
        nx += dx[cd];
        ny += dy[cd];

        while(1) //빈곳이 아닐때까지 이동
        {
            //상, 우, 하, 좌
            // 0  1  2  3
            int next = ny*N+ nx;

            if((nx <0 || ny <0 || nx >N-1 || ny > N-1 || t[next]==5) ) // 방향 바꿈
            {
                cd = (cd +2 )%4;
                b.point++; 
                nx += dx[cd];
                ny += dy[cd];
                continue;
#if debug
    cout<<ny<<"," <<nx<<" 닿아서 반대방향으로 틈 \n";
#endif
            }
            else if( t[next] >= 1 && t[next]<=4)
            {
#if debug
    cout<<ny<<"," <<nx<<" 닿아서 방향바꿈  \n";
#endif
                b.point++;
                switch(cd)
                {
                    case U:
                        if(t[next] ==1 || t[next] ==4)  cd = (cd +2 )%4;
                        if(t[next] ==2) cd= R;
                        if(t[next] ==3) cd= L;
                    break;
                    case D:
                        if(t[next] ==2 || t[next] ==3)  cd = (cd +2 )%4;
                        if(t[next] ==1) cd= R;
                        if(t[next] ==4) cd= L;
                    break;
                    case R:
                        if(t[next] ==1 || t[next] ==2)  cd = (cd +2 )%4;
                        if(t[next] ==3) cd= D;
                        if(t[next] ==4) cd= U;
                    break;
                    case L:
                        if(t[next] ==3 || t[next] ==4)  cd = (cd +2 )%4;
                        if(t[next] ==1) cd= U;
                        if(t[next] ==2) cd= D;
                    break;
                }
                nx += dx[cd];
                ny += dy[cd];
                continue;
            }

            else if(t[next] >=6 && t[next] <=10)
            {
#if debug
    cout<<ny<<"," <<nx<<" 웜홀  \n";
#endif

                if( h[t[next]].a == next ) 
                    next =h[t[next]].b;
                else                       
                    next =h[t[next]].a;

                    ny =next/N;
                    nx =next%N;
                    ny+= dy[cd];
                    nx+= dx[cd];

#if debug
    cout<<"go to:" <<next<<'\n';
#endif
                continue;
            }

            else if(t[next] == -1 || next == b.init_p)
            {
#if debug
    cout<<ny<<"," <<nx<<" 끝남:"<<b.point << " \n";
#endif
                b.p = -1; // 빠트리고
                if (Max <=b.point ) Max= b.point ;
                break;
            }
        nx += dx[cd];
        ny += dy[cd];

            
        }

    }

    
    int solve()
    {
        input();
        do{
        play();
        }while(!q.empty());
        return Max;
    }
};

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	//freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
  vector< Game> g;
    g.resize(T);
	for(test_case = 1; test_case <= T; ++test_case)
	{
		cout<<"#"<<test_case<<" "<< g[test_case-1].solve()<<'\n';
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}