#include <iostream>
#include <queue>
using namespace std;

int ref[]={7,0,1,2,0,3,0,4,2,3,0,3,0,3,2,1,2,0,1,7};
int frames = 3;
int memory[3];
int isfound =0;
int ptr=-1,page_faults=0,front=0;
int page;

int main(){

	
	for(int i=0; i<3; i++)
		memory[i]=-1;
		
	
	for(int i=0; i<20; i++){ // One Page Referance at a Time
		page = ref[i];
		isfound=0;
		cout<<"\n=====Enter page ref-("<<page<<") :"<<endl;
		
		for(int m=0; m<3; m++){
			
			if(page == memory[m]){ // page is already loaded
				cout<<"   Page Found !"<<endl;
				isfound=1;
				continue;
			}
		}
		
		if(!isfound){
			cout<<"   Page Fault occured !"<<endl;
			page_faults++;
			ptr++;
			//cout<<"ptr-"<<ptr<<endl;
			if(ptr<frames){
				memory[ptr] = page;
		    
			}
			else{  // Replace the page
				ptr=(ptr)%frames;
				cout<<"   Replace "<<memory[ptr]<<" with "<<page<<endl;
	
				memory[ptr] = page;

			}
			
			cout<<" Current Memory Status :";
			for(int j=0; j<3; j++){
				cout<<memory[j]<<" ";
			}
			cout<<endl;
		
			
		}
		
		
		
	}
	

return 0;
}
