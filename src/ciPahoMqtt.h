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
// Copyright (c) 2016, Code on Canvas Pty Ltd
//

/*
 * Example of connecting call back:
 * cbOnMessageArrived =  getSignalOnMessageArrived().connect( std::bind( &MyClass::onMessageArrived, this, std::placeholders::_1, std::placeholders::_2 ) );
 */

#pragma once

#include "cinder/Signals.h"
#include "cocPahoMqtt.h"

namespace coc {

class ciPahoMqtt : public cocPahoMqtt {

public:


	ci::signals::Signal<void( const std::string& )> &getSignalOnConnectionLost() { return signalOnConnectionLost; }
	ci::signals::Signal<void( const std::string&, mqtt::message_ptr )> &getSignalOnMessageArrived() { return signalOnMessageArrived; }
	ci::signals::Signal<void( const mqtt::idelivery_token_ptr )> &getSignalOnDeliveryComplete() { return signalOnDeliveryComplete; }
	ci::signals::Signal<void( const mqtt::itoken& )> &getSignalOnFailure() { return signalOnFailure; }
	ci::signals::Signal<void( const mqtt::itoken& )> &getSignalOnSuccess() { return signalOnSuccess; }


private:

	ci::signals::Signal<void( const std::string& )> signalOnConnectionLost;
	ci::signals::Signal<void( const std::string&, mqtt::message_ptr )> signalOnMessageArrived;
	ci::signals::Signal<void( const mqtt::idelivery_token_ptr )> signalOnDeliveryComplete;
	ci::signals::Signal<void( const mqtt::itoken& )> signalOnFailure;
	ci::signals::Signal<void( const mqtt::itoken& )> signalOnSuccess;

	void connection_lost(const std::string& cause);
	void message_arrived(const std::string& topic, mqtt::message_ptr msg);
	void delivery_complete(mqtt::idelivery_token_ptr tok);
	void on_failure(const mqtt::itoken& tok);
	void on_success(const mqtt::itoken& tok);


};//class ciPahoMqtt

}//namespace coc



