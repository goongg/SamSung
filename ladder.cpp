#include <iostream>
#include <vector>
using namespace std;
int n, m, h;

int ladder[100][100]; // 특정 위치에 있는지 체크
void set_ladder(int a, int b, bool set)
{
    if(set)
        ladder[a][b]=1; //a의 b번 세로선의 오른쪽
    else
        ladder[a][b]=0; //a의 b번 세로선의 오른쪽    
};

bool game()
{
    for(int i=1; i<=n; i++)
    {
        int cur = i;
        for(int j =1; j<=h ; j++){
            if(ladder[j][cur] == 1) 
                cur = cur+1;
            else if(ladder[j][cur-1] == 1) 
                cur = cur-1;
        }
        if(cur != i) return 0;
    }
return 1;
}
int answer= 5;
void dfs(int depth, int a, int b)
{
    if(game())
    {
        answer = min(answer, depth);
        return;
    }
    if(depth==3) return;
    for(int j =a; j<=h; j++)
    {
        for(int i =b ; i<n; i++)
        {
            if(ladder[j][i] == 1 ||
                ladder[j][i-1] ==1 ||
                  ladder[j][i+1] == 1 )
                  continue;
            set_ladder(j,i,1);
            dfs(depth+1, j, 1);
            set_ladder(j,i,0);        
        }
    }
};



int main()
{
    cin>>n>>m>>h;
    for(int i=0; i< m; i++)
    {
        int a, b;
        cin>>a>>b;
        set_ladder(a,b,1);
    }
    dfs(0, 1, 1);
    
    if(answer ==5) cout<< -1;
    else cout<< answer;

return 0;
}