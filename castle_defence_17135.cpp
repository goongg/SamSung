//6시
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

#define debug 0

class game
{
    int n, m ,d;
    vector<int> bowman;
    vector<int> enemy;
    int end_time;
    vector<int> t;    

public:
    void input()
    {
        cin>>n >>m>> d;
        t = vector<int>(n*m);
        for(int i=0; i< n*m; i++){
            cin>>t[i];
            if(t[i]==1) {
                enemy.push_back(i);
            }
        }

        end_time =n;
        
    }

    int distance(int a, int b)
    {
        int ax = a % m;
        int ay = a / m;
        int bx = b % m;
        int by = b / m;
        return abs(ax-bx) + abs(ay-by);
    }

    int clac_score(vector<int> bow)
    {

        if(enemy.size()==0) return 0;
        vector<int> nt=t;    
        vector<int> nenemy = enemy;
        vector<int> targets;
        int score=0;
        int end= end_time;

#if debug
cout<<"\n \n enemys:";
for(int i: nenemy) cout<<i<<" ";
cout<<endl;
cout<<"boy mans:";
for(int i: bow) cout<<i<<" ";
cout<<endl;

#endif 

        while(end >0)
        {
            end--;
            //궁수 공격 턴, 새 타겟을 찾음
            if(nenemy.size()==0) break;
            targets.clear(); 

            for(int i: bow)
            {
                int target;
                int dis_min=999999999;
                int dis;
                int x_min=m+1;
                
                for(int e : nenemy) //거리가 가장 가까운 적 후보들 정리
                {
                    dis=distance(i, e); 
                    if(dis <= d && dis <=dis_min)
                        dis_min= dis;
                }
                if(dis_min != 999999999) //적을 하나라도 찾은 경우
                {
                    for(int e : nenemy) //거리가 가장 가까운 애들 중에서 가장 왼쪽에 있는애를 타겟으로 결정
                    {
                        dis=distance(i, e); 
                        if(dis == dis_min)
                            if(e % m < x_min){
                                x_min = e % m;
                                target = e;
                            }
                    }
#if debug
cout<<i<<"'s target:"<<target<<endl;;
#endif 

                    targets.push_back(target);  // 타겟을 넣음
                }
            }

#if debug
// cout<<"targets:";
// for(int i: targets) cout<<i<<" ";
// cout<<endl;
#endif 

            vector<int> nnenemy;
            for(int i: nenemy)//타겟이 된 적들을 제거
            {
                bool check=0;
                for(int j: targets){
                    if(j==i)  check = 1;      //이 적이 타겟이 된 적이 있는 적인지 조사        
                }
                if(!check) nnenemy.push_back(i+m);          //타겟이 아닌 적들의 위치를 전진시켜서 넣음
                else score++;   //타겟이 된 적 있는 적이면 스코어 ++;
            }
            nenemy.clear();
            for(int i : nnenemy)
                if( i < n*m) nenemy.push_back(i);
            
#if debug
cout<<"arrive:";
for(int i: nnenemy) cout<<i<<" ";
cout<<endl <<"score:"<<score<<endl;
#endif 

        }

        return score;
    }

    int sol()
    {
        int ret;
        int ret_max= -1;
        input();

        //궁수 위치 조합 세개 뽑음
        for(int i=0; i<m-2; i++)
            for(int j=i+1; j<m-1; j++)
                for(int k= j+1; k<m; k++)
                {
                    bowman.clear();
                    bowman.push_back(n*m+ i);
                    bowman.push_back(n*m+j);
                    bowman.push_back(n*m+k);
                    ret= clac_score(bowman);
                    if(ret_max < ret) ret_max= ret;
                }
    
        return ret_max;
    }

};

int main()
{  
game g;

cout<< g.sol();


    return 0;
}