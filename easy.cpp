

#include <iostream>
#include <queue>
using namespace std;
int main()
{
      int b, c,n;
  long long answer=0;
    queue<int> q;
    cin>>n;
    for(int i =0; i< n; i++)
    {
        int a;
        cin>>a;
        q.push(a);
    }
    cin>>b>>c;

    while(!q.empty())
    {
        int a= q.front();
        q.pop();

            if(a-b <= 0)  answer+=1;
            else if( (a-b)%c ==0 ) answer += (a-b)/c +1 ;
            else  answer += (a-b)/c +1 +1 ;
    }
    cout<<answer;
}