#include<iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> pii;

int N;
vector<pii> people;
vector<pii> stair;
vector<int> length; //계단의 길이
vector<vector<int> > simul;
vector<int> cur;
int answer=99999999;
int dist(pii a, pii b)
{
    int ret=0;
    ret += a.first - b.first;
    if(ret<0) ret*=-1;
    
    if(a.second - b.second <0) ret +=( b.second - a.second);
    else ret+= a.second- b.second;

    return ret;
}

void dfs(int n, int depth)//n개 로 0, 1 순열 만들기
{    
    if(cur.size()==n)
    {
        simul.push_back(cur);
        return;
    }

    cur.push_back(0); //0을 고르는 경우;
    dfs(n, depth+1);
    cur.pop_back();

    cur.push_back(1); //1을 고르는 경우
    dfs(n,depth+1);
    cur.pop_back();

}

int go(vector<int> sim)
{
    int time=0;
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    for(int i =0 ;i<people.size(); i++)
    {
        int d= dist( people[i], stair[sim[i]]);
        pq.push( make_pair(d, i));
    }
    
    int on[2]={0,0}; //계단위에 있는 사람 수
    vector<int> in_stair[2]; //건너는 사람의 내려간 계단수
    int in[2]={0,0}; //내려가는 중인 사람 수
    while(1)
    {
        time++;
        for(int i =0; i<2; i++)
        {
            for(int j =0 ;j< in_stair[i].size(); j++)
            {    
                in_stair[i][j]++;
                if(in_stair[i][j]==length[i]) 
                    in[i]--;
            }
            for(int iii =0; iii<3; iii++)
                if(in[i] <3 &&  on[i]>0)
                {
                    on[i]--;
                    in[i]++;
                    in_stair[i].push_back(0);
                }
        }

        if(pq.empty() && on[0]==0 && in[0]==0 && on[1]==0 && in[1]==0) break;
        if(pq.empty()) continue;

        while(!pq.empty()&& pq.top().first -time <=0 ) // 이 시간에 빠져나올수 있는 사람
        {
            int i = pq.top().second;
            pq.pop();
            on[sim[i]]++;
        }

    }
return time;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin>>N;
        people.resize(0);
        length.resize(0);
        stair.resize(0);
        for(int i =0; i<N;i++)
        {
            for (int j =0; j<N; j++)
            {
                int a;
                cin>>a;
                if(a==1)
                    people.push_back(make_pair(i,j));
                else if(a>=2 && a<=10) 
                {
                    stair.push_back(make_pair(i,j));
                    length.push_back(a);
                }
            }
        }
        cur.resize(0);
        simul.resize(0);

        dfs((int)people.size(),0);
        answer=9999999;
        for(vector<int> v : simul){
            int ret = go(v);
            answer = min(ret, answer);
        }
        cout<<"#"<<test_case<<" "<<answer<<endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}