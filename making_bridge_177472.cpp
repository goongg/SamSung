//7시 20분
#include <iostream>
#include <vector>
#include <queue>
#define debug 1
using namespace std;

int n, m;
vector<int> t;
vector<bool> visit;
vector<int> link;
int dx[4] ={ -1, 0, 1, 0};
int dy[4] ={  0, 1, 0, -1};

class land
{
    public:
    int num; //섬의 이름
    vector<int> eirth;
    vector<int> connected; //연결된 섬의 index를 넣음
    vector<int> b;// 다리의 갯수를 계산할때 필요
};
vector<land> l; //섬 정보를 저장

void serch_land()
{
    queue<int> q, v;
    land ll;
    int index=0;
    visit= vector<bool>(n*m);
    for(int i=0; i< n; i++)
    {    
        for(int j=0; j<m; j++)
        {
            if( t[i*m+ j] != 0 &&  !visit[i*m+ j]) //섬을 찾았으면, 이곳을 기준으로 bfs를 돌려서 섬을찾음
            {
                q.push(i*m+ j);
                visit[i*m+j]=true;
                ll.num = index++;
                ll.eirth.push_back(i*m+ j);    
                while(!q.empty())
                {
                    int ii = q.front();
                    int x=ii%m;
                    int y=ii/m;
                    q.pop();
                    for(int d=0; d<4; d++) //네방향 조사
                    {
                        if(y+dy[d]>=0 && y+dy[d]<n &&
                            x+dx[d]>=0 && x+dx[d]<m)
                            if(t[(y+dy[d])*m +x+dx[d]] !=0 
                                && !visit[(y+dy[d])*m +x+dx[d]])
                            {
                                q.push( (y+dy[d])*m +x+dx[d] );
                                visit[(y+dy[d])*m +x+dx[d] ]=1;
                                ll.eirth.push_back( (y+dy[d])*m +x+dx[d]);
                            }
                   }
                }
                //주변 섬을 다 찾았으면
                l.push_back(ll);
#if debug
                cout<<endl<<index-1 <<"'s eirth:"; 
                for(int i: ll.eirth)
                    cout<<i<<" ";
                cout<<endl;
#endif                
                ll.eirth.clear();                
            }
        }
    }
    visit.clear();
}
#define init_num 99999999 
int mmin = init_num;
int visit_land_cnt=0;
int bridge_size=0;

int connect(int cur, int ex)
{
#if debug
cout <<"\n cur:"<<l[cur].num <<" visit_land_cnt:"<<visit_land_cnt <<" bridge size:"<<bridge_size <<endl<<endl;
#endif
    for(int i=0; i< visit.size(); i++)
        visit[i]=0
    visit[cur]=1;   //자 자신이랑 지나온 곳은 미 포함
    visit[ex]=1;   //자 자신이랑 지나온 곳은 미 포함

    if(visit_land_cnt == l.size()) //모든 땅을 돌았을 때,
    {
        if(bridge_size<mmin) 
            mmin=bridge_size;
        cout<<"-----------------end!---------------------"<<endl;
        cout<<"bridge size:"<<mmin<<endl;
        return mmin;
    }

       //현재 땅에서 갈 수 있는 섬을 조사
        int x, y;
        int nx, ny;
        for(int ii : l[cur].eirth)//땅 주변 바다를 찾아
        {
            x= ii%m; y= ii/m;
            nx=x; ny=y;
            cout<<"find from"<<ii <<" "<<x<<" "<<y<<endl;
            
            vector<int> bridge;   
            for(int d=0; d<4; d++) //네방향 조사
            {                
                if(y+dy[d]>=0 && y+dy[d]<n &&
                    x+dx[d]>=0 && x+dx[d]<m &&
                        t[(y+dy[d])*m +x+dx[d]] ==0 )   //바다를 찾았을 경우,
                    {
                        bool throuing=0;
                        while(1)                        //루프를돌아 바다 건너편에 다른 땅을 찾아
                        {
                            nx+= dx[d]; ny +=dy[d];
                            if(!(nx >=0 && nx<m && ny>=0 && ny<n))  //땅을 못찾고, 범위를 넘어간 경우 break;
                            {
                                nx=x; ny=y;
                                bridge.clear();
                                break;
                            }
                            if(t[ny*m + nx]==0)                     //바다를 건너는 중이면 인덱스를 넣어
                            {
                                cout<<"throu: "<<ny*m + nx<<" "<<x<<" "<<y<<endl;
                                throuing=1;
                                bridge.push_back(ny*m + nx);
                                continue;
                            }

                            else if(t[ny*m + nx]==1 && throuing)  //섬을 찾은 겨우        //바다를 건너 땅을 찾은 경우
                            {
                                throuing=0;
                                cout<<"is visited?:" <<ny*m + ny<<endl;
                                for(land ll : l)                    //내가 찾은 땅이 몇번째 땅인지를 조사
                                {
                                    bool is_find=0;
                                    for(int iii: ll.eirth)
                                    {
                                        if(iii==ny*m+nx)
                                        {
                                            if(!visit[ll.num])      //방문한 적 없는 땅이면
                                            {
                                                cout<<"find land:"<<nx*m + ny<<" " <<ll.num<<" bridge_size:" <<bridge.size() <<endl;
                                                for(int i: bridge) cout<< i<<" ";
                                                cout<<endl;
                                                bridge_size += bridge.size();
                                                if(bridge.size()>=2)
                                                {
                                                    visit[ll.num]=1;          //이 땅을 방문처리                                                
                                                    visit_land_cnt++;
                                                    connect(ll.num);        //찾은 땅에서 다시 연결 시도
                                                    visit_land_cnt--;
                                                    bridge_size -= bridge.size();
                                                    bridge.clear();
                                                    visit[ll.num]=0;
                                                }
                                                is_find=1;
                                                break;
                                            }
                                        }
                                    }
                                    if(is_find)
                                        break;
                                }
                            }
                        }

                    }        
            }
        }

    

if(mmin!=init_num)
return mmin;
else
return -1;

}
int main()
{
    cin>>n >>m;
    t = vector<int>(n*m);
    for(int i=0; i<n; i++)
        for(int j=0; j< m; j++)
            cin>>t[i*m+j];


serch_land();

visit= vector<bool>(l.size());
link = vector<bool>(l.size());

visit[0]=1;//0번 섬은 방문함
visit_land_cnt=1;
cout<<connect(0);//0번 섬에서출발 dfs
    return 0;
}
