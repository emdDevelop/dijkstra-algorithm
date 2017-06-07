#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LCHILD 2*parent+1
#define RCHILD 2*parent+2
#define PARENT i/2

#define MAX_VERTICES 200//200
#define INF 100000000

//root at index 0
int heapsize;
int seen[MAX_VERTICES]; //vertices seen so far

typedef struct node{
    int vertex;
    int distance;
}node;

node heap[100000];

typedef struct graph{
    int edge;
    int weight;
    struct graph*next;
}graph;

graph *G[MAX_VERTICES];//For every vertex we add all adjacent edge

void makeGraph();
void insertGraph(int v,int e,int w); //v=vertex ,e=edge,w=weight
void heapInit(int source);
void insertHeap(node key);//insert element to heap
void displayHeap();
node extract_min();//extract min element from heap
void swap(node* n1,node* n2);

void makeGraph(){
char line[1024];
int i=0;
int size,a1;
int e,w,n;
FILE *f;

f=fopen("dijkstraData.txt","r");//dijkstraData.txt

for (i=1;i<=MAX_VERTICES;i++)
 {
   G[i]=NULL;  //initialize to NULL
 }
 i=1;
if(f!=NULL){
    while(fgets(line,sizeof line,f)!=NULL){
    sscanf(line,"%d%n",&a1,&size);
    char *temp=line+size;
 while(sscanf(temp,"%d,%d%n",&e,&w,&n)>0){
        temp+=n;
        insertGraph(i,e,w);
 }
 i++;
 }
}
fclose(f);
}

void insertGraph(int v,int e,int w){
 graph *newNode,*temp;
 newNode=(graph*)malloc(sizeof(graph));
 newNode->edge=e;
 newNode->weight=w;
 newNode->next=NULL;

if(G[v]==NULL){
    G[v]=newNode;
}else{
    temp=G[v];
     while(temp->next!=NULL){
        temp=temp->next; //traverse through nodes until find a node with NULL
    }
    temp->next=newNode; //we put newNode in the end
}
}//end of insertGraph

void display(){

int i;
graph *temp;

for(i=1;i<=MAX_VERTICES;i++)
 {
    temp=G[i];
    if(G[i]==NULL){
        continue;
    }
    printf("%d %d,%d ",i,temp->edge,temp->weight);
    while(temp->next!=NULL)
     {
        temp=temp->next; //traverse through nodes until find a node with NULL
        printf("%d,%d ",temp->edge,temp->weight);
     }
    printf("\n");
  }
}

void heapInit(int source){
    heapsize=0;
    heap[0].vertex=source;
    heap[0].distance=0;
}

void swap(node* n1,node* n2){
node temp;

    temp=*n1;
    *n1=*n2;
    *n2=temp;
}

void insertHeap(node key){
heapsize++;
heap[heapsize]=key;
int now=heapsize;

while(heap[now/2].distance>key.distance && now!=0){
    heap[now]=heap[now/2];
    now /=2;
}
    heap[now]=key;
}//end of insert

void displayHeap(){
int i;

for(i=0;i<MAX_VERTICES;i++){
    printf("%d,%d ",heap[i].vertex,heap[i].distance);
}
printf("\n");
}

node extract_min(){
node minElement;
int parent=0;
int c=0;

minElement=heap[parent];
heap[parent]=heap[heapsize];
heapsize--;

while((heap[parent].distance>heap[LCHILD].distance || heap[parent].distance>heap[RCHILD].distance)&& parent<heapsize-1-c)
{
  if(heap[parent].distance>heap[LCHILD].distance && heap[LCHILD].distance<=heap[RCHILD].distance){
   swap(&heap[parent],&heap[LCHILD]);
   parent=LCHILD;
   c++;

   }else if(heap[parent].distance>heap[RCHILD].distance && heap[RCHILD].distance<heap[LCHILD].distance){
       swap(&heap[parent],&heap[RCHILD]);
       parent=RCHILD;
       c++;
   }
}
return minElement;
}

int main()
{
  int source=1;
  int iter;
  int distance[MAX_VERTICES+1];
  node temp;
  graph* tempg;
  makeGraph();
  heapInit(source);
  distance[1]=0;

  for(iter=1;iter<MAX_VERTICES;iter++){//initialize source distance=0 and all others to infinity
        temp.distance=INF;
        distance[iter+1]=INF;
        temp.vertex=iter+1;
        insertHeap(temp);
  }// end of for

  while(heapsize){
    node min=extract_min();
    int presentVertex=min.vertex;
    if(seen[presentVertex]){
        continue;//if the vertex has already been processed then continue
    }
       seen[presentVertex]=1; //proceed with this vertex and set to 1
       tempg=G[presentVertex];

     while(tempg!=NULL){
        int to=tempg->edge;
     if(distance[to]>distance[presentVertex]+tempg->weight){
        distance[to]=distance[presentVertex]+tempg->weight;
        temp.vertex=to;
        temp.distance=distance[to];
        insertHeap(temp);
        for(iter=1;iter<=MAX_VERTICES;iter++){
        }
     }
       tempg=tempg->next;//traverse through nodes until find a node with NULL
    }
  }
 for(iter=1;iter<=MAX_VERTICES;iter++)
        {
                printf("vertex is %d, its distance is %d\n",iter,distance[iter]);
        }

    return 0;
}
