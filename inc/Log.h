/* 
 * File:   LogHandler.h
 * Author: xuanhungcao
 *
 * Created on June 29, 2017, 11:05 AM
 */

#ifndef LOG_H
#define LOG_H

#include <mutex>
#include <fstream>

#include "MemoryCache.h"

namespace service {
namespace log {

template<class Key, class Value>
class Log {
public:
	Log();
	Log(const std::string& filename);
	~Log();
	void recover(cache::MemoryCache<Key, Value>& memcache);
	void startWriting();
	void writeGet(const Key& key);
	void writeSet(const Key& key, const Value&value);
	void writeRemove(const Key& key);
	void reset();
	void backup();
	
private:
	std::ifstream filein_;
	std::ofstream fileout_;
	const std::string filename_;
	std::mutex mutex_;
};

} // namespace log
} // namespace service

#include "Log-imp.h"

#endif /* LOG_H */

