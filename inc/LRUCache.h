/* 
 * File:   LRUCache.h
 * Author: xuanhungcao
 *
 * Created on June 21, 2017, 5:14 PM
 */

#ifndef LRUCACHE_H
#define LRUCACHE_H

#include "MemoryCache.h"

#include <iostream>
#include <fstream>
#include <list>
#include <unordered_map>
#include <utility>
#include <mutex>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

using namespace std;

template<class Key, class Value>
class LRUCache : public MemoryCache<Key, Value> {
public:
	typedef list<Key> list_type;
	typedef pair<Value, typename list_type::iterator> pair_type;
	typedef unordered_map<Key, pair_type> map_type;

	LRUCache(const int _capacity) : MemoryCache<Key, Value>(_capacity) {
	}

	bool contain(const Key& key) {
		std::lock_guard<std::mutex> lock(mtx);
		return (hash_map.find(key) != hash_map.end());
	}

	boost::optional<Value> get(const Key& key) override {
		std::lock_guard<std::mutex> lock(mtx);
		typename map_type::iterator it = hash_map.find(key);
		if (it != hash_map.end()) {
			Value& value = (*it).second.first;
			update(key, (*it).second);
			return value;
		} else
			return boost::optional<Value>();
	}

	void set(const Key& key, const Value& value) override {
		std::lock_guard<std::mutex> lock(mtx);
		typename map_type::iterator it = hash_map.find(key);
		if (it == hash_map.end() && hash_map.size() < this->capacity) {
			add(key, value);
			return;
		}
		if (it == hash_map.end() && hash_map.size() == this->capacity) {
			remove();
			add(key, value);
			return;
		}
		(*it).second.first = value;
		update(key, (*it).second);
	}

	void remove(const Key& key) override {
		std::lock_guard<std::mutex> lock(mtx);
		typename map_type::iterator it = hash_map.find(key);
		if (it != hash_map.end()) {
			typename list_type::iterator pos = (*it).second.second;
			queue.erase(pos);
			hash_map.erase(key);
		}
	}
	
	void write(const std::string& filename) {
		std::lock_guard<std::mutex> lock(mtx);
		std::ofstream ofs(filename.c_str());
		boost::archive::binary_oarchive oa(ofs);
		
		oa << int32_t(queue.size());
		for(auto it = queue.rbegin(); it != queue.rend(); it++) {
			oa << (*it);
			oa << hash_map[*it].first;
		}
	}
	
	void read(const std::string& filename) {
		std::lock_guard<std::mutex> lock(mtx);
		std::ifstream ifs(filename.c_str());
		boost::archive::binary_iarchive ia(ifs);
		
		int32_t _size;
		Key key; Value value;
		ia >> _size;
		for(int i = 1; i <= _size; i++) {
			ia >> key;
			ia >> value;
			add(key, value);
		}
	}

	void clear() {
		std::lock_guard<std::mutex> lock(mtx);
		queue.clear();
		hash_map.clear();
	}

	virtual ~LRUCache() {
		clear();
	};

private:
	map_type hash_map;
	list_type queue;
	mutex mtx;

	void add(const Key& key, const Value& value) {
		queue.push_front(key);
		hash_map[key] = make_pair(value, queue.begin());
	}

	void remove() {
		Key key = queue.back();
		hash_map.erase(key);
		queue.pop_back();
	}

	void update(const Key& key, const pair_type& info) {
		typename list_type::iterator pos = info.second;
		queue.erase(pos);
		queue.push_front(key);
		hash_map[key] = make_pair(info.first, queue.begin());
	}
};

#endif /* LRUCACHE_H */

