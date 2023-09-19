#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;

typedef pair<int, int> pii;

vector<vector<int> > v;
vector<vector<int> > n_v;

int R, C, K;

void print( vector<vector<int> > v)
{
    cout<<endl;
    for(int i =0 ; i< v.size(); i++)
    {
        for(int j =0 ;j< v[i].size(); j++)
            cout<<v[i][j]<<" ";
        cout<<endl;
    }
}

vector<vector<int> > operR(vector<vector<int> > v)
{
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    vector<vector<int> >  nv;
    bool visit[101];
    int cnt[101];
    int max_length=0;
    for(int i =0 ; i< v.size(); i++)
    {
        int length=0;
        for(int i =0; i< 101; i++)
        {
            visit[i]=0;
            cnt[i]=0;
        }

        for(int j =0; j<v[i].size(); j++)  
            cnt[v[i][j]]++; //등장횟수를 기억
        

        for(int j =0; j<v[i].size(); j++)
        {
            if(!visit[v[i][j]] && v[i][j]!=0)
            {
                visit[v[i][j]]=1;
                pq.push(make_pair( cnt[v[i][j]] , v[i][j]));
                length+=2;
            }
        }

        max_length= max(length, max_length);
        vector<int> vv;

        while(!pq.empty()) 
        {
            vv.push_back(pq.top().second);
            vv.push_back(pq.top().first);
            pq.pop();
        }
        nv.push_back(vv);

    }

    for(int i =0; i< v.size(); i++)
    {
        while(nv[i].size() < max_length) nv[i].push_back(0);
    }

    return nv;
}

vector<vector<int> > operC(vector<vector<int> > v)
{
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    vector<vector<int> >  nv;
    bool visit[1000];
    int cnt[1000];
    int max_length=0;
    for(int j =0 ; j< v[0].size(); j++)
    {
        int length=0;
        for(int i =0; i< 1000; i++)
        {
            visit[i]=0;
            cnt[i]=0;
        }

        for(int i =0; i<v.size(); i++)  
            cnt[v[i][j]]++; //등장횟수를 기억
        

        for(int i =0; i<v.size(); i++)
        {
            if(!visit[v[i][j]] && v[i][j]!=0)
            {
                visit[v[i][j]]=1;
                pq.push(make_pair( cnt[v[i][j]] , v[i][j]));
            }
        }

        vector<int> vv;

        while(!pq.empty()) 
        {
            vv.push_back(pq.top().second);
            vv.push_back(pq.top().first);
            // cout<<pq.top().second<<" "<<pq.top().first<<" ";
            length+=2;
            pq.pop();
        }
        // cout<<endl;
        max_length= max(length, max_length);
        nv.push_back(vv);
    }

    for(int i =0; i< nv.size(); i++)
    {
        while(nv[i].size() < max_length) nv[i].push_back(0);
    }

    vector<vector<int> > nnv;
    nnv.resize(nv[0].size());
    vector<int> vv;
    for(int i =0 ; i< nv[0].size(); i++)
    {
        for(int j=0 ; j< nv.size(); j++)
        {
            nnv[i].push_back( nv[j][i]);
        }
    }

    return nnv;
}
int main()
{
    cin>> R >> C >>K;
    R--;
    C--;
    for(int i =0 ;i<3; i++)
    {
        vector<int> vv;
        for(int j=0; j<3; j++)
        {
            int a;
            cin >>a;
            vv.push_back(a);
        }
        v.push_back(vv);
    }
    int cnt=0;
    while(cnt<=100)
    {

        vector<vector<int> > nv;
        if(v.size() > R && v[R].size()>C && v[R][C] ==K)
            break;

        if(v.size() >= v[0].size())
            v=operR(v);
        else
            v=operC(v);


        if(v.size()>100)
        while( v.size() >100) v.pop_back();

        if(v[0].size()>100)
            for(int i =0 ; i< v.size(); i++)
                while(v[i].size()>100) v[i].pop_back();
        
        

        cnt++;

        // print(v);
    }

    if(cnt==101) cout<<-1;
    else cout<<cnt;

    
    return 0;
}