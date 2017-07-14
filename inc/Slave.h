/* 
 * File:   Slave.h
 * Author: xuanhungcao
 *
 * Created on July 14, 2017, 1:59 PM
 */

#ifndef SLAVE_H
#define SLAVE_H

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
	Slave(const std::string& master_host, int master_port);
	~Slave();

	void get(UserProfile& _return, const int32_t id);
	void put(const int32_t id, const UserProfile& profile);
	void remove(const int32_t id);
private:
	boost::shared_ptr<TSocket> socket_;
	boost::shared_ptr<TFramedTransport> transport_;
	boost::shared_ptr<TBinaryProtocol> protocol_;
	boost::shared_ptr<ProfileServiceClient> client_;
};

} // namespace service

#endif /* SLAVE_H */

