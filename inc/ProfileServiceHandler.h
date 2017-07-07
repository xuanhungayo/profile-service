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

#include "../thrift-gen/ProfileService.h"
#include "MemoryCache.h"
#include "LRUCache.h"
#include "JSONSerialization.h"
#include "LogHandler.h"

#include <Poco/Util/AbstractConfiguration.h>
#include <boost/thread.hpp>
#include <kchashdb.h>

using namespace profile;
using namespace kyotocabinet;
using Poco::Util::AbstractConfiguration;

class ProfileServiceHandler : virtual public ProfileServiceIf {
public:
	ProfileServiceHandler(const AbstractConfiguration& config);
	void get(UserProfile& _return, const int32_t id);
	void put(const int32_t id, const UserProfile& profile);
	void remove(const int32_t id);
	void dumpCache(const std::string filename);
	virtual ~ProfileServiceHandler();
private:
	LRUCache<int32_t, UserProfile> mem_cache_;
	std::string cache_type_;
	
	LogHandler<int32_t, UserProfile> log_handler_;
	
	boost::shared_ptr<ProfileServiceClient> slave_;
	bool master_enabled_;
	
	HashDB db_;
	bool db_enabled_;
	
	boost::shared_mutex mutex_;
};

#endif /* PROFILESERVICEHANDLER_H */

