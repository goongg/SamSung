#include <iostream>
#include <vector>
#include <queue>

using namespace std;


int dr[4] = {-1, 1, 0, 0};
int dc[4] = {0, 0, -1, 1};

#define U 0
#define D 1
#define L 2
#define R 3

struct magic
{
    int d; //방향
    int s; //거리
};

class shark
{
    public:
    int N, M;
    int t[105][105];
    queue<magic> magic_q;
    queue<int> map_q;
    int sol;
    void input()
    {
        cin>>N>>M;
        for(int i=0; i< N; i++)
            for(int j=0; j< N; j++)
                cin>>t[i][j];
        
        for(int i=0; i< M; i++)
        {
            magic m;
            cin >> m.d >> m.s;
            m.d--;
            magic_q.push(m);
        }
        sol=0;
    }

    void bzd()
    {
        magic m=magic_q.front();
        magic_q.pop();
        int r = N/2;
        int c = N/2;
        for(int i=0; i< m.s; i++)
        {
            r += dr[m.d];
            c += dc[m.d];

            t[r][c] = 0;
        }
    }

    int solve()
    {
        input();
        while(!magic_q.empty())
        {
            bzd();
            MapToQ();
            while(explore());
            final();

            QToMap();   
        }
        return sol;
    };

    void MapToQ()
    {
        int r = N/2;
        int c = N/2;
        int nr;
        int nc;

        int d= 0;
        int move_cnt=1;
        int move_cnt_buf = move_cnt;
        // int dircet_cnt=1;

        int ddr[4] = { dr[L], dr[D], dr[R], dr[U] };
        int ddc[4] = { dc[L], dc[D], dc[R], dc[U] };

        int even=0;

        while(1)
        {
            move_cnt--;
            r += ddr[d];
            c +=  ddc[d];


            if(t[r][c] !=0)
                map_q.push(t[r][c]);
            
            if(move_cnt==0)
            {
                if(even++ % 2 ==1)
                    move_cnt_buf++;

                move_cnt = move_cnt_buf;
                d= (d+1)%4;
            }

            if(r==0 && c==0) break;
        }

    }

    void QToMap()
    {
        int r = N/2;
        int c = N/2;
        int nr;
        int nc;

        int d= 0;
        int move_cnt=1;
        int move_cnt_buf = move_cnt;

        int ddr[4] = { dr[L], dr[D], dr[R], dr[U] };
        int ddc[4] = { dc[L], dc[D], dc[R], dc[U] };

        int even=0;
        while(1)
        {
            move_cnt--;
            r += ddr[d];
            c +=  ddc[d];

            if(!map_q.empty())
            {
                t[r][c]= map_q.front();
                map_q.pop();
            }
            else
                t[r][c]= 0;

            if(move_cnt==0)
            {
                if(even++ % 2 ==1)
                    move_cnt_buf++;

                move_cnt = move_cnt_buf;
                d= (d+1)%4;
            }

            if(r==0 && c==0) break;
        }

        while(!map_q.empty()) map_q.pop();
    }

    bool explore()
    {
        bool result=0;

        queue<int> new_map_q;
        vector<int> cont;
        // cout<<"폭발시작\n";
        int i;

        if(!map_q.empty())
        {
            i = map_q.front();
            map_q.pop();
            cont.push_back(i);
        }
        else return 0;

        int same_cnt=1;
        while(!map_q.empty())
        {
            i = map_q.front();
            map_q.pop();

            if( i == cont.back())
                same_cnt++;    

                    
            else
            {
                if(same_cnt< 4)
                {
                    for(int ii=0; ii< same_cnt; ii++)
                        new_map_q.push(cont.back());
                    same_cnt=1;
                }
                else if(same_cnt >=4)
                {
                    sol +=  cont.back() * same_cnt;
                    cont.pop_back(); 

                    same_cnt=1;
                    result=1;
                }
                cont.clear();
                cont.push_back(i);
            }
        }
        if(same_cnt< 4)
        {
            for(int ii=0; ii< same_cnt; ii++)
                new_map_q.push(cont.back());
        }
        else if(same_cnt >=4)
        {
            sol +=  cont.back() * same_cnt;
            cont.pop_back(); 

            same_cnt=1;
            result=1;
        }
        
        map_q= new_map_q;

        return result;
    }

    void final()
    {
        queue<int> new_map_q;
        vector<int> cont;
        int i;
        int cnt=0;
        if(!map_q.empty())
        {
            i = map_q.front();
            map_q.pop();
            cont.push_back(i);
        }
        else return ;

        int same_cnt=1;        

        while(!map_q.empty())
        {
            i = map_q.front();
            map_q.pop();

            if( i == cont.back())
                same_cnt++;    

            else
            {
                new_map_q.push(same_cnt);
                new_map_q.push(cont.back());
                same_cnt=1;
                cont.clear();
                cont.push_back(i);
            }
        }
        new_map_q.push(same_cnt);
        new_map_q.push(cont.back());
        map_q = new_map_q;
    }
};


int main()
{
    shark s;
    cout<<s.solve();
    return 0;
}