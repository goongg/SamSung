#include <iostream>
#include <vector>
using namespace std;

#define debug 0;

typedef pair<int,int> pos;

class shark
{
    int dx[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
    int dy[8] = {  0, -1,-1, -1, 0, 1, 1, 1};
    int n, m;
    vector<int> t;
    vector<pos> c; 
    vector<int> d, s;
public:
    void init()
    {
        cin>>n >>m;
        t= vector<int>(n*n);
        d= vector<int>(m);
        s= vector<int>(m);
        c= vector<pos>(4);
        for(int i=0 ;i <n*n; i++) cin>>t[i];
        for(int i=0 ;i <m; i++) cin>>d[i]>>s[i];
        
        c[0] = {n-1, 0};  c[1] = {n-1, 1};  c[2] = {n-2, 0};  c[3] = {n-2, 1}; 
    }
    void move(int d, int s)
    {
        vector<int> nt=t;
        vector<pos> nc;
        nc.clear();
        d-=1;
        int cx[4]={-1, -1, 1, 1 };
        int cy[4]={-1, 1, 1, -1 };
        
        for(int i=0; i<c.size(); i++)
        {
            
#if debuf
cout<<"cloud" << i<<" :"<<c[i].first <<" "<< c[i].second << " "<< dx[d]<< " "<< dy[d]<<endl;
#endif
      
            c[i].first  += dy[d]*s;
            c[i].second  += dx[d]*s;

               
            while(!(c[i].first>=0))    c[i].first +=n;
            while(!(c[i].second>=0))   c[i].second +=n;    //구름 이동

            
            while(!(c[i].first<n))    c[i].first -= (n);
            while(!(c[i].second<n))   c[i].second -=(n);    //구름 이동
      
#if debuf 
            cout<<"move to : " <<c[i].first <<" "<< c[i].second << " "<< dx[d]<< " "<< dy[d] <<endl<<endl;
#endif
            t[c[i].first *n + c[i].second] +=1;     //이동한곳에 비
        }
#if debuf 
cout<<endl;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
                cout<<t[i*n+j] <<" ";
            cout<<endl;
        }
cout<<endl;
#endif
        for(int i=0; i<c.size(); i++)
        {
            for(int j=0; j<4; j++)                  //주변물 복사
            {
                if( ( c[i].first + cy[j] <n && c[i].first+cy[j] >=0 ) &&
                       ( c[i].second + cx[j] <n && c[i].second+cx[j] >=0 ) &&
                            ( t[ (c[i].first + cy[j])*n + c[i].second + cx[j] ] !=0))
                t[ (c[i].first)*n + c[i].second ] ++;
            }

        }
#if debuf 
cout<<endl;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
                cout<<t[i*n+j] <<" ";
            cout<<endl;
        }
cout<<endl;
#endif
        for(int i=0; i<n; i++) //다음 구름 생성
          for(int j=0; j<n; j++) {

            if( t[i*n+j] >=2)
            {    
                bool check = 0;
                for(int k=0; k<c.size(); k++)
                {
                    if(i==c[k].first && j==c[k].second)
                    check=1;
                }
                if(!check)
                {
                    nc.push_back( make_pair(i,j) );
                    t[i*n+j]-=2;
                }
            }
        }
        c.clear();
        c=nc;
#if debuf 
cout<<endl;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
                cout<<t[i*n+j] <<" ";
            cout<<endl;
        }
        cout<<endl;
#endif
    }


    int sol()
    {
        int ret=0;
        init();
        for(int i=0; i<m; i++)
            move(d[i],s[i]);

        for(int i=0; i<n*n; i++)
         ret+= t[i];

         return ret;
    }
};

int main()
{
shark s;
cout<<s.sol();

return 0;

}
