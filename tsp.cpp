#include<iostream>

#include <climits>
using namespace std;


const int inf = INT_MAX;
int cost[5]={};

struct Node{
	int cost=0;
	int red[5][5]={};
};

int inp[5][5]={{inf,20, 30, 10, 11},{15,inf,16,4,2},{3,5,inf,2,4},{19,6,18,inf,3},{16,4,7,16,inf}};



int main(){
	struct Node node[5];

	int min = inf;;
	for(int i=0; i<5; i++){
		min = inp[i][0];
			for(int k=0; k<5; k++){
				node[0].red[i][k]=inp[i][k];
				if(inp[i][k]<min){
					min=inp[i][k];
				}
			}
			cout<<"Min is - "<<min<<endl;
			for(int j=0; j<5; j++){
				
				node[0].red[i][j] -= min;
				node[0].cost+=min; 
			}
	}
	
	for(int i=0; i<5; i++){
		min = node[0].red[i][0];
			for(int k=0; k<5; k++){
				
				if(inp[i][k]<min){
					min=inp[k][i];
				}
			}
			cout<<"Min is - "<<min<<endl;
			for(int j=0; j<5; j++){
				
				node[0].red[j][i] -= min;
				node[0].cost+=min; 
			}
	}
	
	
	
	
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			cout<<node[0].red[i][j]<<" ";
		}
		cout<<endl;
	}


	return 0;
}
