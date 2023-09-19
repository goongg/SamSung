#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int T, D, W, K;
bool v[14][21];

class file
{
    public:
    bool visit0[14]; // 방문기록
    bool visit1[14];

    bool vv[14][21]; //필름 상태
    int depth; //

    int ex;
};

bool check(bool vv[14][21])
{
    for(int j=0; j<W; j++)
    {   
        int cnt=0;
        bool ex;
        for(int i=0; i<D; i++)
        {
            if(i==0) 
            {
                ex= vv[i][j];
                cnt=1;
                continue;
            }

            if(ex== vv[i][j])
                cnt++;
            else
                cnt=1;

            ex= vv[i][j];

            if(cnt>=K) break;

            if(D -(i+1) < K- cnt ) return 0;
        }
        if(cnt<K) return 0;
    }

    return 1;
}

int bfs()
{
    int ret=0;
    queue<file> q;
    
    file u;
    u.depth=0; 
    for(int i =0 ; i< D; i++)
    {
        for(int j =0 ; j<W ; j++)
        {
            u.vv[i][j] = v[i][j];
        }
    }
    u.ex=-1;
    
    if(K==1) return 0;
    for(int i =0; i< D; i++) 
        u.visit0[i] = u.visit1[i]=0;    
    
    q.push(u);

    while(!q.empty())
    {
        u = q.front(); 
        q.pop();

        if(check(u.vv)) 
            return u.depth;

        if(u.depth>=K) return K;

        for(int i=u.ex+1; i<D; i++)
        {
            file v = u;
            if(!v.visit0[i]) 
            {
                for(int j=0; j<W; j++)
                    v.vv[i][j]=0;
                v.depth++;
                v.visit0[i]=1;
                v.ex =i;
                if(v.depth<=K)
                    q.push(v);
                v.depth--;
            }
            
            if(!v.visit1[i])
            {
                for(int j=0; j<W; j++)
                    v.vv[i][j]=1;
                v.depth++;
                v.visit1[i]=1;
                v.ex =i;    
                if(v.depth<=K)
                    q.push(v);
                v.depth--;
            }
        }
    }

    return 0;
}


int main(int argc, char** argv)
{
	int test_case;
    vector<int> ret;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin>>D>>W>>K;
        // v.resize(D);        
        for(int i =0 ; i<D; i++)
        {
            // v[i].resize(W);
            for(int j=0; j<W; j++)
            {
                int a;
               cin>>a;
               v[i][j]=a;
            }
        }   

        cout<<"#"<<test_case<<" "<<bfs()<<endl;
	}


	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}