//11t시 5분
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define debug 0
using namespace std;

int dx[4] ={1,0,-1, 0};
int dy[4] ={0, -1, 0,1};

int x[20];
int y[20];
int d[20];
int g[20];

static bool visit[10201];
typedef pair<int,int> p;
vector<p> answer;
int n;
class curve
{
    int g=0;
    int dest_g;//여기까지 진화해야댐
    p end_point; 
public:
    vector<p> line;

    //특정 점 d를 z를 기준으로 90도 돌리는 함수
    void init(int x, int y, int d, int dg)
    {
        line.push_back(make_pair(x, y)); //시작점을 넣어
        g=0;
        dest_g=dg; 
        end_point= make_pair(x+dx[d], y+dy[d]);
        line.push_back(end_point);
    }
    p lotate(p d, p z)
    {
        int dif_x= 0- z.first;
        int dif_y= 0- z.second;
        // 0,0으로 이동시킴
        d.first += dif_x;
        d.second += dif_y;
        int buf= d.first;
        d.first = -1*d.second;
        d.second = buf;

        d.first -= dif_x;
        d.second -= dif_y;
    return d;
    }
    //다음 세대로 진화하는 함수
    void evolution()
    {   
        //모든 점을, end point 를 기준으로 돌리고,
        //돌린점을 next_line에 넣어,
        //현재 line에 next_line을 다 넣고
        //겹친걸 제거 g를 하나 키움
        vector<p> next_line;        
        p new_end_point= lotate(line[0],end_point);
        for(p i: line) 
            next_line.push_back(lotate(i ,end_point));
        // next_line.pop_back();
        for(p i: next_line)
            line.push_back(i);
        g++;
        end_point= new_end_point;   
#if debug
    cout<<endl;
        for(p i : line)
           cout<<"g:"<<g<<" x,y:" <<i.first<<","<<i.second<<endl;
    cout<<endl;
#endif

    }
    void uni()
    {
        line.erase(unique(line.begin(), line.end()),line.end());
#if debug
    cout<<endl;
        for(p i : line)
           cout<<"uni :x,y:" <<i.first<<","<<i.second<<endl;
    cout<<endl;
#endif
    }

};



int main()
{

cin>>n;
for(int i=0; i<n; i++)
    cin >> x[i] >> y[i] >>d[i]>>g[i];
vector<p> f;
vector<curve> c(n);
for(int i=0; i<n; i++)
{    c[i].init(x[i],y[i],d[i],g[i]);
    for(int j=0; j<g[i]; j++)
        c[i].evolution();
        c[i].uni();
    for(p ii: c[i].line)
    f.push_back(ii);
}

    f.erase(unique(f.begin(), f.end()),f.end());
    // f.erase(unique(f.begin(), f.end()),f.end());

#if debug
    cout<<endl;
#endif
    int cnt=0;
    for(p i: f)
    {
#if debug
        cout <<cnt++<<":"<<i.first<<" "<<i.second<<endl;
#endif
        visit[i.second*101 +i.first ]= true;
    }
    int answer=0;
    for(int i=0; i<100; i++)
        for(int j=0; j<100; j++)
            if(visit[i*101 +j] &&  visit[(i+1)*101 +j] && 
                    visit[i*101 +j+1] &&  visit[(i+1)*101 +j+1])
                        answer++;
                

    cout<<answer;


    return 0;
}