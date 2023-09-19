#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int board[10][10];
int n;
queue<vector<int> > q;

#define R 0
#define D 1
int dr[2] = { 0, 1};
int dc[2] = { 1, 0};
int point;
void check()
{
    int cnt_r=0;
    int cnt_c=0;

    for(int j=6 ; j<10; j++)
    {
        bool no=0;
        for(int i =0 ; i< 4 ; i++)
            if(board[i][j] ==0) 
                no=1;
        //이 열은 삭제
        if(!no)
        {
            for(int i =0 ; i< 4 ; i++)
                board[i][j] =0;
            
            cnt_r++;                
            point++;     
        }
    }

    for(int i=6 ; i<10; i++)
    {
        bool no=0;
        for(int j =0 ; j< 4 ; j++)
            if(board[i][j] ==0) 
                no=1;
        //이 행은 삭제
        if(!no)
        {
            for(int j =0 ; j< 4 ; j++)
                board[i][j] =0;
            point++;     
            cnt_c++;            
        }
    }

    for(int k=0 ; k <cnt_r ; k++){
    for(int j=9; j>=4; j--)
    {
        bool no=0;
        for(int i =0; i<4; i++)
        {
            if(board[i][j]==1) 
                no=1;
        }
        if(!no) //현재 열이 삭제된 열이면 밀기
        {
            for(int i =0; i<4; i++)
                board[i][j]=board[i][j-1];
            for(int i =0; i<4; i++)
                board[i][j-1]=0;

        }
    }
    }

    for(int k=0 ; k <cnt_c ; k++){
   for(int i=9; i>=4; i--)
   {
        bool no=0;
        for(int j =0; j<4; j++)
        {
            if(board[i][j]==1) 
                no=1;
        }
        if(!no) //다음열이 삭제된 열이면 밀기
        {
            for(int j =0; j<4; j++)
                board[i][j]=board[i-1][j];
            for(int j =0; j<4; j++)
                board[i-1][j]=0;
        }
    }
    }
}

void overflow()
{
    int over_c=0;
    bool over=0;
    for(int j =5 ; j>=4; j--)
    {
        over=0;
        for(int i =0; i<4; i++)
            if(board[i][j]==1) over=1;
        if(over)over_c++;
    }
    if(over_c !=0){
        for(int j=9-over_c; j>=4; j--)
        {
            for(int i =0; i<4 ;i++)
                board[i][j+over_c] = board[i][j];
        }
    }

    int over_r=0;
    for(int i =5 ; i>=4; i--)
    {
        over=0;
        for(int j =0; j<4; j++)
            if(board[i][j]==1) over=1;
        if(over)over_r++;
    }
    if(over_r !=0){
        for(int i=9-over_r; i>=4; i--)
        {
            for(int j =0; j<4 ;j++)
                board[i+over_r][j] = board[i][j];
        }
    }

    for(int i =5 ; i>=4; i--)
    {
        for(int j =0; j<4; j++)
            board[i][j]=0;
    }
    for(int j =5 ; j>=4; j--)
    {
        for(int i =0; i<4; i++)
            board[i][j]=0;
    }    


}

void set(vector<int> v)
{
    int t = v[0];
    int r = v[1];
    int c = v[2];

    if(t==1)
    {
        int nr = r;
        int nc = c;
        while(1)
        {
            nr+=dr[R]; nc+=dc[R];
            if(board[nr][nc]==1 || nc >=10) break;
        }
        nc--;
        board[nr][nc] =1;

        nr= r; nc =c;
        while(1)
        {
            nr+=dr[D]; nc+=dc[D];
            if(board[nr][nc]==1 || nr >=10) break;
        }
        nr--;
        board[nr][nc] =1;     
    }

    else if(t==2)
    {
        int nr = r;
        int nc = c+1;
        while(1)
        {
            nr+=dr[R]; nc+=dc[R];
            if(board[nr][nc]==1 || nc >=10) break;
        }
        nc--;
        board[nr][nc] =1;
        board[nr][nc-1] =1;

        nr= r; nc =c;
        while(1)
        {
            nr+=dr[D]; nc+=dc[D];
            if(board[nr][nc]==1 || board[nr][nc+1] || nr >=10) break;
        }
        nr--;
        board[nr][nc] =1;
        board[nr][nc+1] =1;
    }

    else if(t==3)
    {
        int nr = r;
        int nc = c;
        while(1)
        {
            nr+=dr[R]; nc+=dc[R];
            if(board[nr][nc]==1 ||board[nr+1][nc] || nc >=10) break;
        }
        nc--;
        board[nr][nc] =1;
        board[nr+1][nc] =1;

        nr= r+1; nc =c;
        while(1)
        {
            nr+=dr[D]; nc+=dc[D];
            if(board[nr][nc]==1 || nr >=10) break;
        }
        nr--;
        board[nr][nc] =1;
        board[nr-1][nc] =1;        
    }
}

int num()
{
    int ret=0;
    for(int i =6 ; i<10 ; i++ )
    {
        for(int j=0; j<4; j++)
        {
            if(board[i][j]==1) ret++;
        }
    }   
    for(int j =6 ; j<10 ; j++ )
    {
        for(int i=0; i<4; i++)
        {
            if(board[i][j]==1) ret++;
        }
    }   
    return ret;
}
void print()
{
    cout<<"\nPrint-------\n";
    for(int i =0; i<10; i++)
    {
        for(int j=0; j<10; j++)
        {
            if( !(j >=4 && i>=4))
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
}
int main()
{
    cin>>n;
    for(int i =0; i<n; i++)
    {
        vector<int> v(3);
        cin>>v[0]>>v[1]>>v[2];
        q.push(v);
    }
    int cnt=0;
    while(!q.empty())
    {
        vector<int> v = q.front();
        q.pop();
        set(v);
        check();
        overflow();
        // print();
    }

    cout<<point<<endl<<num();

    return 0;
}