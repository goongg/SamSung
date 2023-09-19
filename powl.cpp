#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<vector<int> > t;
int init=0;
int stacked;
int high;
int answer=0;
int dx[4] ={ -1 , 0 , 1, 0};
int dy[4] ={ 0 , 1, 0 , -1};

int nt[1000][1000];

void print()
{
    cout<<"\n---------------------------\n";
    // cout<<<<stacked-init+1<<" " <<high<<endl;    
    for(int i=high-1; i>0; i--)
    {
        for(int j =init; j<= stacked; j++)
            cout<< t[j][i] <<" ";
        cout<<endl;
    }
    // cout<<end
    for(int j=init; j<t.size(); j++)
        cout<<t[j][0]<<" ";

    cout<<"\n---------------------------\n";
    cout<<endl<<endl;
}
int main()
{
    cin>>n>>k;
    t.resize(n);
    for(int i=0; i< n; i++) 
    {
        int f;
        cin>>f;
        t[i].push_back(f);
    }



    while(1)
    {

        /* 1. 물고기 1개씩 넣기*/
        int minf=10000000;
        int maxf=-1;

        for(int i=init; i<t.size();i++)
        {
            minf = min( minf, t[i][0]);
            maxf = max( maxf, t[i][0]);
        }

        if(maxf - minf <=k) 
        {
            cout<<answer;
            return 0;
        }

        for(int i=init; i<t.size();i++)
            if(minf == t[i][0] ) t[i][0]++;
    
        init=0; high=1;
    
        t[init+1].push_back(t[init++][0]); // 가장끝에있는걸 그다음에 올림
    
        while(1){
            for(int i =init; i<t.size(); i++)  //두개 이상 쌓인 곳 조사
                if(t[i].size()>=2) 
                {
                    stacked=i;
                    high=t[i].size();
                }
                
            // print();
            if(high > t.size()-(stacked+1)) break;
        
            for(int i = 0 ; i< high ; i++)
            {
                for(int j= 0; j<stacked-init+1 ; j++)
                    t[i+stacked+1].push_back( t[stacked-j][i]);
            }
            init= stacked+1;
        }

        for(int x = init ; x< t.size(); x++)
        {
            for(int y  =0; y <high; y++)
            {
                // cout<<x-init<<" "<<y<<"좌표 dif:";
                for(int d=0; d<4; d++)
                {
                    int nx = x+ dx[d];
                    int ny = y+ dy[d];
                    if(nx < init || nx >=t.size() || ny<0 || ny>= t[nx].size()) continue;
                    int dif = (t[x][y]-t[nx][ny])/5;
                    nt[x][y] -= dif;
                }
            }
        }   
        for(int x = init ; x< t.size(); x++)
        {
            for(int y  =0; y <t[x].size(); y++)
            {
                t[x][y] +=   nt[x][y];
                nt[x][y]=0;
            }
        }         

        // print();

        int buf = t.size();
        for(int x = init ; x< buf; x++)
        {
            for(int y  =0; y <t[x].size(); y++)
            {
                vector<int> v(1);
                v[0]= t[x][y];
                t.push_back(v);
            } 
        }   
        init = buf;

        for(int i = 0 ; i<n/2; i++)
            t[t.size()-1 -i].push_back(t[init+i][0]);

        init += n/2;

        for(int i = 0 ; i<n/4; i++)
            for(int j=0; j<2; j++)
                t[t.size()-1 -i].push_back(t[init+i][1-j]);

        init += n/4;
        for(int i =init; i<t.size(); i++)  //두개 이상 쌓인 곳 조사
            if(t[i].size()>=2) 
            {
                stacked=i;
                high=t[i].size();
            }
        // print( );

        //물고기조절작업
  
        for(int x = init ; x< t.size(); x++)
        {
            for(int y  =0; y <high; y++)
            {
               for(int d=0; d<4; d++)
                {
                    int nx = x+ dx[d];
                    int ny = y+ dy[d];
                    if(nx < init || nx >=t.size() || ny<0 || ny>= t[nx].size()) continue;
                    int dif = (t[x][y]-t[nx][ny])/5;
                    nt[x][y] -= dif;
                }
            }
        }   
        for(int x = init ; x< t.size(); x++)
        {
            for(int y  =0; y <t[x].size(); y++)
            {
                t[x][y] +=   nt[x][y];
                nt[x][y]=0;
            }
        }   
        // print();

        buf = t.size();

        vector<vector<int> > next;
        for(int x = init ; x< buf; x++)
        {
            for(int y  =0; y <t[x].size(); y++)
            {
                vector<int> v(1);
                v[0]= t[x][y];
                next.push_back(v);
            } 
        }   
        t= next;
        init=0;
        high=1;
        stacked=0;
        // print();

    answer++;
    }

    return 0;
}