#include <string>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

long long TargetNum; /* 만들고 싶은 숫자 */
int Final=1000000;

queue<int> Init_queue1;
queue<int> Init_queue2;

void find(queue<int> q1, queue<int>q2, int cnt)
{
    long long sum=0;    
    
    queue<int> buf;
    while(!q1.empty())
    {
        buf.push(q1.front());
        sum += q1.front();
        q1.pop();
    }
    q1 = buf;
    if(sum == TargetNum) 
    {
        if(cnt < Final)
            Final = cnt;
        return;
    }

    if(cnt !=0 && q1 ==Init_queue1)
        return;

    if(cnt !=0 && q1 ==Init_queue2)
        return;
    

    /*Q1 에있는걸 빼서 q2 에 넣기*/
    if(!q1.empty() && sum > TargetNum)
    {
        q2.push(q1.front());
        q1.pop();

        cnt++;
        if(cnt < Final)
            find(q1, q2, cnt);
        cnt--;

        q1= buf;
        q2.pop();
    }
    else
    {}
    /* q2에 있는걸 빼서 q1에 넣기*/
    if(!q2.empty() && sum < TargetNum )
    {
        buf = q2;
        q1.push(q2.front());
        q2.pop();
        cnt++;
        if(cnt < Final)
            find(q1, q2 ,cnt);
        cnt--; 
    }
    else{}    
}

int solution(vector<int> queue1, vector<int> queue2) {
    int answer = -2;
    for(int i : queue1)
        TargetNum+=i;
    
    for(int i : queue2)
        TargetNum+=i;
    
    if(TargetNum%2 == 1) 
        return -1;
    TargetNum/=2;

    for(int i : queue1)
    {
        Init_queue1.push(i);
    }
    for(int i : queue2)
    {
        Init_queue2.push(i);
    }
    queue<int> q1= Init_queue1;
    queue<int> q2 = Init_queue2;

    find(q1, q2, 0);

    if(Final==1000000) 
        return -1;
    else
        return Final;

    return answer;
}