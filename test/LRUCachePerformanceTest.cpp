/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   PerformanceTest.cpp
 * Author: xuanhungcao
 *
 * Created on June 22, 2017, 2:55 PM
 */

#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <typeinfo>

#include <boost/optional.hpp>

#include "LRUCache.h"
#include "ProfileService.h"

#define RAND rand()% 10000 * rand() % 10000 + 1

using namespace profile;
using namespace service::cache;

const int32_t REQUEST_NUM = 1000000;

void TestPutSmallCapacity() {
	const int32_t CAPACITY = 2;
	const int32_t N = 100;

	LRUCache<int32_t, UserProfile> cache(CAPACITY);
	UserProfile users[N + 1];
	for (int i = 1; i <= N; i++) {
		users[i].id = RAND;
		users[i].age = rand() % 100 + 1;
		users[i].name = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
	}
	
	for (int i = 1; i <= REQUEST_NUM; i++) {
		int32_t num = rand() % N + 1;
		cache.set(users[num].id, users[num]);
	}
}

void TestPutMediumCapacity() {
	const int32_t CAPACITY = 1000;
	const int32_t N = 100;

	LRUCache<int32_t, UserProfile> cache(CAPACITY);
	UserProfile users[N + 1];
	for (int i = 1; i <= N; i++) {
		users[i].id = RAND;
		users[i].age = rand() % 100 + 1;
		users[i].name = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
	}
	
	for (int i = 1; i <= REQUEST_NUM; i++) {
		int32_t num = rand() % N + 1;
		cache.set(users[num].id, users[num]);
	}
}

void TestRandomBigCapacity() {
	const int32_t CAPACITY = 10000;
	const int32_t N = 1000;

	LRUCache<int32_t, UserProfile> cache(CAPACITY);
	UserProfile users[N + 1];
	for (int i = 1; i <= N; i++) {
		users[i].id = RAND;
		users[i].age = rand() % 100 + 1;
		users[i].name = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZ";
	}
	
	for (int i = 1; i <= REQUEST_NUM; i++) {
		int req_type = rand() % 2;
		int32_t num = rand() % N + 1;
		switch (req_type) {
			case 0:
			cache.set(users[num].id, users[num]);
			case 1:
				if (cache.contain(users[num].id)) {
					const UserProfile& someone = *cache.get(users[num].id);
					//boost::optional<UserProfile> profile = cache.get(users[num].id);
					//UserProfile& someone = *profile;
				}
		}
	}
}


int main(int argc, char** argv) {
	srand(time(NULL));	
	clock_t begin, end;
	double time;
	std::cout << "Performance Test started:" << std::endl;
	
	begin = clock();
	TestPutSmallCapacity();
	end = clock();
	time = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "-- TestPutSmallCapacity finished, performance = " << std::fixed 
			<< int(REQUEST_NUM / time) << " request per second" << std::endl; 
	
	begin = clock();
	TestPutMediumCapacity();
	end = clock();
	time = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "-- TestPutMediumCapacity finished, performance = " << std::fixed 
			<< int(REQUEST_NUM / time) << " request per second" << std::endl; 
	
	begin = clock();
	TestRandomBigCapacity();
	end = clock();
	time = double(end - begin) / CLOCKS_PER_SEC;
	std::cout << "-- TestRandomBigCapacity finished, performance = " << std::fixed 
			<< int(REQUEST_NUM / time) << " request per second" << std::endl;
	
	return (EXIT_SUCCESS);
}

