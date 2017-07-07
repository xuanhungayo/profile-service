/* 
 * File:   MemoryCache.h
 * Author: xuanhungcao
 *
 * Created on June 29, 2017, 10:19 AM
 */

#ifndef MEMORYCACHE_H
#define MEMORYCACHE_H

#include <boost/optional.hpp>

template<class Key, class Value>
class MemoryCache {
protected:
	int capacity;
public:

	MemoryCache(const int _capacity) : capacity(_capacity) {
	}
	virtual boost::optional<Value> get(const Key& key) = 0;
	virtual void set(const Key& key, const Value& value) = 0;
	virtual void remove(const Key& key) = 0;
	virtual bool contain(const Key& key) = 0;
	virtual void clear() = 0;
	virtual ~MemoryCache() {};
};

#endif /* MEMORYCACHE_H */

