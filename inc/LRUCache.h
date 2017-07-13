/* 
 * File:   LRUCache.h
 * Author: xuanhungcao
 *
 * Created on June 21, 2017, 5:14 PM
 */

#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <list>
#include <unordered_map>
#include <utility>
#include <mutex>
#include <thread>

#include "MemoryCache.h"
#include "Log.h"

namespace service {
namespace cache {

template<class Key, class Value>
class LRUCache : public MemoryCache<Key, Value> {
public:
	typedef std::list<Key> List;
	typedef std::pair<Value, typename List::iterator> Entry;
	typedef std::unordered_map<Key, Entry> HashMap;

	LRUCache<Key, Value>(const int capacity);
	LRUCache<Key, Value>(const int capacity, const std::string& filename, const std::string& logfile);
	~LRUCache<Key, Value>();

	bool contain(const Key& key) override;
	boost::optional<Value> get(const Key& key) override;
	void set(const Key& key, const Value& value) override;
	void remove(const Key& key) override;
	void clear() override;
	void startDumping();

private:
	HashMap hashmap_;
	List queue_;
	std::mutex mutex_;
	int32_t capacity_;
	std::thread thread_;
	
	const std::string filename_;
	log::Log<Key, Value> log_;
	bool log_enabled_;

	void add(const Key& key, const Value& value);
	void remove();
	void update(const Key& key, const Entry& entry);

	void dump();
	void readFromBinaryFile(const std::string& filename) override;
	void writeToBinaryFile(const std::string& filename) override;
};



} // namespace cache
} // namespace service

#include "LRUCache-imp.h"

#endif /* LRUCACHE_H */

