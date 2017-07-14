/* 
 * File:   main.cpp
 * Author: xuanhungcao
 *
 * Created on June 22, 2017, 5:20 PM
 */

#include "../thrift-gen/ProfileService.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include <cstdlib>
#include <iostream>
#include <thread>
#include <mutex>
#include <assert.h>
#include <utility>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace profile;

std::mutex mtx;

const int REQ_PER_CLIENT = 10000;
const int CLIENT_NUM = 8;
const int LOAD_TEST_NUM = 10;

int total = 0;
int hit = 0;
int get_count = 0;

void print(const UserProfile& profile) {
	std::cout << profile.id << "\n";
	std::cout << profile.age << "\n";
	std::cout << profile.name << "\n";
	std::cout << "\n";
}

void clientThread() {
	int port = 9090;
	boost::shared_ptr<TSocket> socket(new TSocket("localhost", port));
	boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	boost::shared_ptr<ProfileServiceClient> client(new ProfileServiceClient(protocol));
	try {
		transport->open();

		UserProfile user;
		for (int i = 0; i < REQ_PER_CLIENT; i++) {
			int req_t = rand() % 3;
			switch (req_t) {
				case 0:
				{
					user.id = rand() % 10000 + 1;
					user.name = "abcedfghijklmnopqrstuvwxyz";
					user.age = rand() % 100 + 1;
					client->put(user.id, user);
				}
					break;
				case 1:
				{
					int id = rand() % 10000 + 1;
					UserProfile gotUser;
					client->get(gotUser, id);
					get_count ++;
					if (gotUser.id != -1) hit++;
				}
					break;
				case 2:
				{
					int id = rand() % 10000 + 1;
					client->remove(id);
				}
					break;
			}
		}

		transport->close();
	} catch (TException& tx) {
		std::cout << "ERROR: " << tx.what() << std::endl;
	}
}

int LoadTest(int id) {
	std::thread clients[CLIENT_NUM];

	std::pair<int, int> hit_ratio;
	time_t begin = clock();
	for (int i = 0; i < CLIENT_NUM; i++) clients[i] = std::thread(clientThread);
	for (auto& client : clients) client.join();
	time_t end = clock();
	double time = double(end - begin) / CLOCKS_PER_SEC;

	std::cout << "Load Test " << id << " finished" << "\n";
	std::cout << "--Performance: " << int(CLIENT_NUM * REQ_PER_CLIENT / time) << " requests per second\n";
	return int(CLIENT_NUM * REQ_PER_CLIENT / time);
}

void SimpleLogicTest() {


	int port = 9090;
	boost::shared_ptr<TSocket> socket(new TSocket("localhost", port));
	boost::shared_ptr<TTransport> transport(new TFramedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	ProfileServiceClient client(protocol);
	try {
		transport->open();

		UserProfile A, B, C;
		A.id = 1;
		A.age = 1;
		A.name = "Anna";

		B.id = 2;
		B.age = 2;
		B.name = "Bella";

		client.put(1, A);
		client.put(2, B);

		client.get(C, 1);
		assert(C.id == 1);

		client.get(C, 2);
		assert(C.name == "Bella");

		client.remove(1);
		client.get(C, 1);
		assert(C.id == -1);

		client.get(C, 2);
		assert(C.id == 2);
		
		B.name = "bella";
		client.put(2, B);
		assert(B.name == "bella");

		transport->close();
		std::cout << "Simple Logic Test passed\n";
	} catch (TException& tx) {
		std::cout << "ERROR: " << tx.what() << std::endl;
	}
}

int main(int argc, char** argv) {
	std::cout << "Client Test started" << "\n";
	
	SimpleLogicTest();
	std::cout << "---------------------------\n";

	for(int i = 1; i <= LOAD_TEST_NUM; i++) total += LoadTest(i);
	std::cout << "---------------------------\n";
	std::cout << "Number of client: " << CLIENT_NUM << "\n";
	std::cout << "Average performance: " << total / LOAD_TEST_NUM << " requests per second\n";
	std::cout << "Hit ratio: " << std::fixed << (double) hit / get_count << "\n";
	return 0;
}

