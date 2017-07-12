/* 
 * File:   LRUCache-imp.h
 * Author: xuanhungcao
 *
 * Created on June 21, 2017, 5:14 PM
 */

#ifndef LRUCACHE_IMP_H
#define LRUCACHE_IMP_H

#include <iostream>
#include <fstream>
#include <mutex>

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>

#include "MemoryCache.h"

namespace service {
namespace cache {

template<class Key, class Value>
LRUCache<Key, Value>::LRUCache(const int32_t capacity) : capacity_(capacity) {
}

template<class Key, class Value>
LRUCache<Key, Value>::~LRUCache() {
}

template<class Key, class Value>
bool LRUCache<Key, Value>::contain(const Key& key) {
	std::lock_guard<std::mutex> lock(mutex_);
	return (hashmap_.find(key) != hashmap_.end());
}

template<class Key, class Value>
boost::optional<Value> LRUCache<Key, Value>::get(const Key& key) {
	std::lock_guard<std::mutex> lock(mutex_);
	typename HashMap::iterator it = hashmap_.find(key);
	if (it != hashmap_.end()) {
		Value& value = (*it).second.first;
		update(key, (*it).second);
		return value;
	} else
		return boost::optional<Value>();
}

template<class Key, class Value>
void LRUCache<Key, Value>::set(const Key& key, const Value& value) {
	std::lock_guard<std::mutex> lock(mutex_);
	typename HashMap::iterator it = hashmap_.find(key);
	if (it == hashmap_.end() && hashmap_.size() < capacity_) {
		add(key, value);
		return;
	}
	if (it == hashmap_.end() && hashmap_.size() == capacity_) {
		remove();
		add(key, value);
		return;
	}
	(*it).second.first = value;
	update(key, (*it).second);
}

template<class Key, class Value>
void LRUCache<Key, Value>::remove(const Key& key) {
	std::lock_guard<std::mutex> lock(mutex_);
	typename HashMap::iterator it = hashmap_.find(key);
	if (it != hashmap_.end()) {
		typename List::iterator pos = (*it).second.second;
		queue_.erase(pos);
		hashmap_.erase(key);
	}
}

template<class Key, class Value>
void LRUCache<Key, Value>::writeToBinaryFile(const std::string& filename) {
	std::lock_guard<std::mutex> lock(mutex_);
	std::ofstream ofs(filename.c_str());
	boost::archive::binary_oarchive oa(ofs);

	oa << int32_t(queue_.size());
	for (auto it = queue_.rbegin(); it != queue_.rend(); it++) {
		oa << (*it);
		oa << hashmap_[*it].first;
	}
}

template<class Key, class Value>
void LRUCache<Key, Value>::readFromBinaryFile(const std::string& filename) {
	std::lock_guard<std::mutex> lock(mutex_);
	std::ifstream ifs(filename.c_str());
	boost::archive::binary_iarchive ia(ifs);

	int32_t _size;
	Key key;
	Value value;
	ia >> _size;
	for (int i = 1; i <= _size; i++) {
		ia >> key;
		ia >> value;
		add(key, value);
	}
}

template<class Key, class Value>
void LRUCache<Key, Value>::clear() {
	std::lock_guard<std::mutex> lock(mutex_);
	queue_.clear();
	hashmap_.clear();
}

template<class Key, class Value>
void LRUCache<Key, Value>::add(const Key& key, const Value& value) {
	queue_.push_front(key);
	hashmap_[key] = make_pair(value, queue_.begin());
}

template<class Key, class Value>
void LRUCache<Key, Value>::remove() {
	Key key = queue_.back();
	hashmap_.erase(key);
	queue_.pop_back();
}

template<class Key, class Value>
void LRUCache<Key, Value>::update(const Key& key, const Entry& entry) {
	typename List::iterator pos = entry.second;
	queue_.erase(pos);
	queue_.push_front(key);
	hashmap_[key] = make_pair(entry.first, queue_.begin());
}

} // namespace cache
} // namespace service 

#endif /* LRUCACHE_IMP_H */

