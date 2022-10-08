#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int num[11];
int map[100];

int go(int start, int num)
{
    int next=0;
    if (start==0) return num;
    if(start ==5 || (start>=31 && start<=33))
    {
        if(start ==5)
            start=30;
        next = start +num;
        if (next >= 34)
            next+= 26;
    }
    else if(start == 10 || (start>=41 && start<=42))
    {
        if(start==10)
            start=40;
        next= start +num;
        if (next >= 43)
            next+= 17;        
    }
    else if(start == 15 || (start>=51 && start<=53) )
    {
        if(start == 15)
            start=50;
        next= start +num;
         if (next >= 54)
            next+= 6;
    }
    else if(start >=60)
        next = start+num;
    
    else if(start <= 20 ) // 지름길이 아닐떄
        next= start +num;
    
    if(next >=21 && next <30)
        next =21;

    else if(next >= 64)
        next = 21;

    else if (next == 63) 
        next=20;

//    cout<<start<<" "<<next<<endl;
    return next;
}

int answer=0;

void dfs(vector<int> hours, int cur_hours, int depth ,int point)
{
    if(depth==10)
    {
        answer= max(point, answer);
        return;
    }    
    int next = go(hours[cur_hours], num[depth]);

    for(int i =0; i<4  ; i++) // 특정 위치에 말이 겹치게 하는 경우는 없음
        if(i!=cur_hours && hours[i] == next && next!=21)
        return;
    
    hours[cur_hours] = next;

    for(int i=0; i<4; i++)
    {
        if(hours[i]!=21)
            dfs(hours, i, depth+1, point+ map[next]);
    }
}

int main()
{
    for(int i =0; i<10; i++)
        cin>>num[i];
    
    for(int i =1; i<=20; i++)
        map[i] = 2*i;

    map[31]= 13; map[32]= 16; map[33]= 19; map[34]=25;
    map[41]= 22; map[42]= 24; map[43] =25;
    map[51]= 28; map[52]= 27; map[53]= 26; map[54]=25;
    map[60]= 25; map[61]= 30; map[62]= 35; map[63]=40;

    vector<int> hours(4);
    for(int i=0; i<4 ; i++) 
        hours[i] = 0;

    dfs(hours, 0,0,0);
    
    cout<<answer;

    return 0;
}