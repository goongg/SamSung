#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> pos;

int dx[5] = {0, 0, 0, -1, 1};
int dy[5] = {0 ,-1, 1, 0, 0};
  

class Shark
{
    int n, m;
    vector<int> vd;
    vector<int> vs;
    vector<int> t;
    int sx, sy;
  
    vector<int> q;

    public:
    int answer=0;
        void init()
        {
            cin>>n>>m;
            t = vector<int>(n*n);
            vd = vector<int>(m); 
            vs = vector<int>(m);
            for(int i=0; i<n*n; i++)
                cin>>t[i];
            for(int i=0 ; i< m; i++)
                cin>>vd[i]>>vs[i];
            sx = n/2;
            sy = n/2;

            toQ();
        }

        void toQ()
        {    
            q.clear();        
            int cnt=1;
            int cx, cy, nx, ny;
            cx= sx; cy= sy;
            // cout<<"asdfasdf" <<cx<<" "<<cy<<endl<<endl;
            while(1)
            {

                for(int i=0; i< cnt; i++)
                {
                    nx= cx -1;
                    ny= cy;
                    q.push_back(t[ny*n + nx]);
                    // cout<< "L:"<< nx <<" " <<ny<<" "<<t[ny*n + nx]<<endl;
                    cx = nx;
                    cy = ny;
                    if(cx==0 && cy==0)
                        return;
                }//L

                for(int i=0; i< cnt; i++)
                {
                    nx= cx;
                    ny= cy +1;
                    q.push_back(t[ny*n + nx]);
                    // cout<< "D:"<< nx <<" " <<ny<<" "<<t[ny*n + nx]<<endl;
                    cx= nx;
                    cy =ny;
                }//D

                cnt++;
                for(int i=0; i< cnt; i++)
                {
                    nx= cx +1;
                    ny= cy ;
                    q.push_back(t[ny*n + nx]);
                    // cout<< "R:"<< nx <<" " <<ny<<" "<<t[ny*n + nx]<<endl;
                    cx= nx;
                    cy =ny;
                }//R

                for(int i=0; i< cnt; i++)
                {
                    nx= cx ;
                    ny= cy -1;
                    q.push_back(t[ny*n + nx]);
                    // cout<< "U:"<< nx <<" " <<ny<<" "<<t[ny*n + nx]<<endl;
                    cx= nx;
                    cy =ny;
                }//U
                cnt++;
            }
            
        }
        void toT()
        {         
            int cnt=1;
            int cx, cy, nx, ny;
            cx= sx; cy= sy;
            int ii=0;
            while(1)
            {

                for(int i=0; i< cnt; i++)
                {
                    nx= cx -1;
                    ny= cy;
                    t[ny*n + nx] = q[ii++];
                    // cout<< "L:"<< nx <<" " <<ny<<" "<<t[ny*n + nx]<<endl;
                    cx = nx;
                    cy = ny;
                    if(cx==0 && cy==0)
                        return;
                }//L

                for(int i=0; i< cnt; i++)
                {
                    nx= cx;
                    ny= cy +1;
                    t[ny*n + nx] = q[ii++];
                    // cout<< "D:"<< nx <<" " <<ny<<" "<<t[ny*n + nx]<<endl;
                    cx= nx;
                    cy =ny;
                }//D

                cnt++;
                for(int i=0; i< cnt; i++)
                {
                    nx= cx +1;
                    ny= cy ;
                    t[ny*n + nx] = q[ii++];
                    // cout<< "R:"<< nx <<" " <<ny<<" "<<t[ny*n + nx]<<endl;
                    cx= nx;
                    cy =ny;
                }//R

                for(int i=0; i< cnt; i++)
                {
                    nx= cx ;
                    ny= cy -1;
                    t[ny*n + nx] = q[ii++];
                    // cout<< "U:"<< nx <<" " <<ny<<" "<<t[ny*n + nx]<<endl;
                    cx= nx;
                    cy =ny;
                }//U
                cnt++;
            }
            
        }

        void magic(int d, int s)
        {
            int cx, cy;
            cx= sx; cy =sy;
            for(int i=0; i<s; i++)
            {
                cy += dy[d];
                cx += dx[d];
                // answer+=t[ (cy)*n + cx ];
                t[ (cy)*n + cx ] =0;
                // cout<<"?";
            }
            toQ();
            // for(int i: q)
            // {cout<<i <<" ";}
            // cout<<endl;
        }
        void fill()
        {
            vector<int> nq;
            int cnt=0;
            for(int i:q)
            {
                if(i ==0)
                cnt++;
                else
                nq.push_back(i);
            }
            for(int i=0; i< cnt; i++)
                nq.push_back(0);
            q= nq;
        
            // for(int i: q)
            // {cout<<i <<" ";}
            // cout<<endl;
        }

        bool exp()
        {
            vector<int> nq;
            bool flag=0;
            int ex=q[0];
            int cnt=1;
            for(int i=1 ; i<q.size(); i++)
            {   
                int cur= q[i];
                if(cur ==ex)
                    cnt++;
                
                else{
                    if(cnt >=4)
                    {
                        flag=1;
                        answer+= ex*cnt;
                        // cout<< "EXP!: "<<ex<<" "<<cnt<<endl;
                        cnt=1;
                    }
                    else
                    {
                        for(int j=0; j<cnt; j++)
                            nq.push_back(ex);
                        cnt=1;
                    }
                }
                ex= cur;
            }
            nq.push_back(ex);

            while (nq.size() < q.size())
                nq.push_back(0);
            
            if(flag)
                q= nq;

            // for(int i: q)
            // {cout<<i <<" ";}
            // cout<<endl;
            return flag;
        }

        void change()
        {
            vector<int> nq;
            nq.clear();
            int gup;
            int num;
            int cnt=1;
            int ex=q[0];
            // cout<<"change!"<<endl;
            for(int i=1 ; i<q.size(); i++)
            {   
                int cur= q[i];
                if(cur ==ex)
                    cnt++;
                
                else if (ex !=0){
                    nq.push_back(cnt);
                    nq.push_back(ex);
                    cnt=1;
                }

                if(i == q.size()-1)
                {   
                    if(ex !=0)
                    {
                        nq.push_back(cnt);
                        nq.push_back(ex);
                    }
                }
                ex= cur;
            }

             while (nq.size() > q.size())
                nq.pop_back();

            while (nq.size() < q.size())
                nq.push_back(0);
              
            q= nq;

            toT();
        

            // for(int i: q)
            // {cout<<i <<" ";}
            // cout<<endl<<endl;

            // for(int i=0; i<n; i++)
            // {    
            //     for(int j=0; j<n ;j++) 
            //     //     cout<<t[i*n+j] <<" ";
            //     // cout<<endl;
            // }
        }

        int sol()
        {
            init();
            for(int i =0; i<m ; i++)
            {    
                magic(vd[i],vs[i]);
                fill();
                while(1)
                {
                  bool end;
                  end= exp();
                  if(!end)
                  break;
                }
                change();
            }

            return answer;
        }

};


int main()
{
    Shark S;

    cout<<S.sol();
   return 0;


}
