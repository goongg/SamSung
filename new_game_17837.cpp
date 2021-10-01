//6시
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define white 0
#define red 1
#define blue 2
#define debug 0

int dx[4]={1,  -1, 0, 0};    //오 왼 위 아래
int dy[4]={0 ,0, -1, 1};

class horse{
    public:
    int y, x; //위치
    int num; //말의 숫자
    int d; //방향
    int n; //내칸에서 내가 몇번쨰인지
};
typedef vector<horse> hh;

class game{
    int n, k;
    vector<int> t;  //보드 칸 색깔 저장
    vector<hh> ht;  //보드 칸에 쌓여있는 말
    vector<horse> h;  // 전체 말 목록
    int turn=0;
    bool end=0;
    public:
    void input()
    {
        cin>>n>>k;
        t = vector<int>(n*n);
        ht = vector<hh>(n*n);
        h = vector<horse>(k);
        for(int i=0; i<n*n; i++) cin>> t[i];
        for(int i=0; i<k; i++) {
            cin>> h[i].y >> h[i].x >> h[i].d;
            h[i].y--;
            h[i].x--;
            h[i].d--; //범위 재 지정 (0 부터 시작)
            h[i].num=i;
            h[i].n= 0;
        }

        for(horse i: h)
            ht[ i.y*n + i.x].push_back(i);
    }

    void move()
    {
        turn++;

#if debug
cout<<"\n turn:"<<turn<<"------------\n";
    cout<<"\n befor move\n";
    {
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cout<<ht[i*n+j].size()<<" ";
            }
                cout<<"\n";
        }
    }

    cout<<"\n top horse \n";
    {
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
               if(ht[i*n+j].size() !=0) 
                cout<<ht[i*n+j].back().num +1<<" ";
                else
                cout<<0<<" ";
            }
                cout<<"\n";
        }
    }

#endif
        vector<horse> nh;  // 전체 말 목록
        nh = h;
        for(int i=0; i<h.size(); i++) //말들을 하나씩 옮김
        {
            int my_num;
            int color;
            int x = h[i].x; //옮기려는 말의 위치
            int y = h[i].y; //옮기려는 말의 우치
            int d = h[i].d;
            int num= ht[y*n +x].size(); //움직이려는 칸위에 있는 말의 갯수

            //어디로 옮길지, 옮기는 규칙을 정함
            int nx = x+ dx[d];
            int ny = y+ dy[d];
            
            if( t[ny*n+nx] == blue || (nx <0) || (nx >= n) || (ny <0) || (ny >=n) ) //옮길수 없거나 파랑
            {
                color =blue;
                nx -= 2*dx[d];
                ny -= 2*dy[d];// 방향을 바꿈
                if( d == 0)      d++;
                else if( d == 1) d--;
                else if( d == 2) d++;
                else if( d == 3) d--;
                ht[y*n+ x][h[i].n].d =d;

                if( t[ny*n+nx] == blue || (nx <0) || (nx >= n) || (ny <0) || (ny >=n) ) //한번 더 조사 
                    color = -1;
                //가만히 
                else
                    color = t[ny*n+nx];
            }
            else{
                color= t[ny*n+nx] ;
            }
            
#if debug
    cout<<"\n move color : "<<color<<endl;
#endif
            
            
            int erase_cnt=0;
                
            if(color == -1)
            {
                continue;
            } //아무것도 안함
            else if(color==white)   //순서대로 이동
            {
                // cout<<"with: ";
                int buf = h[i].n;
                for(int j= buf ; j< num; j++) // 이칸의 나를 포함 나보다 위에있는 말을 내 규칙대로 옮김
                {
                    // cout<< ht[y*n+ x][j].num<<" ";
                    ht[y*n+ x][j].x = nx;
                    ht[y*n+ x][j].y = ny;
                    // ht[y*n+ x][j].d = d;
                    ht[y*n+ x][j].n= ht[ny*n +nx ].size();
                    ht[ny*n +nx ].push_back(ht[y*n+ x][j]);
                    
                    h[ht[ny*n +nx ].back().num] = ht[ny*n +nx ].back();
                    erase_cnt++;
                }
                // cout<<endl;
            }
            
            else if(color==red)   //반대로
            {
                // cout<<"with: ";
                int buf = h[i].n;
                for(int j= num-1  ; j>= buf; j--) // 이칸의 나를 포함 나보다 위에있는 말을 내 규칙대로 옮김
                {
                    // cout<< ht[y*n+ x][j].num<<" ";
                    ht[y*n+ x][j].x = nx;
                    ht[y*n+ x][j].y = ny;
                    // ht[y*n+ x][j].d = d;
                    ht[y*n+ x][j].n= ht[ny*n +nx ].size();
                    ht[ny*n +nx ].push_back(ht[y*n+ x][j]);
                    
                    h[ht[ny*n +nx ].back().num] = ht[ny*n +nx ].back();
                    erase_cnt++;
                }

            }
            for(int j=0; j< erase_cnt; j++) ht[y*n+x].pop_back();
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (ht[i*n+j].size() >=4) 
            {
                end =1;
                return;
            }
        }
    }   


           #if debug
    cout<<"\n after move\n";
    {
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cout<<ht[i*n+j].size()<<" ";
            }
                cout<<"\n";
        }
    }
    cout<<"\n top horse \n";
    {
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
               if(ht[i*n+j].size() !=0) 
                cout<<ht[i*n+j].back().num +1<<" ";
                else
                cout<<0<<" ";
            }
                cout<<"\n";
        }
    }

#endif

        }


    }

    int sol()
    {
        int max=0;
        input();
        while(turn < 1000)
        {
            move();
                if(end) break;

            for(int i=0; i<n*n; i++) if( max < ht[i].size() ) max = ht[i].size(); 
            if(max == k) break;
        }
        if(turn != 1000)
            return turn;
        else
            return -1;
    }

};

int main()
{
    game g;
    cout<<g.sol();

    return 0;
}