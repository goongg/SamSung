//8시 10분
#include <iostream>
#include <vector>
#include <queue>
#define debug 0
using namespace std;

class game
{
    int n, m;
    vector<int> t;
    int s[19][2]={
        {4, 1}, // 0
        {1, 4}, // 1

        {2, 2}, // 2
        
        {2, 3}, // 3
        {2, 3}, // 4
        {3, 2}, // 5
        {3, 2}, // 6

        {3, 2},
        {3, 2},
        {3, 2},
        {3, 2},

        {2, 3}, 
        {2, 3}, 
        {2, 3}, 
        {2, 3}, 


        {3, 2},
        {3, 2},

        {2, 3}, 
        {2, 3}, 

    };
    int tetrio[19][6] =
    {
        {1, //0
         1,
         1,
         1},

        {1, 1, 1, 1}, //1

        {1, 1,
         1, 1},

        {1, 1, 1,
         0 ,1 , 0},
        
        {0, 1, 0,
         1 ,1 , 1},
        
        {1, 0,
         1, 1,
         1, 0},

        {0, 1,
         1, 1,
         0, 1},

        {1, 0,
         1, 0,
         1, 1},

        {0, 1,
         0, 1,
         1, 1},

        {1, 1,
         0, 1,
         0, 1},

        {1, 1,
         1, 0,
         1, 0},

        {1, 1, 1,
         1 ,0 ,0},
        
        {1, 1, 1,
         0 ,0 ,1},

        {1, 0, 0,
         1 ,1 , 1},

        {0, 0, 1,
         1 ,1, 1},

        {1, 0,
         1, 1,
         0, 1},

        {0, 1,
         1, 1,
         1, 0},

        {0, 1, 1,
         1 ,1 , 0},

        {1, 1, 0,
         0 ,1, 1},
    };
    
    public:
    void input()
    {
        cin>>n>>m;
        t = vector<int>(n*m);
        for(int i=0; i< n*m ; i++) cin>>t[i];

    }


    int sol()
    {
        input();
        long long ret_max =-1;
        int ret_buf=0;
\
        for(int tt=0; tt<19 ; tt++)
        {
            for(int i=0; i<=n-s[tt][0]; i++)
                for(int j=0; j<=m-s[tt][1]; j++)
                {
                    ret_buf=0;
                    for(int ii= 0; ii< s[tt][0]; ii++){
                        for(int jj= 0; jj< s[tt][1]; jj++)
                        {
                            ret_buf += t[(i+ii)*m +j+ jj] * tetrio[tt][ ii*s[tt][1] + jj];
#if debug
                            cout<< t[(i+ii)*m +j+ jj] * tetrio[tt][ ii*s[tt][1] + jj] <<" ";
#endif
                        }
#if debug
                        cout<<endl;
#endif
                    }
#if debug
                    cout<<endl <<ret_buf<< endl<<endl;
#endif
                    if(ret_max < ret_buf) ret_max =ret_buf;
                }
        }
        return ret_max;
    }

};
        

int main()
{

game g;
cout<<g.sol();
    return 0;
}