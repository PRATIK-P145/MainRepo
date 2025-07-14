#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(vector<int> val, vector<int> wt, vector<pair<float,int>> ratio, int cap){

	int profit =0;
     
     for(int i=0; i<wt.size(); i++){
     		int weight = wt[ratio[i].second];
     		
     		if(cap < weight){			
     			profit +=  ratio[i].first * (cap);
     			break;
     		}
     		
     		profit += ratio[i].first*weight;
     		cap = cap - weight;
     }
	return profit;
}

bool comp(pair <float,int> p1, pair <float,int> p2){
	return p1.first > p2.first;
}


int main(){

	
     vector<int> val = {10,15,10,20,8};
     vector<int> wt = {3,3,2,5,1};
     int len = wt.size();
     
     	int cap = 10;
     
     vector<pair<float,int>> ratio(len,make_pair(0.0,0));
     
     
     
     for(int i=0; i<len; i++){
     		ratio[i].first = (float)val[i]/wt[i];
     		ratio[i].second = i;
     		//ratio.push_back(make_pair((float)val[i]/wt[i], i));
     		cout<<" "<<ratio[i].first<<","<<ratio[i].second<<endl; 
     }
     
     sort(ratio.begin(), ratio.end(), comp);
    
     
     cout<<"Total : "<< knapsack(val,wt,ratio,cap) <<endl;
     
  
	
	
	
     //for(int i=0; i<len; i++){
     		//cout<<" "<<ratio[i].first<<","<<ratio[i].second<<endl; 
     //}	

}
