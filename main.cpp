#include <iostream>
#include <array>
#include <fstream>
#include <cctype>

using namespace std;

const int HASH = 61;

struct node{
	string data;
	node* next = NULL;
};

struct node* bucketArray[HASH];

int hashFun(string str) {  
	int hashVal;
	for(int i = 0; i < str.size(); i++)
	{
		hashVal = (hashVal << 2) + str[i];
	}
		return hashVal % HASH;
}

/*long long SPMHash(string str) {
	int p = 31;
	int m = 1e9 +9;
	long long powerP = 1;
	long long hashVal = 0;

	for (int i = 0; i < str.length(); i++) {
		hashVal = (hashVal + (str[i] - 'a' + 1) * powerP) % m;
		powerP = (powerP * p) % m;
	}

	return (hashVal % m + m) % m;
}*/

void insert(string newData) {
	struct node* newNode = new node;
	newNode -> data = newData;
	newNode -> next = bucketArray[hashFun(newData) % HASH];
	bucketArray[hashFun(newData) % HASH] = newNode;
}

bool find(string target) {
	struct node* temp;
	int x = hashFun(target) % HASH;
   	temp = bucketArray[x];
   	if(bucketArray[x] == NULL){
     	return false;
   	}
   	else if(bucketArray[x] ->data == target){
     	cout << bucketArray[x] -> data;
		cout << " found at index " << x << ".\n1 element inspected" << endl;
     	return true;
   	}
   	else{
		int count = 1;
		while (temp != NULL) {
			if(temp -> data == target){
				cout << temp -> data;
				cout << " found at index " << x << endl << count << " elements inspected" << endl;
				return true;
			}
			temp = temp -> next;
			count++;
		}
		return false;
   	}
}

void display(){
	struct node* temp;
	for(int i = 0;i < HASH; i++){
		int x = i % HASH;
		cout << x << ": ";
		temp = bucketArray[x];
		while(temp != NULL){
			cout << "{ " << temp -> data << " } ";
			temp = temp -> next;
		}
		cout << endl;
	}
}

int main() {
  	
	string words[60] = {""};

	ifstream file("text.txt");
	string str;

	int j = 0;
	while (file>>str) {
		for (int i=0; i<str.size(); i++) {
			if (str[i] < 'a' || str[i] > 'z') {
				if (str[i] < 'A' || str[i] > 'Z') {
					str.erase(i, 1);
					i--;
				}
				else {
					str[i] = tolower(str[i]);
				}
			}
		}
		words[j] = str;
		j++;
	}
	for (int i = 0; i < 60; i ++) {
		if (find(words[i]) == false) {
			insert(words[i]);
		}
	}
  	display();

	string search;
	while (search != "-1") {
		cout << "Please enter a word to search for in the Hash table(-1 to quit): ";
		cin >> search;
		if (search != "-1" && !find(search)) {
			cout << search << " is not in the bucket" << endl;
		}
	}	
} 