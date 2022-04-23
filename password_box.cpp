#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define debug 1

int main(int argc, char** argv)
{
	int test_case;
	int T;
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
//	freopen(&quot;input.txt&quot;, &quot;r&quot;, stdin);
	cin>>T;
    int N,K;
	string num_list;
	string new_num_list;
    vector<long long int>  num_all;
    vector<long long int> answer;
    for(test_case = 1; test_case <= T; ++test_case)
	{
        num_all.clear();
		cin>>N>>K;
        num_list.resize(N);
		for(int i=0; i<N; i++)
            cin>>num_list[i];
         
        string split_num[4]; //이 배열에 각 모서리 숫자가 들어감
        long long int split_num_int[4]={0,0,0,0}; //이 배열에 각 모서리 숫자가 들어감

        new_num_list.resize(N);
        //이 밑에 동작은 총 N/4만큼 해야함
        for(int rotation =0; rotation < (N/4); rotation++)
        {
            for(int ii=0; ii<4; ii++)
                split_num_int[ii]=0;

            split_num[0] = num_list.substr(0,       N/4);
            split_num[1] = num_list.substr(N/4,     N/4);
            split_num[2] = num_list.substr((N/4)*2, N/4);
            split_num[3] = num_list.substr((N/4)*3, N/4);
            
#if debug
cout<<"---------------------------------------";
        cout<<split_num[0]+" "<<split_num[1]+" "<<split_num[2]+" "<<split_num[3]+"\n";
#endif 

            //각숫자를 10진수로 변경
            int mul=16;

            for(int i=0; i<split_num[0].size(); i++)
            {
                int c_to_i[4];
                for(int ii=0; ii<4; ii++)
                {
                    if(split_num[ii][i] >='0' && split_num[ii][i] <='9')
                        c_to_i[ii] = (int)split_num[ii][i] - (int)'0';
                    else if(split_num[ii][i] >='A' && split_num[ii][i] <='F')
                        c_to_i[ii] = (int)split_num[ii][i] - (int)'A' + 10;
                }

                for(int ii=0; ii<4; ii++)
                {
                    split_num_int[ii] += c_to_i[ii];
                    split_num_int[ii] *= mul;
                }

            }
            for(int i=0; i<4; i++)
            {
                split_num_int[i]/=mul;
               num_all.push_back(split_num_int[i]);
            }
#if debug
        cout<<split_num_int[0]<<" "<<split_num_int[1]<<" "<<split_num_int[2]<<" "<<split_num_int[3]<<" \n";
#endif 

            new_num_list[0]= num_list.back();
            for(int i=0; i<N-1; i++)                    
               new_num_list[i+1] =num_list[i];
        
            num_list=new_num_list;
        }

        sort(num_all.begin(), num_all.end());
        num_all.erase(unique(num_all.begin(), num_all.end()), num_all.end());
        cout<<"#"<<test_case<<" "<<num_all[num_all.size() -K]<<'\n';
#if debug
        for(long long int ii : num_all)
        cout<< ii <<" ";
#endif 


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}


