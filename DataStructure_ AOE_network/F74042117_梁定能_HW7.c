#include<stdio.h>
#include<stdlib.h>
struct listnode{
	int vertex;
	int dur;
	struct listnode *next;
};
int count = 0,tempnum=0,backward = 0;
typedef struct listnode Listnode;
Listnode *insert(Listnode *head,int ver,int data){
	count++;
	Listnode *current = (Listnode *)calloc(1,sizeof(Listnode));
	Listnode *ptr = head;
	int i;
	current->vertex = ver;
	current->dur = data;
	current->next = NULL;
	if(head==NULL){
		return current;
	}else{
		while(ptr->next!=NULL){
			ptr = ptr->next;
		}
		ptr->next = current;
		return head;
	}
}
void printlist(Listnode *head){
        for(;head!=NULL;head = head->next){
                printf("%d %d\n",head->vertex,head->dur);
        }printf("\n");
}
void vertexnum(Listnode *head,int current,int arr[],int early[]){
	for(;head!=NULL;head=head->next){
		if(arr[current] + head->dur>arr[head->vertex])
			arr[head->vertex] = arr[current] + head->dur;
		early[tempnum++] = arr[current];
	}
}
void lastnum(Listnode *head,int current,int lastarr[]){
	for(;head!=NULL;head=head->next){
		if(lastarr[current]>lastarr[head->vertex] - head->dur)
			lastarr[current] = lastarr[head->vertex] - head->dur;
	}
}
void lasttime(Listnode *head,int current,int lastarr[],int last[]){
	for(;head!=NULL;head = head->next)
		last[backward++] = lastarr[head->vertex] - head->dur;
}
int main(){
	FILE *fp;
	int num,i,j,temp,max = 0,test = 0,isexist =0;
	int early[200],last[200],arr[200],lastarr[200];
	Listnode *head[200];
	
	fp = fopen("Sample_input.txt","r");
	fscanf(fp,"%d",&num);

	for(i=0;i<num;i++)arr[i]=0;
	for(i=0;i<num;i++)head[i] = NULL;
	for(i=0;i<num;i++){
		for(j=0;j<num;j++){
			fscanf(fp,"%d",&temp);
			if(temp!=0){
				head[i] = insert(head[i],j,temp);
				test++;
			}
		}
		if(test==0)isexist++;
		test = 0; 
	}
	if(isexist!=1){
			printf("Failed AOE Network\n");
			return 0;
	}
	
	for(i=0;i<count;i++){
		early[i] = 0;
		last[i] = 0;
	}
	for(j=0;j<5;j++){
		for(i=0;i<num;i++){
			vertexnum(head[i],i,arr,early);
		}
		tempnum=0;
	}
	for(i=1;i<num;i++){
		if(arr[i]==0){
			printf("Failed AOE Network\n");
			return 0;
		}
	}
	
	for(i=0;i<num;i++){
		if(arr[i]>max)max = arr[i];
	}
	for(i=0;i<num;i++)lastarr[i] = max;
	
	for(i=num-1;i>=0;i--){
		lastnum(head[i],i,lastarr);
	}
	for(i=0;i<num;i++){
		lasttime(head[i],i,lastarr,last);
	}
	
	for(i=0;i<count;i++){
		if(early[i]<0||last[i]<0||early[i]>last[i]){
			printf("Failed AOE Network\n");
			return 0;
		}
	}
	printf("activity    e  l  l-e\n");
	printf("-----------------\n");
	for(i=0;i<count;i++){
		printf("(a%2d)      %2d %2d %2d\n",i+1,early[i],last[i],last[i]-early[i]);
	}
	fclose(fp);
}
