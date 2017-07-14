/* 
 * File:   ServerApp.cpp
 * Author: xuanhungcao
 * 
 * Created on June 30, 2017, 11:01 AM
 */

#include "ServerApp.h"
#include "ProfileServiceHandler.h"

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/PosixThreadFactory.h>
#include <thrift/server/TNonblockingServer.h>
#include <thrift/protocol/TBinaryProtocol.h>

#include <boost/make_shared.hpp>
#include <boost/thread.hpp>

#include <iostream>

using namespace apache::thrift::concurrency;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;
using namespace apache::thrift::server;

using namespace profile;

namespace service {

ServerApp::ServerApp() {
}

void ServerApp::initialize(Application& self) {
	loadConfiguration("config.properties");
	ServerApplication::initialize(self);
	logger().information("Starting server");
}

void ServerApp::uninitialize() {
	logger().information("Shutting down");
	ServerApplication::uninitialize();
}

void ServerApp::defineOptions(OptionSet& options) {
	ServerApplication::defineOptions(options);
	options.addOption(Option("cache", "c", "Memory caching type"));
	options.addOption(Option("db", "db", "Use database"));
	options.addOption(Option("recover","r", "Recover memory cache from log"));
}

void ServerApp::handleOption(const std::string& name, const std::string& value) {
	config().setString(name, value);
}

int ServerApp::main(const ArgVec& args) {
	
	// Set up thread manager for Nonblocking server
	boost::shared_ptr<ThreadManager> threadManager =
			ThreadManager::newSimpleThreadManager(config().getInt("worker"));
	threadManager->threadFactory(
			boost::make_shared<PosixThreadFactory>(new PosixThreadFactory()));
	threadManager->start();

	// Set up thrift server
	boost::shared_ptr<ProfileServiceHandler> handler(new ProfileServiceHandler(config()));
	boost::shared_ptr<ProfileServiceProcessor> processor(new ProfileServiceProcessor(handler));
	boost::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	TNonblockingServer server(processor, protocolFactory, config().getInt("port"), threadManager);
	server.serve();

	waitForTerminationRequest();

	return Application::EXIT_OK;
}

ServerApp::~ServerApp() {
}

} // namespace service

POCO_SERVER_MAIN(service::ServerApp);

