// 7시 32분


#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define debug 0

class ramp
{
    int n, l;
    vector<int> t; 
    vector<bool> poss_r;// 가능 행 조사
    vector<bool> poss_c;// 가능 열 조사
    vector<bool> v;
    public:
        void input()
        {
            cin>>n >>l;
            t = vector<int>(n*n);
            poss_r = vector<bool>(n);
            poss_c = vector<bool>(n);
            v = vector<bool>(n);
            for(int i=0; i<n*n; i++) cin>>t[i];
        }

        int check()
        {
            int ret=0;
            vector<bool> visit ;

            for(int i=0; i<n; i++)
            {
                poss_r[i] =1;
                visit = v;
                //행 조사
                for(int j=0; j<n-1; j++)
                {
                    int cur= t[i*n+j];
                    int next= t[i*n+j+1];
                    
                    if(cur == next)
                    {
                        //do noting
                    } 
                    else if( cur == next -1)
                    {
                        if(l==n)
                        {
                            poss_r[i] =0;
                            break;   
                        }
                        if(visit[j]) 
                        {
                            poss_r[i] =0;
                            break;   
                        }
                        visit[j]=1;
                        for(int k =1 ; k<l; k++)
                        {
                            if( j-k >=0 && visit[j-k])
                            {
                                poss_r[i] =0;
                                break;   
                            }
                            if( !(j-k >=0 && cur == t[i*n +j-k]) )
                            {
                                poss_r[i] =0;
                                break;                            
                            }
                            visit[j-k]=1;

                        }
                    }
                    else if( cur == next +1){
                    
                        if(l==n)
                        {
                            poss_r[i] =0;
                            break;   
                        }
                        if(visit[j+1]) 
                        {
                            poss_r[i] =0;
                            break;   
                        }
                        visit[j+1]=1;
                        for(int k =1 ; k<l; k++)
                        {   
                            if( j+1+k < n && visit[j+1+k])
                            {
                                poss_r[i] =0;
                                break;   
                            }                     
                            if( !(j+1+k < n  && next == t[i*n +j+1+k]))
                            {
                                poss_r[i] =0;
                                break;                            
                            }
                            visit[j+1+k]=1;
                        }
                    }
                    else
                    {
                        poss_r[i] =0;
                        break;
                    }
                }
                if(poss_r[i]) ret++;
#if debug
                cout<<i<<"행:"<<poss_r[i]<<endl;   
#endif
            }

#if debug
                cout<<endl;   
#endif

            //열 조사
            for(int j=0; j<n; j++)
            {
                poss_c[j] =1;
                visit = v;
                for(int i=0; i<n-1; i++)
                {
                    int cur= t[i*n+j];
                    int next= t[(i+1)*n+j];
                    if(cur == next)
                    {
                        //do noting
                    } 
                    else if( cur == next -1)
                    {

                        if(l==n)
                        {
                            poss_c[j] =0;
                            break;   
                        }

                        if(visit[i]) 
                        {
                            poss_c[j] =0;
                            break;   
                        }
                        visit[i]=1;
                        for(int k =1 ; k<l; k++){
                            if( i-k >=0 && visit[i-k ])
                            {
                                poss_c[j] =0;
                                break;   
                            }
                            if( !(i-k >=0 && cur == t[(i-k)*n +j]))
                            {
                                poss_c[j] =0;
                                break;                            
                            }
                            visit[i-k  ]=1;
                        }
                    }
                    else if( cur == next +1)
                    {

                        if(l==n)
                        {
                            poss_c[j] =0;
                            break;   
                        }
                        
                        if(visit[i+1]) 
                        {
                            poss_c[j] =0;
                            break;   
                        }
                        visit[i+1]=1;
                        for(int k =1 ; k<l; k++){
                            if( i+1+k <n && visit[i+1+k  ])
                            {
                                poss_c[i] =0;
                                break;   
                            }                        
                            if( !(i+1+k < n  && next == t[(i+1+k)*n +j]))
                            {
                                poss_c[j] =0;
                                break;                            
                            }
                            visit[i+1+k  ]=1;
                        }
                    }
                    else
                    {
                        poss_c[j] =0;
                        break;
                    }
                }
                if(poss_c[j]) ret++;
#if debug
                cout<<j<<"열:"<<poss_c[j]<<endl;   
#endif
            }
            return ret;
        }    

};

int main()
{
ramp r;
r.input();
cout<<r.check();
    return 0;
}