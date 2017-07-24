/* 
 * File:   Slave.cpp
 * Author: xuanhungcao
 * 
 * Created on June 30, 2017, 11:01 AM
 */

#include <boost/make_shared.hpp>

#include "Slave.h"
#include "ProfileService.h"

namespace service {

Slave::Slave(const std::string& master_host, int master_port, int connections_num) :
connections_num_(connections_num) {
	// Create and open a number of connections
	for(int i = 0; i < connections_num_; i++) {
		sockets_.push_back(boost::make_shared<TSocket>(master_host, master_port));
		transports_.push_back(boost::make_shared<TFramedTransport>(sockets_[i]));
		protocols_.push_back(boost::make_shared<TBinaryProtocol>(transports_[i]));
		clients_.push_back(boost::make_shared<ProfileServiceClient>(protocols_[i]));
		
		transports_[i]->open();
	}
}

void Slave::get(UserProfile& _return, const int32_t id) {
	boost::shared_ptr<ProfileServiceClient> client(getClient());
	client->get(_return, id);
	returnClient(client);
}

void Slave::put(const int32_t id, const UserProfile& profile) {
	boost::shared_ptr<ProfileServiceClient> client(getClient());
	client->put(id, profile);
	returnClient(client);
}

void Slave::remove(const int32_t id) {
	boost::shared_ptr<ProfileServiceClient> client(getClient());
	client->remove(id);
	returnClient(client);
}

// We guarantee the size of the connection pool is equal to the number of threads using it
boost::shared_ptr<ProfileServiceClient> Slave::getClient() {
	std::lock_guard<std::mutex> lock(client_mtx_);
	boost::shared_ptr<ProfileServiceClient> result = clients_.back();
	clients_.pop_back();
	
	return result;
}

void Slave::returnClient(boost::shared_ptr<ProfileServiceClient> client) {
	std::lock_guard<std::mutex> lock(client_mtx_);
	clients_.push_back(client);
}

Slave::~Slave() {
	for(int i = 0; i < connections_num_; i++) 
		transports_[i]->close();
}

} // namespace service