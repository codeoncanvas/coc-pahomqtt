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

#include "ciPahoMqtt.h"

namespace coc {

void ciPahoMqtt::connection_lost(const std::string& cause)
{
	lock();

	if (!cause.empty()) {
		CI_LOG_E( "Connection lost, cause: " << cause);
	}
	else {
		CI_LOG_E( "Connection lost");
	}

	signalOnConnectionLost.emit(cause);

	unlock();
}

void ciPahoMqtt::message_arrived(const std::string& topic, mqtt::message_ptr msg)
{
	lock();

	if ( getIsVerbose() ) {
		CI_LOG_V("Message arrived\n"
				<< "\ttopic: '" << topic << "'\n"
				<< "\t'" << msg->to_str());
	}

	signalOnMessageArrived.emit(topic,msg);

	unlock();

}

void ciPahoMqtt::delivery_complete(mqtt::idelivery_token_ptr tok)
{
	lock();

	if ( getIsVerbose() ) {
		CI_LOG_V( "[Delivery complete for token: " << (tok ? tok->get_message_id() : - 1) << "]" );
	}
	signalOnDeliveryComplete.emit(tok);

	unlock();
}

void ciPahoMqtt::on_failure(const mqtt::itoken& tok)
{
	lock();

	if (tok.get_message_id() != 0) {
		CI_LOG_E("Failure, (token: " << tok.get_message_id() << ")");
	}
	else {
		CI_LOG_E("Failure");
	}
	signalOnFailure.emit(tok);

	unlock();
}

void ciPahoMqtt::on_success(const mqtt::itoken& tok)
{
	lock();

	if ( getIsVerbose() ) {
		CI_LOG_V("Success:");
		if (tok.get_message_id() != 0)
			CI_LOG_V("\t(token: " << tok.get_message_id() << ")");
		if (!tok.get_topics().empty())
			CI_LOG_V("\ttoken topic: '" << tok.get_topics()[0] << "', ...");
	}
	signalOnSuccess.emit(tok);

	unlock();
}

}//namespace coc
