#include<iostream>
#include <vector>
#include <map>
using namespace std;


typedef pair<int,int> pii;
int N, M;
map <pii, int> visit;
int city[21][21];

int all_people=0;
vector<vector<pii> > zone; //서비스 지역을 모음
int dr[4]={-1, 0, 1, 0};
int dc[4]={0, 1, 0, -1};

vector<pii> next_k(vector<pii> ex) // 서비스 지역 세팅
{
    vector<pii> next;
    next = ex;

    for(pii p: ex)
    {
        int r = p.first;
        int c = p.second;
        for(int d=0; d<4 ; d++)
        {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if(visit[make_pair(nr,nc)] != 1)
            {
                visit[make_pair(nr,nc)]=1;
                next.push_back(make_pair(nr,nc));
            }
        }
    }
    return next;
}

int check(int r, int c, int k)
{
int ret=0;
    for(pii p : zone[k])
    {
        int nr = r + p.first;
        int nc = c + p.second;

        if(nr>=N || nr <0 || nc <0 || nc >=N) continue;
        if(city[nr][nc] == 1) ret++;
    }

    return ret;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
    int answer=1;
	cin>>T;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin>>N>>M;
        all_people=0;
        zone.resize(0);
        visit.clear();
        for(int i =0 ; i<N ; i++)
            for(int j =0 ; j<N ; j++)
            {
                cin>>city[i][j];
                if(city[i][j]==1) all_people++;
            }
        answer=1;
        zone.resize(N+2);
        zone[1].push_back(make_pair(0, 0));
        visit[make_pair(0, 0)]=1;
        for(int i =1 ; i<=N; i++)
            zone[i+1]= next_k(zone[i]);            
        
        // for(pii p : zone[8])
        //     cout<< p.first<<" "<<p.second<<endl;

        for(int i =0; i < N; i++)
        {
            for(int j=0; j<N; j++)
            {
                for(int k=2 ; k<=N; k++)
                {
                    int people = check(i,j, k);
                    if(people < answer) continue;

                    int remain_people = all_people-people;

                    int fee = people*M; //사람이 지불한 돈
                    int oper_fee = k*k + (k-1)*(k-1); //운영비용



                    if(oper_fee <= fee)
                    {
                        cout<<i<<" "<<j<<" k:" <<k<<" 사람:" << people<< " " <<  fee - oper_fee  << endl;
                        answer = max (answer, people);
                    }
                    int next_operfee= (k+1)*(k+1) + k*k;

                    if( next_operfee - oper_fee  > remain_people*M) //다음에 추가 되는 운영비용이 남은칸의 요금 다받는것보다 크면 끝
                        break;
                }
            }
        }

        cout<<"#" <<test_case <<" " <<answer<<endl;
	}

	return 0;
}