#include <iostream>
#include <vector>

using namespace std;


int dr[4] ={ -1, 0, 1, 0};
int dc[4] ={ 0, 1, 0, -1};

#define U 0
#define R 1
#define D 2
#define L 3

class _pos{
    public:
    int r;
    int c;
};

class Processor
{
public:
    int N;
    int t[12][12];
    bool visit[12][12];
    
    vector<_pos> cores;
    vector<bool> connected;
    void input()
    {
        cin>>N;
        cores.clear();
        connected.clear();
 
        for(int i=0; i<N; i++) 
            for(int j=0; j<N; j++)
            {
                cin>>t[i][j];
                visit[i][j]=0;
                if(t[i][j] !=0){
                    _pos core;
                    core.r=i; core.c=j;
                    cores.push_back(core);
                    visit[i][j]=1;
                    
                    if(i==0 || j==0 || i==N-1 || j==N-1) 
                        connected.push_back(1);
                    else
                        connected.push_back(0);
                }
            }
    }
    //이방향으로연결가능한지정의
    bool check(int idx, int d)
    {
        _pos next= cores[idx];
        while(1)
        {
            next.r += dr[d];
            next.c += dc[d];

            if(next.r<0 || next.c <0 || next.r >=N|| next.c>=N)
                return 1;
            
            if(visit[next.r][next.c] ==1)
                return 0;
        }
    }

    int connect(int idx, int d)
    {
        int result=0;
        _pos next = cores[idx];
        while(1)
        {
            next.r += dr[d];
            next.c += dc[d];

            if(next.r<0 || next.c <0 || next.r >=N|| next.c>=N)
                return result;

            visit[next.r][next.c ] = !visit[next.r][next.c];
            result++;
        }

        
    }

    vector<int> answer_length;
    vector<int> answer_connected;
    int max_answer_connected;
    int min_answer_length;
    void print()
    {
        cout<<"\nprint\n";
        for(int i=0; i<N; i++) 
        {
            for(int j=0; j<N; j++)
                cout<<visit[i][j]<<" ";
            cout<<endl;
        }   
        cout<<"end print\n";

    }
    int solve()
    {
        input();
        // cout<<cores.size();
        answer_length.clear();
        answer_connected.clear();
        min_answer_length = 99999999;
        max_answer_connected=-1;
        dfs(0, 0);

        for(int i=0; i< answer_connected.size(); i++)
        {
            if(answer_connected[i] == max_answer_connected)
            {
                if(min_answer_length > answer_length[i]) 
                 min_answer_length= answer_length[i];
            }
        }

        return min_answer_length;
    }

    void dfs(int core_idx, int length)
    {
        int cur_length;
        if(core_idx == cores.size())
        {
            int con=0;
            answer_length.push_back(length);

            for(int i=0; i< connected.size(); i++)
                if(connected[i]==1) con++;

            answer_connected.push_back( con);

            if(max_answer_connected < con)
                max_answer_connected= con;
            
            return;
        }

        // cout<<core_idx<<"연결체크! 현재 길이:" <<length;
        // print();


        if(connected[core_idx]) 
        {
            // cout<<"core" <<core_idx<<"is already coneeceted\n\n\n";
            dfs(core_idx+1, length);
        
            return;
        }

        for(int i=0; i<5; i++)
        {   
            if(i==4)
                dfs(core_idx+1, length);
            else
            {    
                if(check(core_idx, i))  //이을수 있으면
                {
                    int plus_length = connect(core_idx, i); //그방향으로 잇고
                    connected[core_idx] =1;    //이 코어가 연결됐음을 기록.
                    // print();
                    // cout<<i<<"방향으로 연결! 추가길이: "<<plus_length <<endl<<endl;
                    

                    dfs(core_idx+1, length+plus_length);
                    connected[core_idx] =0;    //초기화
                    connect(core_idx, i);
                }
            }
        }

    };
};

int main()
{
    Processor p;
    cout<< p.solve();
    return 0;
}