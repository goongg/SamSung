#include<iostream>
#include<vector>
#include<queue>
using namespace std;

int map[21][21];
queue<vector<int>> q;
int T, N, X;

bool check(vector<int> v)
{
    int n = v.size();
    vector<bool> visit(n);
    for(int i=0; i<n; i++) visit[i]=0;
    int i =0 ;
    int j =0;
    while(1)
    {
        if(i>=n-1) break;

        if(i+1<n && v[i+1] == v[i]-1 ) //자기 앞에가 1 작을 때, 내 앞부터 X번 경사로 건설
        {
            for( j =i+1; j<=i+X; j++)
            {
                if(j>=n) return 0;
                if(visit[j]) return 0;
                if(v[j] != v[i]-1) return 0;
            }
            for( j =i+1; j<=i+X; j++)
                visit[j]=1;
            i= i+X;
        }
        else if (i+X <n && v[i+X] == v[i]+1) //자기 x번 앞이 1클때 나부터 x번 경사로 건설
        {
            for( j= i; j<i+X; j++)
            {
                if(j>=n) return 0;
                if(v[j]!=v[i]) return 0;
                if(visit[j]) return 0;
            }
            for( j= i; j<i+X; j++)
                visit[j]=1;

            i= i+X;
        }
        else if(i+1 <n && v[i+1] == v[i])  
            i++;
        else
            return 0;
        
    }
    return true;
}
int main(int argc, char** argv)
{
	int test_case;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int answer=0;
        cin>>N >> X;
        for(int i=0; i< N; i++){
            vector<int> v;
            for(int j =0; j<N; j++)
            {
                cin>>map[i][j];
                v.push_back(map[i][j]);
            }
            q.push(v);
        }
        for(int j=0; j<N; j++){
            vector<int> v;
            for(int i=0; i< N; i++)
                v.push_back(map[i][j]);
            q.push(v);
        }
            int tt=0;

        while(!q.empty())
        {
            if(check(q.front()))
                answer++;
            q.pop();
        }
        cout<<"#"<<test_case<<" "<<answer<<endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}