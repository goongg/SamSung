#include <iostream>
#include <vector>

using namespace std;
// 부터 순서대로 ←, ↖, ↑, ↗, →, ↘, ↓, ↙ 
int dr[8] ={ 0, -1, -1, -1, 0, 1, 1, 1};
int dc[8] ={ -1 ,-1, 0, 1, 1, 1, 0, -1};

#define U 1
#define L 2
#define D 3
#define R 4


class Fish
{
    public:
    int r;
    int c;
    int d;
};

class Space
{
    public:
    int M, S;
    int smell[4][4];
    vector<Fish> t[4][4];
    vector<Fish> nt[4][4];

    Fish shark;

    void input()
    {
        KillCnt=0;
        cin>> M >>S;
        for(int i=0; i< M; i++)
        {
            Fish f;
            cin>>f.r>>f.c>>f.d;
            f.d--;
            f.r--;
            f.c--;
            t[f.r][f.c].push_back(f);
        }
        cin>>shark.r>>shark.c;
        shark.r--;
        shark.c--;        
        for(int i=0; i<4 ;i++)
        {
            for(int j=0; j<4; j++)
                smell[i][j]=0;
        }
    };

    void fish_move()
    {
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
            {
                for(int ff =0; ff< t[i][j].size(); ff++)
                {
                    Fish f = (t[i][j])[ff];
                    int nr = f.r;
                    int nc = f.c;
                    int nd = f.d;
                    int cnt=0;
                    do{
                        cnt++;
                        nr = f.r + dr[nd];
                        nc = f.c + dc[nd];
                        if(nc <0 || nr <0 || nc>=4 || nr >=4 || smell[nr][nc] !=0 || (nr == shark.r && nc==shark.c) )  
                        {
                            nd= (nd-1 +8)%8;
                            if(nd == f.d) 
                            {
                               nt[f.r][f.c].push_back(f);
                               break;
                            }
                            continue;
                        }     
                    f.r =nr;
                    f.c= nc;
                    f.d= nd;
                    nt[nr][nc].push_back(f);
                    break;
                    }while(1);
                }
            }
        }
    };

    void print()
    {  
        static int cnt=0;
        cout<< ++cnt<<"번쨰 이동 \n 상어위치" << shark.r+1<<" " <<shark.c+1<<endl;
        cout<<"물고기 수\n";
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
                cout<<t[i][j].size()<< " ";
            cout<<'\n';
        }
        cout<<"\n 냄새  \n";
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<4; j++)
                cout<<smell[i][j]<< " ";
            cout<<'\n';
        }
        cout<<"\n" ;
    }

    vector<vector<int> > answer;
    vector<int > answer_kill;

    vector<int> move_way;
    int KillCnt;
    int max_kill;
    bool visit[4][4];

    int shark_move() //이판에 남아있는수
    {
        KillCnt=0;
        max_kill=0;
        int result=0;

        // visit[shark.r][shark.c]=1;
        move_way.clear();
        answer_kill.clear();
        answer.clear();

        dfs();

        string min_string="444";
        for(int i=0; i< answer.size(); i++)
        {
            vector<string> answer_string;
            if( answer_kill[i] == max_kill)
            {      
                string m;
                m.clear();
                //이중에서 사전순서로 제일 빠른거 찾기
                for(int ii : answer[i]) 
                {
                    if(ii == 0) m.push_back('2');
                    if(ii == 2) m.push_back('1');
                    if(ii == 4) m.push_back('4');
                    if(ii == 6) m.push_back('3');
                }
                if(min_string >= m ) min_string= m;
            }
        }
        
        // cout<<"상어의 이동 ";
        for(char c : min_string)
        {
            int d;
            if(c == '1'){ d=2; }
            if(c == '2'){ d=0; }
            if(c == '3') {d=6; }
            if(c == '4') {d=4; }

            int nr= shark.r + dr[d];
            int nc= shark.c + dc[d];
            KillCnt+=nt[nr][nc].size();
            if(nt[nr][nc].size()!=0) smell[nr][nc]=3;  //잡아먹었다면 냄새 남김
            nt[nr][nc].clear();

            shark.r= nr; shark.c=nc;
        }
            // cout<<endl;

        for(int i=0; i< 4; i++)
            for(int j=0; j<4 ; j++)
            {
                if(smell[i][j] >0 ) smell[i][j]--;

                for(Fish f : nt[i][j])
                    t[i][j].push_back(f);
                nt[i][j].clear();

                result+= t[i][j].size();
            }

        return result;
    }


    void dfs()
    {

        if(move_way.size()==3)
        {
            if( KillCnt >= max_kill)
                max_kill = KillCnt;

            answer_kill.push_back(KillCnt);
            answer.push_back(move_way);

            return;
        }


        int r= shark.r;
        int c = shark.c;
        for(int d=0; d<=6; d+=2) //네방향조사 
        {

            int nr= r + dr[d];
            int nc= c + dc[d];
            if(nc <0 || nr <0 || nc>=4 || nr >=4 )  continue;
            
            //임시저장
            vector<Fish> buf = nt[nr][nc];
            int buf_kill = KillCnt;
            int buf_smell = smell[nr][nc];

            KillCnt += nt[nr][nc].size();   //잡아먹은거 증가
            move_way.push_back(d);  //이동 자취 남김
            nt[nr][nc].clear();     //먹었으니 없어지고
            shark.r= nr; shark.c=nc;

            dfs();

            KillCnt = buf_kill;
            nt[nr][nc]= buf;
            move_way.pop_back();
            shark.r= r; shark.c=c;
            visit[nr][nc] =0;
        }₩

    };


    int solve()
    {
        input();
        int result=0;
        while(S-- >0)
        {
            fish_move();    
            result= shark_move();
        }
        return result;
    }
};


int main()
{
    Space s;
    cout<< s.solve();
    return 0;
}