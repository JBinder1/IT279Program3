// Implementation file for AVL search tree

#include "Dictionary.h"

#include <queue>

#define MIN_CAPACITY 19
int capacity = MIN_CAPACITY;

enum EntryType {Legitimate, Empty, Deleted};

struct HashNode{
    string data;
    enum EntryType info;
};

struct HashTable{
    int capacity;
    int size;
    HashNode *table;
};

HashTable *htable;

HashTable * initializeTable(int capacity){
    if(htable != NULL)
        delete htable;
    if(capacity < MIN_CAPACITY){
        cout<<"Table capacity too small.\n";
        return NULL;
    }
    htable = new HashTable;
    if(htable == NULL){
        cout<<"Out of space.\n";
        return NULL;
    }
    htable->capacity = capacity;
    htable->table = new HashNode[htable->capacity];
    if(htable->table == NULL){
        cout<<"Table capacity too small.\n";
        return NULL;
    }
    for(int i = 0; i < htable->capacity; i++){
        htable->table[i].info = Empty;
        htable->table[i].data = "";
    }
    htable->size = 0;
    cout<<"htable size initialized to size: "<<htable->size<<" and capacity: "<<htable->capacity<<endl;
    return htable;
}

Dictionary::Dictionary(){
    initializeTable(MIN_CAPACITY);
}

Dictionary::Dictionary(const Dictionary& orig){
  this->copyDict(orig);
}

Dictionary::~Dictionary(){
  this->deleteDict();
}

Dictionary& Dictionary::operator=(const Dictionary& orig){
    this->copyDict(orig);
}

unsigned int hashFunction(const string & key, int tableSize){
    unsigned int hashVal = 0;
    
    for(char ch : key){
        hashVal = 37 * hashVal + ch;
    }
    unsigned int ans = hashVal % tableSize;
    cout<<key<<" hash function = "<<ans<<endl;
    return ans;
}

bool isPrime(int n){
    if(n == 2 || n == 3)
        return true;
    if(n % 2 == 0 || n % 3 == 0)
        return false;
    int divisor = 6;
    while(divisor * divisor - 2 * divisor + 1 <= n){
        if(n % (divisor - 1) == 0)
            return false;
        if(n % (divisor + 1) == 0)
            return false;
        divisor += 6;
    }
    return true;
}

int nextPrime(int prime){
    prime *= 2;
    while(!isPrime(++prime)){}
    return prime;
}

HashTable * Rehash(HashTable * htable);

void Insert(string anEntry){
    int collisions = 0;
    bool added = false;
    while(!added){
        unsigned int temp = hashFunction(anEntry, htable->capacity);
        int pos = (temp + collisions * collisions) % htable->capacity;
        cout<<anEntry<<" placed at position "<<pos<<endl<<endl;
        if(htable->table[pos].info == Legitimate){
            collisions++;
        }else{
            htable->table[pos].info = Legitimate;
            htable->table[pos].data = anEntry;
            added = true;
        }
    }
    htable->size = htable->size + 1;
    cout<<"# of elements in htable: "<<htable->size<<endl;
}

void Dictionary::AddEntry(string anEntry){
    double tempSize = htable->size;
    double tempCapacity = htable->capacity;
    double load = tempSize / tempCapacity;
    cout<<"Load: "<<load<<endl;
    if(load >= .5)
        Rehash(htable);
    
    Insert(anEntry);
}

HashTable * Rehash(HashTable * htable){
    cout<<"Rehash called."<<endl;
    HashNode * table = htable->table;
    cout<<"Next prime: "<<nextPrime(htable->capacity)<<endl;
    htable = initializeTable(nextPrime(htable->capacity));
    for(int i = 0; i < htable->capacity; i++){
        if(table[i].info == Legitimate)
            Insert(table[i].data);
    }
    free(table);
    return htable;
    cout<<"Rehash finished. New table capacity: "<<htable->capacity<<endl;
}

bool Dictionary::FindEntry(string key){
    for(int i = 0; i < htable->capacity; i++){
        if(htable->table[i].info == Legitimate && htable->table[i].data == key)
            return true;
    }
    return false;
}

void Dictionary::PrintSorted(ostream& outStream){
  
}

void Dictionary::copyDict(const Dictionary& orig){
  
}

void Dictionary:: deleteDict(){
    
}

