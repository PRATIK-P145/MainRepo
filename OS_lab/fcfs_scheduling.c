#include <stdio.h>

struct process{
	int  at;
	int  st;
	int  wt;
	int  ct;
	int tat;
};

int main(){
	struct process p[6];
	
	printf("Enter Arrival Time :\n");
	for(int i=0; i<5; i++){
		printf("P%d ",i+1);
		scanf(  "%d",&p[i].at );
	}
	
	printf("Enter Service Time :\n");
	for(int i=0; i<5; i++){
		printf("P%d ",i+1);
		scanf( "%d",&p[i].st );
	}
	struct process temp;
	for(int i=0; i<4; i++){
		for(int j=0; j<4-i; j++){
			if( p[j].at > p[j+1].at){
				temp = p[j];
				p[j] = p[j+1];
				p[j+1] = temp;
			}		
		}
	}
	
	p[0].ct = p[0].st;
	p[0].wt = 0;
	
	printf("Arrival Time :\n");
	for(int i=0; i<5; i++){
		printf("P%d\t ",i+1);
		printf(  "%d\n",p[i].at );
	}
	
	for(int i=1; i<5; i++){    //Calculate Completion Time
		p[i].ct  =  p[i-1].ct + p[i].st;
	}
	
	for(int i=1; i<5; i++){   //Calculate Wait  Time
		p[i].wt  =  p[i-1].ct - p[i].at;
	}
	
	for(int i=0; i<5; i++){   //Calculate Turn Around Time
		p[i].tat  =  p[i].st + p[i].wt;
	}
	
	printf("Arrival\tService\tWaiting\tCompl\tTAT\n");
	for(int i=0; i<5; i++){
		
		printf("%d\t%d\t%d\t%d\t%d\n",p[i].at,  p[i].st,  p[i].wt,  p[i].ct,  p[i].tat);
	
	}



	return 0;
}
