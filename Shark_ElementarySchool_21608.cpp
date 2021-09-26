//1시 35분
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

#define debug 0
int dx[4]={0,-1,1,0};
int dy[4]={-1,0,0,1};
int n;
vector<int> t;

class shark{
public:
    int c, r; //자리
    int num; //숫자
    int love[4]; //좋아하는애

    int search() //들어갈 자리를 서치 //i 값을 반환하니까 0~n*n-1 범위
    {        
        vector<int> good;
        vector<int> good_blac;
        vector<int> nt;
        nt= vector<int>(n*n);
        bool f1=0; //좋아하는애가 있는지
        bool f2=0; //자리가 여러갠지

        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            {
                if(t[i*n+j] == love[0]
                    || t[i*n+j] == love[1]
                        || t[i*n+j] == love[2]
                            || t[i*n+j] == love[3]  )
                {
                    //이곳이 내가 좋아하는 애 자리야
                    for(int k=0; k<4; k++)//여기서 네방향 중에 빈칸이 있나 조사해
                    {
                        if( i+dy[k] >=0 && i+dy[k] <n && j+dx[k] >=0 && j+dx[k] <n )
                        if(t[(i+dy[k])*n+j+dx[k]]==0 ) //있어, 그러면 그 자리에 침발라
                            nt[(i+dy[k])*n+j+dx[k]]--; 
                    }
                }
                else
                {
                }
            }
            //nt 음수이거나 0인 자리는 좋은 자리
        int min= 10000;
        int cnt=0;

            for(int i=0; i<n*n; i++) if(nt[i]<=min && t[i] ==0) min = nt[i]; //그중에서 가장 많은것 찾고 
            for(int i=0; i<n*n; i++) if(nt[i]==min && t[i] ==0 ) good.push_back(i); //좋은자리를 넣고
#if debug
            cout<<good_blac.size()<<endl;
#endif
            good_blac= vector<int>(good.size());
            // if(good.size()==0) return 0;
            if(good.size()==1) //하나밖에없음 글로
                return good[0];
            else    //여러개면 그 중 주변에 빈자리조사..
            {
                int ii=0;
                for(int i: good){
                    for(int k=0; k<4; k++)//여기서 네방향 중에 빈칸이 있나 조사해
                    {
                        if(((i/n +dy[k]) >=0 && (i/n +dy[k]) <n && (i%n+dx[k] >=0 && i%n+dx[k] <n) ))
                        if((t[(i/n +dy[k])*n+ i%n+dx[k]]==0))
                            cnt++;
                    }
                    good_blac[ii]= (cnt);
                    ii++;
                    cnt=0;
                }
                int max=-1;
                for(int i=0; i< good_blac.size(); i++)
                    if(max <= good_blac[i]) max = good_blac[i]; //가장 많은 빈칸의 크기
                for(int i=0; i< good_blac.size(); i++)          
                    if(max==good_blac[i]) return good[i];       //그 자리중 숫자가 제일 작은것이 들어갈 자리
            }
    }
};
vector<shark> student;

int main()
{
    cin>>n;
    t= vector<int>(n*n);
    for(int i=0 ;i<n*n; i++) t[i]=0;

    student= vector<shark>(n*n);
    int ret=0;
    vector<vector<int>> near_stu((n+1)*(n+1));

    int select;
    for(int i=0; i<n*n; i++) 
        cin>>student[i].num>>student[i].love[0]>>student[i].love[1]>>student[i].love[2]>>student[i].love[3];

    for(int i=0; i<n*n; i++)
    {
        select= student[i].search();
        t[select]= student[i].num;

#if debug
        cout<<i<<" num:" <<student[i].num<<" seleceted:"<<select<<endl;

        for(int ii=0; ii<n; ii++)
        {    for(int jj=0; jj<n; jj++)
                cout<<t[ii*n+jj]<<" ";
            cout<<endl;
        }   
#endif
    }

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
    {
        //4방향 조사
        for(int k=0; k<4; k++)  
        {
            if( i+dy[k] >=0 && i+dy[k] <n && j+dx[k] >=0 && j+dx[k] <n )
                near_stu[t[i*n+j]].push_back( t[(i+dy[k])*n +j+dx[k]] );
        }
    }
    // cout<<"?";
    for(int i=0; i<n*n; i++)
    {
        int cnt=0;
        for(int j: near_stu[student[i].num]) // 첫번째 학생 주변 학생을 조사
        if( j == student[i].love[0] || j == student[i].love[1] || j == student[i].love[2] || j == student[i].love[3] )
            cnt++;
        if(cnt ==1) ret+=1;
        if(cnt ==2) ret+=10;
        if(cnt ==3) ret+=100;
        if(cnt ==4) ret+=1000;
        

    }
    cout<<ret;
return 0;

}