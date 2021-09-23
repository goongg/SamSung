#include <iostream>
#include <vector>
#include <cstring>
#define debug 0

using namespace std;

//3시 6분
int dx[8] = {0,-1,-1,-1,0,1,1,1};
int dy[8] = {-1,-1,0,1,1,1,0,-1};
class fish{

    public:
    int a, b;  // 번호, 방향4
};
int dfs_ans=-1;

class shark
{

    public:
        vector<fish> map;
        bool arrive[17] ={1,1,1,1 ,1,1,1,1, 1,1,1,1, 1,1,1,1,1 };
        bool posible=1;
        int a=0;
        int sc=0;
        int sr=0;
        int b;      //방향
        int first_fish=10000;
         int last_fish=-1;
        void input()
        {
            map= vector<fish>(16);
            for(int i=0; i<4; i++)
                for(int j=0; j<4;j++)
                    {
                        cin>>map[i*4 + j].a>>map[i*4 + j].b;
                        map[i*4 + j].b--;
                        if(map[i*4 + j].a >= last_fish) last_fish= map[i*4 + j].a;
                        if(map[i*4 + j].a <= first_fish) first_fish= map[i*4 + j].a;
                    }
            a+=map[0].a;
            b= map[0].b;
            arrive[map[0].a]=0;
            map[0].a =0;
            map[0].b =0;
        }

        void move_fish()
        {
            for(int i=1; i<=16; i++)
                if ( arrive[i]) {
                    first_fish=i; break;
                }

            for(int i=16; i>=1; i--)
                if ( arrive[i]) {
                    last_fish=i; break;
                }
                
            int serch_num=first_fish;
            bool serch_flag=0;
            int c, r;
            fish from, to;
            while(1)
            {
                for(int i=0; i<4; i++){
                   for(int j=0; j<4; j++)
                        if(map[i*4+j].a== serch_num)
                        {
                            serch_flag=1;
                            c=i; r=j;
                            break;
                        } 
                    if(serch_flag) break;
                }

        #if debug
        cout<<"serch" << serch_flag <<" "<< serch_num<<": " <<c<<" " <<r<< " " <<map[ (c)*4+ r ].b <<endl;
        #endif

            if(serch_flag)  //번호의 물고기가 있으면 이동해
            { 
                from= map[ c*4+ r ];
  
                for(int i= 0; i<8; i++)
                {
                    if( c + dy[from.b] >=0 && c + dy[from.b] <4 &&    //움직일수 있으면
                            r + dx[from.b] >=0 && r + dx[from.b] <4 &&
                                !(r + dx[from.b] ==sr && c + dy[from.b] ==sc) )            
                    {
                        to= map[ (c + dy[from.b])*4 + (r + dx[from.b])];
                        map[ (c + dy[from.b])*4 + (r + dx[from.b])] =from;
                        map[ c*4 + r ] = to;
                        
                               #if debug
                               cout<<"to:"<<to.a<<" from:"<<from.a<<endl;
                               #endif

                            break;
                    }
                    else    //못가면 화전
                        from.b = (from.b+1)%8;  
                
                }
            }

        #if debug
        cout<<endl<<"----------------"<<endl;
        for(int i=0; i<4 ;i++){
            for(int j=0; j<4; j++)
                cout<<map[i*4 + j].a<<" ";
            cout<<endl;
        }
        cout<<"----------------"<<endl;
        #endif

            serch_flag=0;
            serch_num++;
            if(serch_num>last_fish)
                break;
        }


        #if debug
        for(int i=0; i<4 ;i++){
            for(int j=0; j<4; j++)
                cout<<map[i*4 + j].a<<" ";
            cout<<endl;
        }
        #endif
    }
        


};


int dfs(  shark s)
{

    if( dfs_ans < s.a) dfs_ans= s.a;
    
        for(int i=1; i<=3; i++) //많이 가봐야 최대 3칸
        {
            shark ns=s;
            ns.posible=0;
            if( s.sc + dy[s.b]*i >=0 && s.sc + dy[s.b]*i <4 &&
                 s.sr + dx[s.b]*i  >=0 && s.sr + dx[s.b]*i <4 &&
                    s.arrive[s.map[ (s.sc + dy[s.b]*i)*4+  s.sr + dx[s.b]*i].a] ) // 절로 갈 수 있으면       
            { 
                ns.posible=1;
                ns.sc= s.sc + dy[s.b]*i;
                ns.sr= s.sr + dx[s.b]*i;            //상어 위치 이동
                ns.a += s.map[ ns.sc*4+  ns.sr].a;  //잡아먹고
                ns.b = s.map[ ns.sc*4+  ns.sr].b;   //방향 저장 
                ns.map[ ns.sc*4+  ns.sr].a=0; 
                ns.map[ ns.sc*4+  ns.sr].b=0;
                 
                ns.arrive [ns.map[ ns.sc*4+  ns.sr].a] =0;

                ns.move_fish();


                dfs(ns);
            }
        }

    return dfs_ans;

}


int main()
{
shark s;
s.input();
s.move_fish();
cout<< dfs(s);
// cout<<dfs(s);

    return 0;
}