#include <iostream>
#include <vector>
using namespace std;
#define debug 0


class board {

    vector<int> t;
    vector<int> v;


    int ans;
    int n;
    public:


        void input()
        {
            cin>>n;
            t = vector<int>((n+1)*(n+1));   //문제 input조건에 맞춤 0 열, 0행 버림
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    cin>>t[i*n+j];

        }

        int calc(int x ,int y, int d1, int d2) //선거구 정해서 제일큰거 작은거 뺴기
        {
            v.clear();
            v = vector<int>((n+1)*(n+1));  //선거구
            vector<int> p(6);
            int cnt =0;
            bool f=0;
                
                int c, r;
                c=x; r=y;
                int dc[4]= {1, 1, -1, -1}; 
                int dr[4]= {1, -1, -1, 1};
                int dd[4]= {d2, d1, d2,d1};

                for(int j=0; j<4; j++)  //경계선 긋기
                    for(int i=0; i< dd[j]; i++)
                    {
                       v[c*n+ r] =5;
                       c+=dc[j]; r+=dr[j];
                    }  


                // //경계선에 닿기 전까지 1
                for(int i=1; i<x+d1; i++)
                    for(int j=1; j<= y; j++)
                    {
                        if(v[i*n+j] ==5)
                            break;
                        else v[i*n+j]=1;
                    }

                 for(int i=1; i<=x+d2; i++)
                    for(int j=n; j> y; j--)
                    {
                        if(v[i*n+j] ==5)
                            break;
                        else v[i*n+j]=2;
                    }

                for(int i=x+d1; i<=n; i++)
                    for(int j=1; j< y-d1+d2; j++)
                    {
                        if(v[i*n+j] ==5)
                            break;
                        else v[i*n+j]=3;
                    }

      

                for(int i=x+d2+1; i<=n; i++)
                    for(int j=n; j>= y-d1+d2; j--)
                    {
                        if(v[i*n+j] == 5 )
                            break;
                        else v[i*n+j]=4;
                    }

#if debug
                cout<<endl;
#endif              
                for(int i=1; i<=n; i++){
                    for(int j=1; j<=n; j++)
                    {
                        if(v[i*n+j] == 1)   p[1] += t[i*n+j];
                        if(v[i*n+j] == 2)   p[2] += t[i*n+j];
                        if(v[i*n+j] == 3)   p[3] += t[i*n+j];
                        if(v[i*n+j] == 4)   p[4] += t[i*n+j];
                        if(v[i*n+j] == 5 ||v[i*n+j] == 0) p[5] += t[i*n+j];
#if debug
                        cout <<v[i*n+j]  <<" " ;
#endif
                    }
#if debug
                   cout<<endl;
#endif                    
                }
#if debug                
                cout<<"p:" <<p[1] <<" "<<p[2] <<" "<<p[3] <<" "<<p[4] <<" "<<p[5] <<endl;
#endif

            int max=-1, min=10000000;
            for(int i=1; i<6; i++)
            {
                if( p[i] > max) max =p[i];
                if( p[i] < min) min =p[i];
            }
            
               return max-min;
        }

        int sol()
        {
            input();
            int a;
            int min=100000000;
            for(int d1 =1; d1<=n; d1++){
                for(int d2= 1; d2<=n; d2++){
                    for(int x =1; x<=n; x++){
                        for(int y =1; y<=n; y++){
                            if ( (x+d1+d2 <=n) && (d1 + 1 <=y) && ( y+d2 <=n) )   
                            {
                                a = calc(x, y, d1, d2);
#if debug
                                cout<< x<<" " << y<<" "<< d1<<" "<<d2<<" "<<endl;
                                cout <<a <<endl;
#endif
                                

                                if(min > a) min=a;
                            } 
                         }
                    }
                }
            }
        
            return min;
        }
};

int main()
{

board b;
cout<<b.sol();
// b.input();
cout<<endl;
// cout << b.calc(2,4,2,2);
// cout << b.calc(2,5,3,2);
// cout << b.calc(4,3,1,1);


}