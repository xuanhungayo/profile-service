/* 
 * File:   Slave.cpp
 * Author: xuanhungcao
 * 
 * Created on June 30, 2017, 11:01 AM
 */

#include "Slave.h"
#include "ProfileService.h"

namespace service {

Slave::Slave(const std::string& master_host, int master_port) :
socket_(new TSocket(master_host, master_port)),
transport_(new TFramedTransport(socket_)),
protocol_(new TBinaryProtocol(transport_)),
client_(new ProfileServiceClient(protocol_)) {
	transport_->open();
}

void Slave::get(UserProfile& _return, const int32_t id) {
	client_->get(_return, id);
}

void Slave::put(const int32_t id, const UserProfile& profile) {
	client_->put(id, profile);
}

void Slave::remove(const int32_t id) {
	client_->remove(id);
}

Slave::~Slave() {
	transport_->close();
}

} // namespace service