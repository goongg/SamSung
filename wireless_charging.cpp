#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

typedef struct _pos{int x; int y;} pos;

class bc {
    public:
        pos p; //중심 위치
        int C; //범위
        int P; //성능
};
class man{
    public:
        pos p;
        vector<int> area;
};

// 정지, 상, 우, 하, 좌
int dx[5] ={0, 0, 1 ,0, -1};
int dy[5] ={0, -1 ,0, 1, 0};

class WirelessCharging
{
    public:
        int M; //시간
        int A; //bc의 갯수
        vector<bc> bcs; 
        vector<int> direct[2];
        int time;
        man m[2];

        int chargepoint;

        void input()
        {
            cin>>M>>A;
            
            direct[0].resize(M);
            direct[1].resize(M);

            for(int i=0; i< M; i++)
                cin>>direct[0][i];

            for(int i=0; i< M; i++)
                cin>>direct[1][i];

            bcs.resize(A);
            for(int i=0; i< A; i++)   
                cin >> bcs[i].p.x >> bcs[i].p.y>> bcs[i].C >> bcs[i].P;

            m[0].p.x=1;        
            m[0].p.y=1;

            m[1].p.x=10;        
            m[1].p.y=10;

            time=0;
            chargepoint=0;
        }
        int solve()
        {
            input();
            int sum=0;   
            do{
            sum+=charge();
            move();
            }while(time <= M);

            return sum;
        }
        void move()
        {
            m[0].p.x += dx[direct[0][time]];
            m[0].p.y += dy[direct[0][time]];

            m[1].p.x += dx[direct[1][time]];
            m[1].p.y += dy[direct[1][time]];
            time++;
        }

        int charge() // 이 시간에 각 충전량을 계산
        {
            int max=-1;
            (m[0].area).clear();
            (m[1].area).clear();
            for(int i= 0; i< bcs.size(); i++) //bcs 주변에 사람이 있는지 조사, 
            {
                for(int ii=0; ii<2; ii++)
                {
                    if( abs(m[ii].p.x - bcs[i].p.x) + abs(m[ii].p.y - bcs[i].p.y) <= bcs[i].C)
                      m[ii].area.push_back(i);
                }
            }

            if(m[0].area.size() ==0 && m[1].area.size() ==0)  //둘다 속한게 없으면 던짐
                return 0;
            else if(m[0].area.size() ==0 && m[1].area.size() !=0)  //m1 속한게 있다면 최고갑 고름            
            {
                for(int i=0; i< m[1].area.size(); i++)
                    if(max < bcs[m[1].area[i]].P) max = bcs[m[1].area[i]].P;
                
                return max;
            }
            else if(m[1].area.size() ==0 && m[0].area.size() !=0)  //m0 속한게 있다면 최고갑 고름            
            {
                for(int i=0; i< m[0].area.size(); i++)
                    if(max < bcs[m[0].area[i]].P) max = bcs[m[0].area[i]].P;
                
                return max;
            }
            else{
                int buf;
                for(int i=0; i< m[0].area.size(); i++)
                    for(int j=0; j< m[1].area.size(); j++)
                    {
                        if (m[0].area[i] == m[1].area[j]) buf = bcs[m[0].area[i]].P;
                        if (m[0].area[i] != m[1].area[j]) buf = bcs[m[0].area[i]].P + bcs[m[1].area[j]].P;
                    
                        if(buf> max) max= buf;
                    }                    
            }
            return max;
        }


};

int main()
{
WirelessCharging W;
cout<<W.solve();
    return 0;
}