/* 
 * File:   ProfileServiceHandler.h
 * Author: xuanhungcao
 *
 * Created on June 29, 2017, 2:25 PM
 */

#ifndef PROFILESERVICEHANDLER_H
#define PROFILESERVICEHANDLER_H
#pragma POCO_STATIC

#include <mutex>

#include <Poco/Util/AbstractConfiguration.h>
#include <boost/thread.hpp>
#include <kchashdb.h>

#include "ProfileService.h"
#include "MemoryCache.h"
#include "LRUCache.h"
#include "Log.h"
#include "Slave.h"

using profile::ProfileServiceIf;
using profile::UserProfile;
using profile::ProfileServiceClient;

using kyotocabinet::HashDB;
using Poco::Util::AbstractConfiguration;

namespace service {

class ProfileServiceHandler : virtual public ProfileServiceIf {
public:
	ProfileServiceHandler(const AbstractConfiguration& config);
	void get(UserProfile& _return, const int32_t id);
	void put(const int32_t id, const UserProfile& profile);
	void remove(const int32_t id);
	virtual ~ProfileServiceHandler();
private:
	cache::LRUCache<int32_t, UserProfile> memcache_;
	std::string cache_type_;

	HashDB db_;
	bool db_enabled_;
	
	bool master_enabled_;
	Slave slave_;
	
	boost::shared_mutex mutex_;
};

} //namespace service
#endif /* PROFILESERVICEHANDLER_H */

