#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> pii;

#define U 1
#define D 2
#define L 3
#define R 4

int dr[5]={0, -1, 1, 0, 0};
int dc[5]={0, 0, 0, -1, 1};


class shark
{
    public:
    int index;
    int d; // 현재 방향
    int prio[5][4]; //우선 순위
    pii p; //위치
    bool dead;
};

int n, m, k; //격자, 상어수, k냄새 머물
int cur_shark;
pii smell[24][24];
vector<int> map[24][24];
vector<int> nmap[24][24];

void print()
{
    cout<<"\n냄새\n";
    for(int i =0; i<n; i++)
    {
        for(int j =0; j<n; j++)
            cout<<smell[i][j].first<<" ";
                cout<<endl;
    }
    cout<<"\n냄새주인\n";
    for(int i =0; i<n; i++)
    {
        for(int j =0; j<n; j++)
            cout<<smell[i][j].second<<" ";
                cout<<endl;
    }

    cout<<"\n상어위치\n";
    for(int i =0; i<n; i++)
    {
        for(int j =0; j<n; j++)
        {
            cout<<map[i][j].size()<<" ";
        }
        cout<<endl;
    }
}

int main()
{  
    cin>>n>>m>>k;
    cur_shark= m;
    vector<shark> sharks(m+1);
    for(int i =0; i<n; i++)
    {
        for(int j =0; j<n; j++)
        {
            int ii;
            cin>>ii;
            shark s;
            if(ii !=0)
            {
                s.index=ii;
                s.dead=0;
                s.p= make_pair(i,j);   
                map[i][j].push_back(ii);        
                sharks[ii]=s;     
            }
        }
    }
    for(int i =1; i<= m; i++)
        cin>>sharks[i].d;

    for(int i =1; i<= m; i++)
    {
        for(int d = U ; d<= R ; d++)
        {
            for(int p=0; p<4 ; p++)
                cin>>sharks[i].prio[d][p];    
        }
    }

    int cnt=0;
    while(1)
    {
    
    for(int i =0; i<n ; i++)
    for(int j =0; j<n; j++)
        nmap[i][j].resize(0);
    
    //냄새 뿌리기
    for(int i =1; i<= m; i++)
        if(!sharks[i].dead)
            smell[sharks[i].p.first][sharks[i].p.second]= make_pair(k, i);
    
    //이동
    for(int i =0; i<n; i++)
    {
        for(int j =0; j<n ; j++)
        {
            if(map[i][j].size()==0) continue;
            for(int s_idx: map[i][j])
            {
                bool cant=1;
                shark s = sharks[s_idx];

                for(int dd=0; dd<4 ;dd++)
                {
                    int index = s.index;
                    int d = s.d;
                    int nd = s.prio[d][dd];
                    int nr = s.p.first + dr[nd];
                    int nc = s.p.second + dc[nd];
                    if(nr <0 || nc <0 || nr>=n || nc >=n) continue; //격자 벗어남
                    if(smell[nr][nc].first !=0) continue; //누군가의 냄새가 있음.
                    s.d=nd;
                    s.p = make_pair(nr,nc);

                    nmap[nr][nc].push_back(index);     
                    sharks[s_idx] = s;        
                    cant=0;
                    break;
                }
                if(cant)// 냄새가 없는 칸이 없으면
                {
                    for(int dd=0; dd<4 ;dd++)
                    {
                        int index = s.index;
                        int d = s.d;
                        int nd = s.prio[d][dd];
                        int nr = s.p.first +dr[nd];
                        int nc = s.p.second + dc[nd];
                        if(nr <0 || nc <0 || nr>=n || nc >=n) continue; //격자 벗어남
                        if(smell[nr][nc].second !=index) continue; //누군가의 냄새가 있음.
                        s.d=nd;
                        s.p = make_pair(nr,nc);

                        nmap[nr][nc].push_back(index);             
                        sharks[s_idx] = s;        
                        cant=0;
                        break;
                    }                    
                }
                // cout<<"("<<s.p.first <<","<<s.p.second<<")\n";
            }            
        }
    }
    for(int i =0; i<n; i++)
    {
        for(int j =0;j<n; j++) 
        {            
            map[i][j] =nmap[i][j];
            int min_idx=1000000;
            for(int idx : map[i][j])
                min_idx= min(min_idx,idx);

            for(int idx : map[i][j])
            {
                if(min_idx != idx && !sharks[idx].dead)
                {
                    sharks[idx].dead=1;
                    cur_shark--;
                }
                else if(min_idx == idx)
                {
                    smell[i][j]= make_pair( k+1 , min_idx);
                }
            }
            if(min_idx != 1000000)
            {
                map[i][j].resize(0);
                map[i][j].push_back(min_idx);
            }
        }
    }

    for(int i=0; i< n ; i++)
    {
        for(int j =0 ; j<n; j++)
        {
            if(smell[i][j].first >0) 
                smell[i][j].first--;
            if(smell[i][j].first ==0)
               smell[i][j].second=0; 

        }
    }
        // print();
        if(cur_shark==1) break;
        if(++cnt >=1000) break;
    }

    if(cnt != 1000)
    cout<<cnt+1;
    else
    cout<<-1;
    return 0;
}