/* 
 * File:   ProfileServiceHandler.cpp
 * Author: xuanhungcao
 * 
 * Created on June 29, 2017, 2:25 PM
 */

#include "../inc/ProfileServiceHandler.h"

#include <iostream>

#include <boost/optional.hpp>
#include <boost/chrono.hpp>

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/protocol/TBinaryProtocol.h>

using apache::thrift::protocol::TBinaryProtocol;
using apache::thrift::transport::TSocket;
using apache::thrift::transport::TFramedTransport;


ProfileServiceHandler::ProfileServiceHandler(const AbstractConfiguration& config) :
mem_cache_(config.getInt("cache-capacity")),
log_handler_(config.getString("log-file")),
cache_type_(config.getString("cache")),
db_enabled_(config.getBool("db")),
master_enabled_(config.getBool("master"))
{
	// Using DB
	if (db_enabled_)
		db_.open(config.getString("db-file").c_str(), HashDB::OWRITER | HashDB::OCREATE);
	
	// Using recover mode
	if (config.getBool("recover")) 
		log_handler_.recover(mem_cache_);
	
	// Set up connection to master server
	if (master_enabled_) {
		boost::shared_ptr<TSocket> socket(new TSocket(config.getString("master-host"), config.getInt("master-port")));
		boost::shared_ptr<TFramedTransport> transport(new TFramedTransport(socket));
		boost::shared_ptr<TBinaryProtocol> protocol(new TBinaryProtocol(transport));
		slave_.reset(new ProfileServiceClient(protocol));
		
		transport->open();
	}
	
	log_handler_.startWriting();
}

void ProfileServiceHandler::get(UserProfile& _return, const int32_t id) {
	log_handler_.writeGet(id);
	_return.id = -1;
	
	boost::shared_lock<boost::shared_mutex> lock(mutex_);
	boost::optional<UserProfile> profile;
	
	// Try getting from cache
	if (profile = mem_cache_.get(id)) {
		_return = (*profile);
		return;
	} 
	
	// Try getting from db
	std::string buffer;
	if (db_enabled_ && db_.get(std::to_string(id), &buffer)) {
		_return = JSONSerialization<UserProfile>::deserialize(buffer);
		mem_cache_.set(id, _return);
		return;
	}
	
	// Try getting from master
	if (master_enabled_)
		slave_->get(_return, id);
	if (_return.id != -1) { // Success
		std::string serialized_profile = JSONSerialization<UserProfile>::serialize(_return);
		db_.set(std::to_string(id), serialized_profile);
		mem_cache_.set(id, _return);
		return;
	}
}

void ProfileServiceHandler::put(const int32_t id, const UserProfile& profile) {
	log_handler_.writeSet(id, profile);
	
	boost::shared_lock<boost::shared_mutex> lock(mutex_);
	std::string serialized_profile = JSONSerialization<UserProfile>::serialize(profile);

	mem_cache_.set(id, profile);
	if (db_enabled_) 
		db_.set(std::to_string(id), serialized_profile);
	if (master_enabled_)
		slave_->put(id, profile);
}

void ProfileServiceHandler::remove(const int32_t id) {
	log_handler_.writeRemove(id);
	
	boost::shared_lock<boost::shared_mutex> lock(mutex_);
	mem_cache_.remove(id);
	if (db_enabled_) 
		db_.remove(std::to_string(id));
	if (master_enabled_)
		slave_->remove(id);
}

void ProfileServiceHandler::dumpCache(const std::string filename) {
	while (true) {
		boost::this_thread::sleep_for(boost::chrono::minutes(30));
		std::cout << "Start dumping cache to " << filename << std::endl;
		boost::lock_guard<boost::shared_mutex> lock(mutex_);
		log_handler_.clear();
		mem_cache_.write(filename);
	}
}


ProfileServiceHandler::~ProfileServiceHandler() {
	db_.close();
}

