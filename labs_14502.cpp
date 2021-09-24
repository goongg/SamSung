#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define debug 0


int dx[4] ={1, 0, -1, 0};
int dy[4] ={0, -1, 0, 1};

typedef pair<int, int> p;

class lab{
    int n, m;
    queue<p> v;
    vector<int> t;


    public:
    void input()
    {
        cin>>n>>m;
        t= vector<int>(n*m);
        for(int i=0; i< n; i++) 
            for(int j=0; j<m; j++)
                {
                    cin>> t[i*m+j];
                    if(t[i*m+j] ==2) 
                        v.push( make_pair(i,j));
                    
                }
    }
    
    int sol()
    {
        // 0 ~ n*m-1 중 3개를 뽑으면 됨, 순서 상관x
        input();
        int max = -1;
        int ret;
        for(int i=0; i<n*m-2; i++)
            for(int j=i+1; j<n*m-1; j++)
                for(int k=j+1; k<n*m; k++)
                    if(t[i] == 0 && t[j] == 0 &&  t[k] == 0)    //세개 다 빈칸인 경우에 벽세우고 퍼트리기
                    {  
                        t[i]=1; t[j]=1; t[k]=1;
                        ret= spread();
                        if(max < ret) max= ret;
                        t[i]=0; t[j]=0; t[k]=0;
                    }
        return max;
    }

    int spread() //퍼짐, 안전영역 계산
    {
        vector<int> nt =t;
        queue<p> w=v;
        int ret=0;
        p cr;
        
        while(!w.empty())
        {
            cr = w.front();
            w.pop();
            for(int i=0; i<4 ; i++) //4방향 조사
            {
                if( cr.first+dy[i] >=0 && cr.first+dy[i] <n &&
                        cr.second +dx[i]>=0 && cr.second+dx[i] <m &&
                            nt[ (cr.first+dy[i])*m + cr.second+dx[i] ]==0 )  //범위안이고 0이면 가지치기
                        {
                            w.push(make_pair(cr.first+dy[i], cr.second+dx[i] ));
                            nt[ (cr.first+dy[i])*m + cr.second+dx[i] ]=2;       //방문 처리
                        }
            }
        }
        for(int i=0; i<n*m; i++) if(nt[i]==0) ret++;    //안전영역만큼 ++

#if debug
cout<<endl;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++)
                cout<<nt[i*m+j]<<" ";
        cout<<endl;
        }
cout<<endl;       
#endif

        return ret;
    }


};


int main()
{
lab l;
cout<< l.sol();

}