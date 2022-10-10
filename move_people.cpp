#include <iostream>
#include <vector>
using namespace std;

int n, L, R;
int map[51][51];

int dr[4] = {-1 ,0 ,1 ,0};
int dc[4] = {0, 1, 0, -1};

typedef pair<int, int > pii;
vector<pii > cur_union;
vector<vector<pii > > unions;

bool visit[51][51];
void dfs( pii cur)
{
    int r =cur.first;
    int c =cur.second;

    for(int d =0; d<4 ;d++)
    {
        int nr = r + dr[d];
        int nc = c + dc[d];
        if(nc <0 || nc >=n || nr <0 || nr >=n) continue;
        if(visit[nr][nc]) continue;
        int dif = abs(map[r][c] - map[nr][nc]);
        if(dif>=L && dif<=R)
        {
            visit[nr][nc]=1;
            cur_union.push_back( make_pair(nr, nc));
            dfs( make_pair(nr, nc ));
        }
    }
}
int main()
{
int cnt=0;
    cin>>n>>L>>R;

    for(int i =0; i<n; i++)
        for(int j=0; j<n; j++)
            cin>>map[i][j];
    
    while(1)
    {
        unions.resize(0);
        for(int i=0; i<n; i++)
            for(int j =0; j<n; j++)
                visit[i][j]=0;

        for(int i =0; i<n; i++)
            for(int j=0; j<n; j++)
                {
                    if(!visit[i][j]) 
                    {
                        cur_union.resize(0);
                        cur_union.push_back(make_pair(i,j));
                        visit[i][j]=1;
                        dfs(make_pair(i,j));
                        if(cur_union.size() >=2)
                            unions.push_back(cur_union);
                    }
                }
    
        if(unions.size()==0) break;
        cnt++;
        int idx=0;
        int all_people=0;
        for( vector<pii> vv: unions)
        {   
            all_people=0;
            // cout<<idx++ <<"연합" <<endl;
            for( pii pp :vv)
                all_people+=map[pp.first][pp.second];
            
            all_people/= vv.size();
            for( pii pp :vv)
                map[pp.first][pp.second]= all_people;
        } 
// cout<<endl;
        // for(int i=0; i<n; i++){
        //     for(int j =0; j<n; j++)
        //     {    
        //         cout<<map[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
            
        // cout<<cnt<<"번 이동\n"; 
    }
cout<< cnt;


    return 0;
}