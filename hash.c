#include "hash.h"


/**
* @input - A number of buckets, the size to make the hash table.
* Should assign space for the hash_struct pointer, all buckets, and should
* initialize all entries as KEY = -1, VALUE = -1 to begin.
* 
*/

hash_struct* initTable(int num_of_buckets){
  int i;
  data_entry null_entry = {-1, -1}; //this will be copied into each bucket
  hash_struct* hshtab = (hash_struct*) malloc(sizeof(hash_struct)); //allocate memory for hashtable
  hshtab->num_of_buckets = num_of_buckets;
  //allocate memory for all the empty buckets
  hshtab->buckets = (data_entry**) malloc(num_of_buckets*sizeof(data_entry*));
  //allocate memory for all the null buckets
  for (i = 0; i < num_of_buckets; i++) {
    hshtab->buckets[i] = (data_entry*) malloc(sizeof(null_entry));
    memcpy(hshtab->buckets[i], &null_entry, sizeof(null_entry));
  }
  return hshtab;
}


/*
* @input : Some key value.   
* @returns : The key value modulated by the size of the hash table.
*/

int hashcode(hash_struct* table, int key){
  if (key >= 0) {
    return key % table->num_of_buckets;
  } else {
    return table->num_of_buckets + key % table->num_of_buckets;
  }
 
}

/*
* @input : Some key value, table pointer.
* @returns : The data entry if some matching (key, value) pair exists, otherwise returns NULL.
*/
data_entry* get(hash_struct* table, int key){
	int i = hashcode(table, key);
  data_entry* entry = table->buckets[i];
	//first check in O(1)
  if (entry->key == key) {
    return entry;
  }
	//check in O(n)
	if (!contains(table, key)) {
		return NULL;
	}
	//check in O(n)
  for (i = (i+1) % table->num_of_buckets ; i != hashcode(table, key) ; i = (i+1) % table->num_of_buckets) {
		if (table->buckets[i]->key == key) {
			return table->buckets[i];
		}
  }
	//worse case
	return NULL;
}

/*
* @input : Some key value, table pointer.
* @returns : True only if a valid key exists that maps to this value.
*/
bool contains(hash_struct* table, int key){
  int i = hashcode(table, key);
  data_entry* entry = table->buckets[i];
	//first check in O(1)
  if (entry->key == key) {
    return true;
  }
	//check in O(n)
  for (i = (i+1) % table->num_of_buckets ; i != hashcode(table, key) ; i = (i+1) % table->num_of_buckets) {
    if (table->buckets[i]->key == key) {
      return true;
    }
  }
	//worse case
  return false;
}

/*
* @input : Some key integer.
* @input : Some value,.
* @returns : void. Places (key, value) pairing into map.
* Replaces value if another pairing with this key already exists.
* Do nothing if the table is full!
*/
void put(hash_struct* table, int key, int value){
	int i = hashcode(table, key);
  data_entry* entry = table->buckets[i];
	//if key already exists at bucket or bucket is empty, add pairing in O(1)
  if (entry->key == key || entry->key == -1) {
		entry->key = key;
		entry->value = value;
    return;
  }
	//check if the table is full before probing for an insertion
	if (isFull(table)) {
		return;
	}
  for (i = (i+1) % table->num_of_buckets ; i != hashcode(table, key) ; i = (i+1) % table->num_of_buckets) {
    if (table->buckets[i]->key == -1 || table->buckets[i]->key == key) {
      table->buckets[i]->key = key;
			table->buckets[i]->value = value;
			return;
    }
  }
}

/*
* @returns : The number of valid (key, value) pairings in the table.
*/
int size(hash_struct* table){
	int i;
	int s = 0;
	for (i = 0; i < table->num_of_buckets; i++) {
		if (table->buckets[i]->key != -1) {
			s = s + 1;
		}
	}
	return s;
}

/*
* Iterates through the table and resets all entries.
*/
void clear(hash_struct* table){
	int i;
	for (i = 0; i < table->num_of_buckets; i++) {
    if (table->buckets[i]->key != -1) {
      table->buckets[i]->key = -1;
      table->buckets[i]->value = -1;
    }
	}
}

/*
* @returns : true, only if the table contains 0 valid (key, value) pairings.
*/
bool isEmpty(hash_struct* table){
	return (size(table) == 0);
}


/*
* @returns : true, only when the table is filled entirely with VALID values.
*/
bool isFull(hash_struct* table){
	return (size(table) == table->num_of_buckets);
}


/*
* @input : Some key value.
* @returns : void. if a pair exists for this key, reinitialize this entry.
*/
void removeEntry(hash_struct* table, int key){
	int i = hashcode(table, key);
  data_entry* entry = table->buckets[i];
	//first check in O(1)
  if (entry->key == key) {
		entry->key = -1;
		entry->value = -1;
    return;
  }
	//check in O(n)
	if (!contains(table, key)) {
		return;
	}
	//check in O(n)
  for (i = (i+1) % table->num_of_buckets ; i != hashcode(table, key) ; i = (i+1) % table->num_of_buckets) {
		if (table->buckets[i]->key == key) {
			table->buckets[i]->key = -1;
			table->buckets[i]->value = -1;
			return;
		}
  }
}


/*
* Debugging function.
* Iterates through the hashTable and prints all NON-NULL (key, value) pairings.
* Print statement should be of the form "(key1, value1), (key2, value2), ...."
*/
void printEntries(hash_struct* table){
	int i;
	for (i = 0; i < table->num_of_buckets; i++) {
		if (table->buckets[i]->key == -1) {
			continue;
		} 
		printf("INDEX: %d, KEY: %d, VALUE: %d\n", i, table->buckets[i]->key, table->buckets[i]->value);
	}
}

/*
* Debugging function.
* Iterates though the hashTable and prints ALL entries in order.
* If a value is not valid, you will print "EMPTY" for the value.
* Entry print Format: "(INDEX: tableIndex, KEY: key, VALUE: value)"
* Example :  "(INDEX: 0, KEY: 0, VALUE: 3), (INDEX: 1, KEY: EMPTY, VALUE: EMPTY), (INDEX: 2, KEY: 2, VALUE: 49), ..."
*/
void printFullTable(hash_struct* table){
	int i;
	for (i = 0; i < table->num_of_buckets; i++) {
		if (table->buckets[i]->key == -1) {
			printf("INDEX: %d, KEY: EMPTY, VALUE: EMPTY\n", i);
		} else {
			printf("INDEX: %d, KEY: %d, VALUE: %d\n", i, table->buckets[i]->key, table->buckets[i]->value);
		}
	}
}


/**
* Should free all space consumed by the hash table.
*/
void done(hash_struct* table){
  int i;
  for (i = 0; i < table->num_of_buckets; i++) {
    free(table->buckets[i]);
  }
  free(table->buckets);
  free(table);
}