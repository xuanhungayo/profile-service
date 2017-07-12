/* 
 * File:   Util-imp.h
 * Author: xuanhungcao
 *
 * Created on July 12, 2017, 3:13 PM
 */

#ifndef UTIL_IMP_H
#define UTIL_IMP_H

#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TJSONProtocol.h>

using apache::thrift::transport::TMemoryBuffer;
using apache::thrift::protocol::TJSONProtocol;

namespace service {

template<class TObject>
std::string Util::JSONSerialize(const TObject& thrift_object) {
	boost::shared_ptr<TMemoryBuffer> transport(new TMemoryBuffer());
	boost::shared_ptr<TJSONProtocol> protocol(new TJSONProtocol(transport));

	thrift_object.write(protocol.get());
	return transport->getBufferAsString();
}

template<class TObject>
TObject Util::JSONDeserialize(const std::string& json_string) {
	boost::shared_ptr<TMemoryBuffer> transport(new TMemoryBuffer());
	boost::shared_ptr<TJSONProtocol> protocol(new TJSONProtocol(transport));

	transport->resetBuffer((uint8_t*) json_string.data(), static_cast<uint32_t> (json_string.length()));

	TObject object;
	object.read(protocol.get());

	return object;
}

} // namespace service

#endif /* UTIL_IMP_H */

