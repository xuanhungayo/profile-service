/* 
 * File:   LogHandler.h
 * Author: xuanhungcao
 *
 * Created on June 29, 2017, 11:05 AM
 */

#ifndef LOGHANDLER_H
#define LOGHANDLER_H

#include "JSONSerialization.h"

#include <iostream>
#include <fstream>
#include <mutex>

template<class Key, class Value>
class LogHandler {
public:

	LogHandler(const std::string& file_in_name) : file_name_(file_in_name) {
	}

	void recover(MemoryCache<Key, Value>& mem_cache) {
		file_in_.open(file_name_.c_str(), ios::in);
		if (!file_in_.is_open()) {
			std::cout << "Error opening log file to recover" << "\n";
			return;
		}
		
		std::string request;
		Key key;
		std::string serialized_value;
		while (file_in_ >> request) {
			switch (request[0]) {
					// SET
				case 'S':
					file_in_ >> key;
					file_in_ >> serialized_value;
					mem_cache.set(key, JSONSerialization<Value>::deserialize(serialized_value));
					break;
					// GET
				case 'G':
					file_in_ >> key;
					mem_cache.get(key);
					break;
					// REMOVE
				case 'R':
					file_in_ >> key;
					mem_cache.remove(key);
					break;
			}
		}
		file_in_.close();
	}
	
	void startWriting() {
		file_out_.open(file_name_.c_str(), std::ios::out);
		if (!file_out_.is_open())
			std::cout << "Error opening log file to write" << "\n";
	}
	
	void writeGet(const Key& key) {
		std::lock_guard<std::mutex> lock(mtx);
		file_out_ << "G " << key << "\n";
		file_out_.flush();
	}

	void writeSet(const Key& key, const Value& value) {
		std::lock_guard<std::mutex> lock(mtx);
		file_out_ << "S " << key << " " << JSONSerialization<Value>::serialize(value) << "\n";
		file_out_.flush();
	}

	void writeRemove(const Key& key) {
		std::lock_guard<std::mutex> lock(mtx);
		file_out_ << "R " << key << "\n";
		file_out_.flush();
	}

	void clear() {
		file_out_.close();
		file_out_.open(file_name_.c_str(), std::ios::out);
	}
	
	virtual ~LogHandler() {
		file_out_.close();
	};
private:
	std::ifstream file_in_;
	std::ofstream file_out_;
	const std::string file_name_;
	mutex mtx;
};

#endif /* LOGHANDLER_H */

