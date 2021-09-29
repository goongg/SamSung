//7시 10분

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define debug 0

//위, 아래, 오, 왼
int dx[4] ={0, 0, 1, -1};
int dy[4] ={-1,1, 0, 0 };


class shark
{
    public:
    int y, x, s, d, z ; // 방향, 속도, 방향, 크기 
    int num;
};
typedef vector<shark> ss;
class fisher
{
  int Y, X, M;
  int x = -1;
  vector<shark> sharks;
  vector<bool> dead;
  vector<ss> t;

  public:
    void input()
    {
        cin>>Y>>X>>M; 
        sharks = vector<shark>(M);
        dead = vector<bool>(M) ;
        t = vector<ss>(X*Y);

        for(int i=0; i<M; i++)
        {
            cin>>sharks[i].y>>sharks[i].x>>sharks[i].s>>sharks[i].d>>sharks[i].z; 
            sharks[i].y--;
            sharks[i].x--;
            sharks[i].d--;
            sharks[i].num=i; 
            if(sharks[i].d ==0 || sharks[i].d==1)
                sharks[i].s %= (2*Y -2);
            if(sharks[i].d ==2 || sharks[i].d==3)
                sharks[i].s %= (2*X -2);

        }
    }
    int sol()
    {
        input();
        int score=0;
        vector<shark> nsharks =sharks;// 다음 상어 상태
        int cnt =0;
        vector<ss> nt;
        if(sharks.size()==0) return 0;

        while(x <X){ 
            nt =  vector<ss>(X*Y);

            x++;//어부 이동
            if(sharks.size() ==0 ) break;
#if debug
cout<<"X:"<<x<<"score:"<<score<<endl;
#endif      

            //상어 잡는 단계
            int y_min=9999999;
            for(shark s: sharks)
                if(s.x == x) // 낚시꾼과 같은 열에 있으면,
                    if(y_min > s.y) y_min =s.y; //그중에서 가장 가까운 행이 뭔지 조사

            for(shark s: sharks) 
            {
                if(s.x==x && y_min== s.y)
                {
                    score+= s.z; 
                    dead[s.num] =1;
                }
            }


            //살아남은 상어가 이동하는 단계
            for(int i=0; i<sharks.size(); i++)
            {
                if(dead[sharks[i].num])
                     continue;
                
                cnt=0;
                int ddx= dx[sharks[i].d];
                int ddy= dy[sharks[i].d];
#if debug
cout<< "move " << sharks[i].num <<":"<< sharks[i].y+1<< " "<< sharks[i].x+1 <<endl;
#endif

                for(int s=0; s< sharks[i].s; s++) //상어의 속력만큼 반복
                {
                    if( sharks[i].y + ddy >=0 && sharks[i].y + ddy <Y &&
                            sharks[i].x + ddx >=0 && sharks[i].x + ddx <X)  //끝에 닿지 않았으면 이동
                    {
                        sharks[i].x += ddx;
                        sharks[i].y += ddy;
                    }
                    else{
                        cnt++;  //방향을 바꾼횟수를 기억
                        ddy *= -1;
                        ddx *= -1;
                        sharks[i].y += ddy;
                        sharks[i].x += ddx; //방향을 반대로 바꿔서 이동
                    }
                }

#if debug
cout<< "to    " << sharks[i].num <<":"<< sharks[i].y+1<< " "<< sharks[i].x+1 <<endl;
#endif
                //이 상어의 이동이 다 끝난순간에 방향을 홀수번 바꿨으면
                if(cnt%2 ==1)   
                {
                    if(sharks[i].d ==0 )      sharks[i].d++;
                    else if(sharks[i].d ==1 ) sharks[i].d--;
                    else if(sharks[i].d ==2 ) sharks[i].d++;
                    else if(sharks[i].d ==3 ) sharks[i].d--;
                }

                nt[ sharks[i].y*X + sharks[i].x  ].push_back(sharks[i]);

            }
            sharks.clear();
            //상어가 자기보다 작은 상어를 잡아먹는 단계
            for(int i=0 ; i< Y; i++)
            {
                for(int j=0 ;j< X; j++){
                    int max_size=-1;
                    if (nt[i*X +j].size()==0) continue;
                    for(shark s: nt[i*X +j]) 
                        if(max_size < s.z) max_size=s.z;


                    for(shark s: nt[i*X +j]) 
                        if(max_size == s.z)  sharks.push_back( s); 
                        
                }
            }
            nt.clear();

        }

        return score;
    }

};

int main()
{
    fisher f;
    cout<<f.sol();

    return 0;
}