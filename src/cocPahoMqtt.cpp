/**
 *
 *      ┌─┐╔═╗┌┬┐┌─┐
 *      │  ║ ║ ││├┤
 *      └─┘╚═╝─┴┘└─┘
 *   ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
 *   │  ├─┤║║║└┐┌┘├─┤└─┐
 *   └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
 *
 * Copyright (c) 2016 Code on Canvas Pty Ltd, http://CodeOnCanvas.cc
 *
 * This software is distributed under the MIT license
 * https://tldrlegal.com/license/mit-license
 *
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code
 *
 **/

#pragma once

#include "cocPahoMqtt.h"

#include "cinder/Log.h"
#include "cinder/Utilities.h"

#include "connect_options.h"
#include "message.h"
#include "exception.h"

#define QOS         1


namespace coc {

bool cocPahoMqtt::connect( std::string address, int port, std::string clientId, std::string persistDir ) {

	std::string addressStr = address + ":" + ci::toString(port);
	if (persistDir.length()) {
		mPersistDir = persistDir;
		mClient = new mqtt::client(addressStr.c_str(), clientId.c_str(), mPersistDir );
	}
	else {
		mClient = new mqtt::client(addressStr.c_str(), clientId.c_str() );
	}


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

	return mClient->is_connected();
}

void cocPahoMqtt::disconnect() {
	if (!mClient->is_connected()) return;
	mClient->disconnect();
	mClient->close();
	CI_LOG_I( "Disonnected/Closed" );
}

bool cocPahoMqtt::getIsConnected() { return mClient->is_connected(); }


void cocPahoMqtt::sendMessage( std::string topic, mqtt::message_ptr pubmsg ) {

	if (!mClient->is_connected()) return;

	//use a message pointer.

	pubmsg->set_qos(QOS);
	mClient->publish(topic.c_str(), pubmsg);
	CI_LOG_V("Sent message");

}

void cocPahoMqtt::subscribe( std::string topic )
{
	if (!mClient->is_connected()) return;
	mClient->subscribe( topic, QOS );
}

void cocPahoMqtt::unsubscribe( std::string topic )
{
	if (!mClient->is_connected()) return;
	mClient->unsubscribe( topic );
}


void cocPahoMqtt::sendMessage( std::string topic, std::string payload ) {

	if (!mClient->is_connected()) return;

	// with itemized publish.

	CI_LOG_V("Sending message...");
	mClient->publish(topic.c_str(), payload.c_str(), payload.size()+1, 0, false);
	CI_LOG_V("Sent message");


}

}//namespace coc
