/* 
 * File:   Slave.h
 * Author: xuanhungcao
 *
 * Created on July 14, 2017, 1:59 PM
 */

#ifndef SLAVE_H
#define SLAVE_H

#include <vector>
#include <thread>
#include <mutex>

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include "ProfileService.h"

using apache::thrift::protocol::TBinaryProtocol;
using apache::thrift::transport::TSocket;
using apache::thrift::transport::TFramedTransport;

using profile::UserProfile;
using profile::ProfileServiceClient;

namespace service {

class Slave {
public:
	Slave(const std::string& master_host, int master_port, int connections_num);
	~Slave();

	void get(UserProfile& _return, const int32_t id);
	void put(const int32_t id, const UserProfile& profile);
	void remove(const int32_t id);
private:
	std::mutex client_mtx_;
	int connections_num_;
	
	std::vector<boost::shared_ptr<TSocket>> sockets_;
	std::vector<boost::shared_ptr<TFramedTransport>> transports_;
	std::vector<boost::shared_ptr<TBinaryProtocol>> protocols_;
	std::vector<boost::shared_ptr<ProfileServiceClient>> clients_;
	
	boost::shared_ptr<ProfileServiceClient> getClient();
	void returnClient(boost::shared_ptr<ProfileServiceClient> client);
};

} // namespace service

#endif /* SLAVE_H */

