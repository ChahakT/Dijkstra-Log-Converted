#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<limits.h>


struct AdjListNode
{
    int dest;
    float weight;
    struct AdjListNode* next;
};
 
struct AdjList
{
	float vwt;
    struct AdjListNode *head;  // pointer to head node of list
};
 
struct Graph
{
    int V;int E;
    struct AdjList* array;
};
 
struct AdjListNode* newAdjListNode(int dest, int weight)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}
 
struct Graph* createGraph(int V,int E)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
 
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0; i < V; ++i){
    	graph->array[i].vwt=0;
        graph->array[i].head = NULL;
    }
 
    return graph;
}
 

void addEdge(struct Graph* graph, int src, int dest, int weight)
{
   
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
} 

void readEdge(struct Graph* graph,int i){
	struct AdjListNode* ptr=graph->array[i].head;
	while(ptr!=NULL){
		if(ptr!=graph->array[i].head)cout<<", ";
		cout<<ptr->dest;
		ptr=ptr->next;
	}
}
struct Graph* readgraph(int n, int m){
	struct Graph* graph = createGraph(n,m);
    
	cout<<"+++ Reading edges"<<endl;
	int src,dst;
	for(int i=0;i<m;i++){
		cin>>src;cin>>dst;
		addEdge(graph, src, dst, 1);
	}
	cout<<endl;
	cout<<"+++ The generated graph"<<endl;
	for(int i=0;i<n;i++){
		cout<<i<<" -> ";
		readEdge(graph,i);
		cout<<endl;
	}
	cout<<"+++ Reading edge weights"<<endl;
	cout<<"enter only edge weights one by one"<<endl;
	float wt;
	for(int i=0;i<n;i++){
		struct AdjListNode* ptr=graph->array[i].head;
		while(ptr!=NULL){
			cin>>wt;
			ptr->weight=wt;
			ptr=ptr->next;
		}
	}
	
	for(int i=0;i<n;i++){
		struct AdjListNode* ptr=graph->array[i].head;
		while(ptr!=NULL){
			cout<<" edge "<<i<< " to "<<ptr->dest<<" : "<<ptr->weight<<endl;
			ptr=ptr->next;
			
		}
		
	}
	cout<<"+++ Reading vertex weights"<<endl;
	cout<<"enter only vertex weights one by one";
	float vt;
	for(int i=0;i<n;i++){
		cin>>vt;
		graph->array[i].vwt=vt;
	}
	for(int i=0;i<n;i++){
		cout<<"vertex "<<i<<" : "<<graph->array[i].vwt;
		cout<<endl;
	}
	return graph;
} 

struct MinHeapNode
{
    int  v;
    float dist;
};
 
// Structure to represent a min heap
struct MinHeap
{
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array;
};
 
struct MinHeapNode* newMinHeapNode(int v, float dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}
 
struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;
 
    if (smallest != idx)
    {
        
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];
 
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;
 
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
 
        minHeapify(minHeap, smallest);
    }
}
 

int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;
 
    struct MinHeapNode* root = minHeap->array[0];
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 

void decreaseKey(struct MinHeap* minHeap, int v, float dist)
{
 
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;
    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist)
    {
        minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
 
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
   if (minHeap->pos[v] < minHeap->size)
     return true;
   return false;
}
 
void printArr(int dist[], int n)
{
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

void dijkstra(struct Graph* graph,int n, int src, int dest)
{
    int V = graph->V;// Get the number of vertices in graph
    float dist[V];      // dist values used to pick minimum weight edge in cut
 
    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(V);
 
    // Initialize min heap with all vertices. dist value of all vertices 
    for (int v = 0; v < V; ++v)
    {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }
 
    // Make dist value of src vertex as 0 so that it is extracted first
    minHeap->array[src] = newMinHeapNode(src, dist[src]);
    minHeap->pos[src]   = src;
    dist[src] = 0;
    decreaseKey(minHeap, src, dist[src]);

    minHeap->size = V;
 
   
    while (!isEmpty(minHeap))
    {
        
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; 
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL)
        {
            int v = pCrawl->dest;
            if (isInMinHeap(minHeap, v) && dist[u] != INT_MAX && 
                                          pCrawl->weight + dist[u] < dist[v])
            {
                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
        if(u==dest)break;
    }
    printf("+++ Running Dijkstra on the original graph\n");
    printf("--- Shortest (0,4) distance is ");
    printf("%f",dist[dest]);
    printf("\n");
}

int main() {
  int n,m;
  printf("Enter n\n"); cin>>n;
  cout<<"enter m"<<endl; cin>>m;
  struct Graph* graph= readgraph(n,m);
  int s=0;
  int t=n-1;
  cout<<"+++ Running Dijkstra on the original graph"<<endl;
  dijkstra(graph,n,s,t);
  float wt;
  for(int i=0;i<n;i++){
		struct AdjListNode* ptr=graph->array[i].head;
		while(ptr!=NULL){
			cout<<" edge weight"<<i<< " to "<<ptr->dest<<" changes from "<<ptr->weight<<" to "<< abs(log(ptr->weight))<<endl;
			ptr=ptr->next;
			
		}
		
	}
	for(int i=0;i<n;i++){
		struct AdjListNode* ptr=graph->array[i].head;
		while(ptr!=NULL){
			wt=abs(log(ptr->weight));
			ptr->weight=wt;
			ptr=ptr->next;
		}
	}
	cout<<"+++ Running Dijkstra on the log-converted graph"<<endl;
	dijkstra(graph,n,s,t);
	
}


