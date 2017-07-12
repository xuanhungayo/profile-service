/* 
 * File:   MemoryCache.h
 * Author: xuanhungcao
 *
 * Created on June 29, 2017, 10:19 AM
 */

#ifndef MEMORYCACHE_H
#define MEMORYCACHE_H

#include <boost/optional.hpp>

namespace service {
namespace cache {

template<class Key, class Value>
class MemoryCache {
public:
	virtual bool contain(const Key& key) = 0;
	virtual boost::optional<Value> get(const Key& key) = 0;
	virtual void set(const Key& key, const Value& value) = 0;
	virtual void remove(const Key& key) = 0;
	virtual void clear() = 0;
	virtual void readFromBinaryFile(const std::string& filename) = 0;
	virtual void writeToBinaryFile(const std::string& filename) = 0;
};


} // namespace cache
} // namespace service

#endif /* MEMORYCACHE_H */

