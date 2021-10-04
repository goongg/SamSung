//1시 20분
#include <iostream>
#include <vector>
#include <queue>
#define debug 0
using namespace std;

int dx[8] ={-1 , -1 , 0, 1, 1, 1, 0, -1,};
int dy[8] ={0,  -1,  -1, -1, 0, 1, 1, 1 };

class tree
{
    public:
    int y, x; //위치
    int age=1;
    bool dead=0;  //죽었는지 살았는지
    bool aging=0; //나이를 먹었는지 안먹었는지

    
};
typedef vector<tree> ts;

class field
{
    int n, m, k;
    vector<int> a;
    vector<ts> t;   //그걸 칸에다가 넣은것
    vector<int> f;

    ts trees;       //살아있는 트리의 목록
    public:
        void input()
        {
            cin>>n>>m>>k;
            t = vector<ts>(n*n);
            a = vector<int>(n*n);
            f = vector<int>(n*n);
            trees= vector<tree>(m);
            for(int i=0 ;i <n*n; i++)
            {
                cin>> a[i];
                f[i]= 5;   
            }
            for(int i=0; i< m; i++)
            {
                cin>>trees[i].y >> trees[i].x>> trees[i].age;
                trees[i].y--;
                trees[i].x--;
                t[trees[i].y  * n + trees[i].x ].push_back(trees[i]); 
            }
        }

        void spring()   //봄
        {
            
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    if(t[i*n+j].size() ==0)
                        continue;
#if debug
cout<<"\nspring 칸:" <<i+1<<" "<<j+1<<" 양분:"<< f[i*n +j] <<endl;
#endif
                    bool end=0; 
                    while(!end)
                    {
                        end=1;
                        int min_age=100000;
                        //어린 어린 나이를 찾아
                        for(int k=0; k< t[i*n+j].size(); k++)
                            if( t[i*n+j][k].age <min_age && !t[i*n+j][k].aging && !t[i*n+j][k].dead )
                            {
                                min_age=t[i*n+j][k].age;
                                end=0;
                            }
                        //제일 어린 나무를 찾아
                        for(int k=0; k< t[i*n+j].size(); k++)
                        {
                            if( t[i*n+j][k].age == min_age && !t[i*n+j][k].aging && !t[i*n+j][k].dead )
                            {
                                if( f[i*n +j] >=  t[i*n+j][k].age)
                                {
                                    f[i*n +j]-= t[i*n+j][k].age;
                                    t[i*n+j][k].age++;
                                    t[i*n+j][k].aging=1;
#if debug
cout<<"aging:" << t[i*n+j][k].age << " 양분:"<< f[i*n +j]<<endl;
#endif
                                }
                                else
                                {
                                    t[i*n+j][k].dead=1;
                                    end=1;
                                    break;
#if debug                           
cout<<"dead:" <<endl;
#endif
                                }
                            }
                        }
                    }
                }
            }
        }
        
        void summer()   //여름
        {
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    if(t[i*n+j].size() ==0)
                        continue;
                    ts nt;
                    for(int k=0; k< t[i*n+j].size(); k++)
                    {
                        if(!t[i*n+j][k].aging ) f[i*n +j] += t[i*n+j][k].age/2;

                        else
                        {
                            t[i*n+j][k].aging=0;
                            nt.push_back(t[i*n+j][k]);
                        }
                    }
                        t[i*n+j]= nt;
#if debug
cout<<"summer 칸:" <<i+1<<" "<< j+1<<" 양분:" << f[i*n +j] << " 남아있는 나무"<<t[i*n+j].size() <<endl;
#endif
                    nt.resize(0);
                    nt.clear();
                    // while(nt.size()!=0) nt.pop_back();
                }
            }
        }


        void fall() //가을
        {
            vector<ts> nt= t;
            tree new_tree;

            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    if(t[i*n+j].size() ==0)
                        continue;

                    for(int k=0; k< t[i*n+j].size() ;k++)
                    {
                        if(t[i*n+j][k].age %5 ==0 ) 
                        {

#if debug
                            cout<<"fall 번식 칸:"<<i+1<<" "<<j+1<<endl;
#endif

                            for(int d=0; d<8; d++)
                            {
                                new_tree.y= i+dy[d];
                                new_tree.x= j+dx[d];
                                new_tree.age=1;
                                new_tree.aging=0;
                                new_tree.dead=0;
                                if(new_tree.y <0 || new_tree.y>=n ||
                                 new_tree.x <0 || new_tree.x>=n)
                                    continue;
                                
                                // cout<<new_tree.y+1 << " " <<new_tree.x+1<<endl;
                                nt[(new_tree.y)*n +new_tree.x].push_back(new_tree);
                            }
                            // cout<<endl;
                        }
                    }
                }
            }
            t= nt;
        }
        
        int winter()
        {
            int ret=0;
            for(int i=0; i<n; i++)
            {
                for(int j=0; j<n; j++)
                {
                    f[i*n +j] += a[i*n +j];
                    ret += t[i*n+j].size();
                }
            }
            // cout<<"winter:" <<ret<<endl;
            return ret;
        }

    int sol()
    {
        int ret;
        input();
        for(int i=0; i<k; i++)
        {
#if debug
cout<<i<<"년"<<endl;
#endif

            spring();
            summer();
            fall();
            ret= winter();
        }
        return ret;
    }

};


int main()
{

field ff;

cout<< ff.sol();
    return 0;
}
