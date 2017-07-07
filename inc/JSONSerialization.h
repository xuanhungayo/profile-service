/* 
 * File:   JSONSerialization.h
 * Author: xuanhungcao
 *
 * Created on June 29, 2017, 11:35 AM
 */

#ifndef JSONSERIALIZATION_H
#define JSONSERIALIZATION_H

#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TJSONProtocol.h>

using namespace apache::thrift::transport;
using namespace apache::thrift::protocol;

// Serialize/Deserialize between JSON string and Thrift object
template<class TObject>
class JSONSerialization {
public:
	JSONSerialization();

	static std::string serialize(const TObject& object) {
		boost::shared_ptr<TMemoryBuffer> transport(new TMemoryBuffer());
		boost::shared_ptr<TJSONProtocol> protocol(new TJSONProtocol(transport));

		object.write(protocol.get());
		return transport->getBufferAsString();
	}

	static TObject deserialize(const std::string& buffer) {
		boost::shared_ptr<TMemoryBuffer> transport(new TMemoryBuffer());
		boost::shared_ptr<TJSONProtocol> protocol(new TJSONProtocol(transport));

		transport->resetBuffer((uint8_t*) buffer.data(), static_cast<uint32_t> (buffer.length()));

		TObject object;
		object.read(protocol.get());

		return object;
	}
	
	virtual ~JSONSerialization();
private:

};

#endif /* JSONSERIALIZATION_H */

