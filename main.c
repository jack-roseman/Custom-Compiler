#include "hash.h"

#include <stdbool.h>
#include <assert.h>

/**
 * This file is to check list.h and list.c for part I of the assignment only
 *
 * Do not include it in the submission of part II
 *
 * You are expected to add additional test cases to this file
 * and to run valgrind on the program once you have it working
 */

//Tests that the hashcode function works
bool basicHashcode(hash_struct* table){


    if (hashcode(table, 7) == 7 && hashcode(table, 107) == 7){
        return true;
    } else {
        return false;
    }

}


//tests that an empty list has size == 0
bool testBasicEmpty(hash_struct* table){

    clear(table);

    if (isEmpty(table) == true){
        return true;
    } return false;

}

bool testBasicFill(hash_struct* table){
	int i;
	for (i = 0; i < table->num_of_buckets; i++) {
		put(table, i, i);
	}

	if (isFull(table) == true){
			return true;
	} return false;
}

bool testPutContains(hash_struct* table){
	int i;
	clear(table);
	put(table, 1, 23);
	put(table, 101, 2);
	put(table, 201, 6);
	put(table, 2, 5);
	
	if (contains(table, 1) && contains(table, 101) && contains(table, 201) && contains(table, 2)){
			return true;
	} return false;
}

bool testPutGet(hash_struct* table){
	int i;
	clear(table);
	put(table, 1, 23);
	put(table, 101, 2);
	put(table, 201, 6);
	put(table, 2, 5);
	
	data_entry* v1 = get(table, 1);
 	data_entry* v2 = get(table, 101);
 	data_entry* v3 = get(table, 201);
 	data_entry* v4 = get(table, 2);
	if ( ((v1->key == 1  ) && (v1->value == 23)) &&
			 ((v2->key == 101) && (v2->value == 2 )) && 
		   ((v3->key == 201) && (v3->value == 6 )) &&
			 ((v4->key == 2  ) && (v4->value == 5 ))   ){
			return true;
	} return false;
}

bool testSize(hash_struct* table){
	int i;
	clear(table);
	put(table, 1, 23);
	put(table, 101, 2);
	put(table, 201, 6);
	put(table, 2, 5);

	if ( size(table) == 4 ){
			return true;
	} return false;
}

bool testPutRemoveEntry(hash_struct* table){
	int i;
	int s1;
	clear(table);
	put(table, 1, 23);
	put(table, 101, 2);
	put(table, 201, 6);
	put(table, 2, 5);
	
	s1 = size(table);
	
	removeEntry(table, 101);
	removeEntry(table, 201);
	removeEntry(table, 1);
	removeEntry(table, 2);
	if (s1 == 4 && isEmpty(table) ){
			return true;
	} return false;
}

bool testUpdateEntry(hash_struct* table){
	int i;
	int s1;
	clear(table);
	put(table, 1, 23);
	put(table, 101, 2);
	put(table, 1, 6);
	put(table, 101, 5);
  data_entry* v1 = get(table, 1);
  data_entry* v2 = get(table, 101);
	if ((v1->value == 6) && (v2->value == 5)){
			return true;
	} return false;
}

int main() {
	printf ("Creating table\n") ;
	hash_struct* my_table = initTable(100) ;

	if (basicHashcode(my_table) == true){
		printf("%s\n", "Passed Test 1 : basicHashcode()");
	} else {
		printf("%s\n", "Failed Test 1 : basicHashcode()");
	}

	if (testBasicEmpty(my_table) == true){
		printf("%s\n", "Passed Test 2 : testBasicEmpty()");
	} else {
		printf("%s\n", "Failed Test 2 : testBasicEmpty()");
	}

	//-------------------YOU CAN ADD YOUR OWN TESTS HERE---------

	if (testBasicFill(my_table) == true){
			printf("%s\n", "Passed Test 3 : testBasicFill()");
	} else {
			printf("%s\n", "Failed Test 3 : testBasicFill()");
	}

	if (testPutContains(my_table) == true){
			printf("%s\n", "Passed Test 4 : testPutContains()");
	} else {
			printf("%s\n", "Failed Test 4 : testPutContains()");
	}

	if (testPutGet(my_table) == true){
			printf("%s\n", "Passed Test 5 : testPutGet()");
	} else {
			printf("%s\n", "Failed Test 5 : testPutGet()");
	}
	
	if (testSize(my_table) == true){
			printf("%s\n", "Passed Test 6 : testSize()");
	} else {
			printf("%s\n", "Failed Test 6 : testSize()");
	}
	if (testPutRemoveEntry(my_table) == true){
			printf("%s\n", "Passed Test 7 : testPutRemoveEntry()");
	} else {
			printf("%s\n", "Failed Test 7 : testPutRemoveEntry()");
	}
  if (testUpdateEntry(my_table) == true){
			printf("%s\n", "Passed Test 8 : testUpdateEntry()");
	} else {
			printf("%s\n", "Failed Test 8 : testUpdateEntry()");
	}
  
	//-------------------------------------------------


	printf ("freeing table\n") ;
	done(my_table) ;



	return 0;

}
