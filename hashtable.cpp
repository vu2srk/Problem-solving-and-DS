#include<iostream>
using namespace std;

const int TABLE_SIZE = 128;

struct HashNode{
	int key;
	char *value;
};

class HashTable{
	HashNode *table[TABLE_SIZE];
	
	public:
	HashTable(){
		for (int i=0; i<TABLE_SIZE; i++){
			table[i] = NULL;
		}
	}

	char* get(int key){
		int hash = key % TABLE_SIZE;
		if (table[hash] == NULL)
			return NULL;
		else
			return table[hash]->value;		
	}

	void put(int key, char *value){
		int hash = key % TABLE_SIZE;
		HashNode *newNode = new HashNode;
		newNode->key = key;
		newNode->value = value;
		if (get(key) == NULL){
			table[hash] = newNode;
		}
		else 
		{
			cout<<"Hash occupied";
			return;
		}
	}
};

int main(void){
	HashTable hashTable;
	char *value = "Sharadha";
	hashTable.put(1, value);
	cout<<hashTable.get(1);
}
