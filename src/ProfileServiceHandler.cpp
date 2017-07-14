/* 
 * File:   ProfileServiceHandler.cpp
 * Author: xuanhungcao
 * 
 * Created on June 29, 2017, 2:25 PM
 */

#include "ProfileServiceHandler.h"

#include <iostream>

#include <boost/optional.hpp>

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "Util.h"
#include "Slave.h"

using apache::thrift::protocol::TBinaryProtocol;
using apache::thrift::transport::TSocket;
using apache::thrift::transport::TFramedTransport;

namespace service {

ProfileServiceHandler::ProfileServiceHandler(const AbstractConfiguration& config) :
memcache_(config.getInt("cache-capacity"), config.getString("cache-file"), config.getString("log-file")),
db_enabled_(config.getBool("db")),
master_enabled_(config.getBool("master")),
master_host_(config.getString("master-host")),
master_port_(config.getInt("master-port")) {
	// Set up DB
	if (db_enabled_)
		db_.open(config.getString("db-file").c_str(), HashDB::OWRITER | HashDB::OCREATE);

	// Run thread for cache dumping
	memcache_.startDumping();
}

ProfileServiceHandler::~ProfileServiceHandler() {
	db_.close();
}

void ProfileServiceHandler::get(UserProfile& _return, const int32_t id) {
	_return.id = -1;
	boost::optional<UserProfile> profile;

	// Try getting from cache
	if (profile = memcache_.get(id)) {
		_return = (*profile);
		return;
	}

	// Try getting from db
	std::string buffer;
	if (db_enabled_ && db_.get(std::to_string(id), &buffer)) {
		_return = Util::JSONDeserialize<UserProfile>(buffer);
		memcache_.set(id, _return);
		return;
	}

	// Try getting from master
	if (master_enabled_) {
		Slave slave(master_host_, master_port_);
		slave.get(_return, id);
	}
	if (_return.id != -1) { // Success
		std::string serialized_profile = Util::JSONSerialize<UserProfile>(_return);
		if (db_enabled_) 
			db_.set(std::to_string(id), serialized_profile);
		memcache_.set(id, _return);
		return;
	}
}

void ProfileServiceHandler::put(const int32_t id, const UserProfile& profile) {
	std::string serialized_profile = Util::JSONSerialize<UserProfile>(profile);

	memcache_.set(id, profile);
	if (db_enabled_)
		db_.set(std::to_string(id), serialized_profile);
	if (master_enabled_) {
		Slave slave(master_host_, master_port_);
		slave.put(id, profile);
	}
}

void ProfileServiceHandler::remove(const int32_t id) {
	memcache_.remove(id);
	if (db_enabled_)
		db_.remove(std::to_string(id));
	if (master_enabled_) {
		Slave slave(master_host_, master_port_);
		slave.remove(id);
	}
}

} // namespace service

