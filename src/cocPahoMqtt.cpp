#pragma once

#include "cocPahoMqtt.h"

#include "cinder/Log.h"
#include "cinder/Utilities.h"

#include "connect_options.h"
#include "message.h"
#include "exception.h"

#define QOS         1


namespace coc {

void cocPahoMqtt::connect( std::string address, int port, std::string clientId ) {


	std::string addressStr = address + ":" + ci::toString(port);
	mClient = new mqtt::client(addressStr.c_str(), clientId.c_str() );


	//CALLBACKS

	mClient->set_callback(*this);


	mqtt::connect_options connOpts;
	connOpts.set_keep_alive_interval(20);
	connOpts.set_clean_session(true);

	try {
		mClient->connect(connOpts);
		CI_LOG_I( "Connected" );
	}
	catch (const mqtt::persistence_exception& exc) {
		CI_LOG_E( "Persistence Error: " << exc.get_message() << " ["
				<< exc.get_reason_code() << "]");
	}
	catch (const mqtt::exception& exc) {
		CI_LOG_E( "Error: " << exc.get_message() << " ["
				<< exc.get_reason_code() << "]");
	}
	catch ( ... ) {
		CI_LOG_E( "Connect Failed" );
	}
}

void cocPahoMqtt::disconnect() {
	if (!mClient->is_connected()) return;
	mClient->disconnect();
	CI_LOG_I( "Disonnected" );
}


void cocPahoMqtt::sendMessage( std::string topic, mqtt::message_ptr pubmsg ) {

	if (!mClient->is_connected()) return;

	//use a message pointer.

	pubmsg->set_qos(QOS);
	mClient->publish(topic.c_str(), pubmsg);
	CI_LOG_V("Sent message");

}


void cocPahoMqtt::sendMessage( std::string topic, std::string payload ) {

	if (!mClient->is_connected()) return;

	// with itemized publish.

	CI_LOG_V("Sending message...");
	mClient->publish(topic.c_str(), payload.c_str(), payload.size()+1, 0, false);
	CI_LOG_V("Sent message");


}

}//namespace coc