#include<iostream>
using namespace std;

/*struct Vertex{
	char *name;
	int estimatedDistance;
}

struct Edge{
	Vertex *from;
	Vertex *to;
	int weight;
}*/

struct Node{
	int num;
	Node *next;
};

class Queue{
	Node *front;
	Node *rear;

	public:
	Queue(){
		front = NULL;
		rear = front;
	}

	void addElement(int i){
		Node *temp = new Node;
		temp->num = i;
		temp->next = NULL;
		if (front == NULL){
			front = temp;
			rear = front;
		}
		else{
			temp->next = rear;
			rear = temp;
		}
	}

	bool isEmpty(){
		if (front == NULL)
			return true;
		else
			return false;
	}

	void printQueue(){
		Node *ptr = rear;
		cout<<"Queue: ";
		while (ptr!=NULL){
			cout<<ptr->num+1;
			ptr = ptr->next;
		}
		cout<<endl;
	}

	int deQueue(){
		Node *ptr = rear;
		if (front == rear){
			int popped = front->num;
			front = NULL;
			rear = front;
			return popped;
		}
		Node *previous;
		while (ptr->next!=NULL){
			previous = ptr;
			ptr = ptr->next;
		}
		front = previous;
		front->next = NULL;
		int popped = ptr->num;
		delete ptr;
		return popped;
	}
};

enum states {WHITE, GRAY, BLACK};

class MyGraph{
	int V;
	int **adjacencyMatrix;
	states *visited;

	public:
		MyGraph(int vertexCount){
			V = vertexCount;
			adjacencyMatrix = new int*[V];
			visited = new states[V];
			for (int i=0; i<V; i++){
				adjacencyMatrix[i] = new int[V];
				visited[i] = WHITE;
				for (int j=0;j<V;j++){
					adjacencyMatrix[i][j] = 0;
				}
			}
		}
		
		void addEdge(int i, int j, int weight){
			adjacencyMatrix[i][j] = weight;
			adjacencyMatrix[j][i] = weight;
		}

		void removeEdge(int i, int j){
			adjacencyMatrix[i][j] = 0;
			adjacencyMatrix[j][i] = 0;
		}

		bool isEdge(int i, int j){
			if (adjacencyMatrix[i][j])
				return true;
			else
				return false;
		}

		void dfs(int i){
			visited[i] = GRAY;
			for (int j=0; j<V; j++){
				if (visited[j] == WHITE && isEdge(i, j)) 
					dfs(j);
			}
			cout<<i+1<<endl;
			visited[i] = BLACK;
		}
		
		void bfs(int i){
			Queue queue;
			if (visited[i] == WHITE){
				queue.addElement(i);
			}
			visited[i]=BLACK;
			while (!queue.isEmpty()){
				queue.printQueue();
				int popped = queue.deQueue();
				cout<<popped+1<<endl;
				for (int j=0; j<V; j++){
					if (isEdge(popped,j) && visited[j]==WHITE){
						visited[j] = BLACK;
						queue.addElement(j);
					}
				}
			}
		}

		void djikstra(int i){
			Queue q;
			int minDistance[V];
			for (int j=0; j<V; j++){
				minDistance[j] = -999;
			}
			minDistance[i] = 0;
			q.addElement(i);
			while (!q.isEmpty()){
				int popped = q.deQueue();
				for (int j=0; j<V; j++){
					if (isEdge(popped, j)){
						if (minDistance[j] == -999)
							minDistance[j] = minDistance[popped] + adjacencyMatrix[popped][j];
						else{
							int tempMinDistance = minDistance[popped] + adjacencyMatrix[popped][j];
							if (tempMinDistance < minDistance[j]){
								minDistance[j] = tempMinDistance;
							}
						}
					}
					if (visited[j]==WHITE){
						q.addElement(j);
						visited[j] = BLACK;
					}
				}
				printArray(minDistance, V);
			}
		}

		void printArray(int array[], int len){
		        for (int j=0;j<len;j++){
                		cout<<j+1<<":"<<array[j]<<" ,  ";
        		}
        		cout<<endl;
		}
		
		void printGraph(){
			for (int i=0;i<V;i++){
				for (int j=0;j<V;j++){
					cout<<adjacencyMatrix[i][j]<<"   ";
				}
				cout<<endl;
			}
		}

		void reIntVisited(){
			for (int i=0; i<V; i++){
				visited[i] = WHITE;
			}
		}
};

int main(void){
	int vertexCount = 0;
	cout<<"Enter the number of vertices"<<endl;
	cin>>vertexCount;
	MyGraph g(vertexCount);
	g.addEdge(0,3,1);
	g.addEdge(3,1,1);
	g.addEdge(3,4,1);
	g.addEdge(2,4,1);
	g.addEdge(1,4,1);
	g.printGraph();
	cout<<"DFS:"<<endl;
	g.dfs(0);
	MyGraph g1(8);
	//g.reIntVisited();
	g1.addEdge(0,1,1);
	g1.addEdge(0,2,1);
	g1.addEdge(1,3,1);
	g1.addEdge(1,4,1);
	g1.addEdge(2,5,1);
	g1.addEdge(2,6,1);
	g1.addEdge(4,7,1);
	cout<<"BFS:"<<endl;
	g1.bfs(0);
	MyGraph g2(6);
	g2.addEdge(0,1,7);
	g2.addEdge(0,2,9);
	g2.addEdge(0,5,14);
	g2.addEdge(1,2,10);
	g2.addEdge(1,3,15);
	g2.addEdge(2,3,11);
	g2.addEdge(2,5,2);
	g2.addEdge(5,4,9);
	g2.addEdge(3,4,6);
	g2.printGraph();
	g2.djikstra(5);
}
