//
//	    ┌─┐╔═╗┌┬┐┌─┐
//      │  ║ ║ ││├┤
//      └─┘╚═╝─┴┘└─┘
//	 ┌─┐┌─┐╔╗╔┬  ┬┌─┐┌─┐
//	 │  ├─┤║║║└┐┌┘├─┤└─┐
//	 └─┘┴ ┴╝╚╝ └┘ ┴ ┴└─┘
//	http://CodeOnCanvas.cc
//
// Created by Rene Christen on 4/05/2016.
// Copyright (c) 2016, Code on Canvas Pty Ltd//

#include "ciPahoMqtt.h"

namespace coc {

void ciPahoMqtt::connection_lost(const std::string& cause)
{
	if (!cause.empty()) {
		CI_LOG_E( "Connection lost, cause: " << cause);
	}
	else {
		CI_LOG_E( "Connection lost");
	}

	signalOnConnectionLost.emit(cause);
}

void ciPahoMqtt::message_arrived(const std::string& topic, mqtt::message_ptr msg)
{

	if ( getIsVerbose() ) {
		CI_LOG_V("Message arrived\n"
				<< "\ttopic: '" << topic << "'\n"
				<< "\t'" << msg->to_str());
	}

	signalOnMessageArrived.emit(topic,msg);

}

void ciPahoMqtt::delivery_complete(mqtt::idelivery_token_ptr tok)
{

	if ( getIsVerbose() ) {
		CI_LOG_V( "[Delivery complete for token: " << (tok ? tok->get_message_id() : - 1) << "]" );
	}
	signalOnDeliveryComplete.emit(tok);
}

void ciPahoMqtt::on_failure(const mqtt::itoken& tok)
{
	if (tok.get_message_id() != 0) {
		CI_LOG_E("Failure, (token: " << tok.get_message_id() << ")");
	}
	else {
		CI_LOG_E("Failure");
	}
	signalOnFailure.emit(tok);
}

void ciPahoMqtt::on_success(const mqtt::itoken& tok)
{
	if ( getIsVerbose() ) {
		CI_LOG_V("Success:");
		if (tok.get_message_id() != 0)
			CI_LOG_V("\t(token: " << tok.get_message_id() << ")");
		if (!tok.get_topics().empty())
			CI_LOG_V("\ttoken topic: '" << tok.get_topics()[0] << "', ...");
	}
	signalOnSuccess.emit(tok);
}

}//namespace coc
