/* 
 * File:   ServerApp.h
 * Author: xuanhungcao
 *
 * Created on June 30, 2017, 11:01 AM
 */

#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <Poco/Util/Application.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>

using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;

namespace service {

class ServerApp : public ServerApplication {
public:
	ServerApp();
	virtual ~ServerApp();
protected:
	void initialize(Application& self);
	void uninitialize();
	void defineOptions(OptionSet& option);
	void handleOption(const std::string& name, const std::string& value);
	int main(const ArgVec& args);
};

} // namespace service

#endif /* SERVERAPP_H */

