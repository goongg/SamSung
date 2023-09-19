#include <queue>
#include <iostream>
using namespace std;


int n, k;
int belt[210];
bool full[210];
queue<int> bot;
queue<int> nbot;

int answer=1;

void print()
{
    cout<<endl<<"---------------\n";


    for(int i=0; i<n; i++)
        cout<<belt[i] <<" ";
    cout<<endl;
    for(int i=n*2-1; i>=n; i--)
        cout<<belt[i] <<" ";

    cout<<endl<<endl;


    for(int i=0; i<n; i++)
        cout<<full[i] <<" ";
    cout<<endl;
    for(int i=n*2-1; i>=n; i--)
        cout<<full[i] <<" ";

    cout<<endl<<"---------------\n";
}
int main()
{
    cin>>n>>k;
    for(int i =0; i< n*2; i++)
       cin>>belt[i];
    

        // print();

    while(1)
    {

        int buf =belt[2*n-1];
        bool buf_b = full[2*n-1];

        for(int i =n*2; i>=0; i--)
        {   
            full[i]= full[i-1];
            belt[i]=belt[i-1];
        }
            full[0]= buf_b;
            belt[0]= buf;

        int bot_num = bot.size();
        for(int i =0; i< bot_num; i++)
        {
            int b= bot.front();
            bot.pop();
            b++; //우선 밸트따라 한칸 이동
            if(b==n-1)
            {
                full[b]=0;
                continue;
            }
            int next = b+1;
            if(!full[next] && belt[next] !=0 )
            {
                belt[next]--;
                if(next != n-1)
                {
                    bot.push( next );
                    full[next]=1;
                    full[b]=0;
                }
                else
                {
                    full[b]=0; full[next]=0;
                }   
            }
            else
            {
                bot.push(b);
            }
        }    
        if(belt[0] >=1 )
        {
            full[0]=1;
            belt[0]--;
            bot.push(0);
        }        

        int cnt=0;
        for(int i =0 ;i< 2*n; i++)
            if(belt[i] ==0) cnt++;

        
        // print();
        
        if(cnt>=k) break;
        
        answer++;
    }

    cout<< answer;
    return 0;
}