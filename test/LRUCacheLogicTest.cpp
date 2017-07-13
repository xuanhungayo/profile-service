/* 
 * File:   LRUCacheLogicTest.cpp
 * Author: xuanhungcao
 *
 * Created on June 22, 2017, 1:40 PM
 */

#include <stdlib.h>
#include <assert.h>
#include <iostream>

#include "LRUCache.h"
#include "ProfileService.h"

using namespace profile;
using namespace service::cache;

void BasicTest() {
	const int32_t CAPACITY = 2;

	LRUCache<int32_t, UserProfile> cache(CAPACITY);
	UserProfile user1, user2;
	user1.id = 1;
	user1.name = "A";
	user2.id = 2;
	user2.name = "B";

	cache.set(1, user1);
	cache.set(2, user2);
	assert(cache.get(1)->name == "A");
	assert(cache.get(2)->name == "B");
	cache.remove(1);
	assert(cache.contain(1) == false);
	assert(cache.contain(2) == true);
	
	user2.name = "C";
	cache.set(2, user2);
	assert(cache.get(2)->name == "C");
}

void SimpleSmallTest() {
	const int32_t CAPACITY = 2;
	const int32_t N = 5;

	LRUCache<int32_t, UserProfile> cache(CAPACITY);
	UserProfile users[N + 1];
	for (int i = 1; i <= N; i++) 
		users[i].id = i;


	cache.set(1, users[1]);
	cache.set(2, users[2]);
	assert(cache.contain(3) == false);
	assert(cache.get(1)->id == 1);
	cache.set(3, users[3]);
	assert(cache.contain(2) == false);
	assert(cache.get(3)->id == 3);
	cache.remove(3);
	assert(cache.contain(3) == false);
}

void BigTest() {
	const int32_t CAPACITY = 100000;
	const int32_t EVICT = 100;
	const int32_t N = CAPACITY + EVICT;

	LRUCache<int32_t, UserProfile> cache(CAPACITY);
	UserProfile users[N + 1];
	for (int i = 1; i <= N; i++) 
		users[i].id = i;
	
	for(int i = 1; i <= N; i++) 
		cache.set(i, users[i]);
	for(int i = 1; i <= EVICT; i++) 
		assert(cache.contain(i) == false);
	assert(cache.get(1000)->id == 1000);
	
	// Test cache dumping
//	cache.writeToBinaryFile("cache.bin");
//	cache.clear();
//	cache.readFromBinaryFile("cache.bin");
//	assert(cache.get(101)-> id == 101);
//	assert(cache.get(1000)-> id == 1000);
}

int main(int argc, char** argv) {
	std::cout << "%SUITE_STARTING% LogicTest" << std::endl;
	std::cout << "%SUITE_STARTED%" << std::endl;
	
	std::cout << "%TEST_STARTED% BasicTest (LogicTest)" << std::endl;
	BasicTest();
	std::cout << "%TEST_FINISHED% time=0 BasicTest (LogicTest)" << std::endl;
	
	std::cout << "%TEST_STARTED% SimpleSmallTest (LogicTest)" << std::endl;
	SimpleSmallTest();
	std::cout << "%TEST_FINISHED% time=0 SimpleSmallTest (LogicTest)" << std::endl;
	
	std::cout << "%TEST_STARTED% BigTest (LogicTest)" << std::endl;
	BigTest();
	std::cout << "%TEST_FINISHED% time=0 BigTest (LogicTest)" << std::endl;
	
	std::cout << "%SUITE_FINISHED% time=0" << std::endl;
	return (EXIT_SUCCESS);
}

