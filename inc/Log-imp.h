/* 
 * File:   Log-imp.h
 * Author: xuanhungcao
 *
 * Created on July 12, 2017, 2:32 PM
 */

#ifndef LOG_IMP_H
#define LOG_IMP_H

#include "Util.h"
#include "Log.h"

namespace service {
namespace log {

template<class Key, class Value>
Log<Key, Value>::Log(){
}

template<class Key, class Value>
Log<Key, Value>::Log(const std::string& filename) : filename_(filename) {
}

template<class Key, class Value>
Log<Key, Value>::~Log() {}

template<class Key, class Value>
void Log<Key, Value>::recover(cache::MemoryCache<Key, Value>& memcache_) {
	filein_.open(filename_.c_str(), std::ios::in);
	if (!filein_.is_open()) {
		std::cout << "Error opening log file to recover" << "\n";
		return;
	}

	std::string request;
	Key key;
	std::string serialized_value;
	while (filein_ >> request) {
		switch (request[0]) {
				// SET
			case 'S':
				filein_ >> key;
				filein_ >> serialized_value;
				memcache_.set(key, Util::JSONDeserialize<Value>(serialized_value));
				break;
				// GET
			case 'G':
				filein_ >> key;
				memcache_.get(key);
				break;
				// REMOVE
			case 'R':
				filein_ >> key;
				memcache_.remove(key);
				break;
		}
	}
	filein_.close();
}

template<class Key, class Value>
void Log<Key, Value>::startWriting() {
	fileout_.open(filename_.c_str(), std::ios::out);
	if (!fileout_.is_open())
		std::cout << "Error opening log file to write" << "\n";
}

template<class Key, class Value>
void Log<Key, Value>::writeGet(const Key& key) {
	std::lock_guard<std::mutex> lock(mutex_);
	fileout_ << "G " << key << "\n";
	fileout_.flush();
}

template<class Key, class Value>
void Log<Key, Value>::writeSet(const Key& key, const Value& value) {
	std::lock_guard<std::mutex> lock(mutex_);
	fileout_ << "S " << key << " " << Util::JSONSerialize<Value>(value) << "\n";
	fileout_.flush();
}

template<class Key, class Value>
void Log<Key, Value>::writeRemove(const Key& key) {
	std::lock_guard<std::mutex> lock(mutex_);
	fileout_ << "R " << key << "\n";
	fileout_.flush();
}

template<class Key, class Value>
void Log<Key, Value>::reset() {
	std::lock_guard<std::mutex> lock(mutex_);
	fileout_.close();
	fileout_.open(filename_.c_str(), std::ios::out);
}

template<class Key, class Value>
void Log<Key, Value>::backup() {
	std::lock_guard<std::mutex> lock(mutex_);
	fileout_.close();
	
	filein_.open(filename_.c_str(), std::ios::binary);
	fileout_.open( (filename_ + ".bak").c_str(), std::ios::binary);
	fileout_ << filein_.rdbuf();
	
	filein_.close();
	fileout_.close();
}

} // namespace log
} // namespace service


#endif /* LOG_IMP_H */

