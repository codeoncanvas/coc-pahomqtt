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

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "ciPahoMqtt.h"

#define ADDRESS		    "tcp://iot.eclipse.org" //public MQTT broker for testing
#define PORT            1883
#define CLIENTID        "client_id"
#define TOPIC_SEND      "topic_send/"
#define TOPIC_RECEIVE   "topic_receive/"
#define PAYLOAD1        "Hello World 1!"
#define PAYLOAD2        "Hello World 2!"
#define PAYLOAD3        "Hello World 3!"

using namespace ci;
using namespace ci::app;
using namespace std;

class MqttClientApp : public App {
public:
    void setup() override;
    void mouseDown( MouseEvent event ) override;
    void update() override;
    void draw() override;
    void cleanup() override;

    ci::signals::ScopedConnection   cbOnDeliveryComplete, cbOnMessageArrived;

    void onDeliveryComplete( const mqtt::idelivery_token_ptr  tok);
    void onMessageArrived( const std::string& topic, mqtt::message_ptr msg );

    coc::ciPahoMqtt    mqtt;
};

void MqttClientApp::setup()
{

    cbOnDeliveryComplete =  mqtt.getSignalOnDeliveryComplete().connect( std::bind( &MqttClientApp::onDeliveryComplete, this, std::placeholders::_1 ) );
    cbOnMessageArrived =  mqtt.getSignalOnMessageArrived().connect( std::bind( &MqttClientApp::onMessageArrived, this, std::placeholders::_1, std::placeholders::_2 ) );


    mqtt.setIsVerbose(true);
    mqtt.connect(ADDRESS,PORT,CLIENTID);

    mqtt.subscribe( TOPIC_RECEIVE );

    mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(PAYLOAD1);
    mqtt.sendMessage( TOPIC_SEND, pubmsg);
    mqtt.sendMessage( TOPIC_SEND, PAYLOAD2);


}

void MqttClientApp::mouseDown( MouseEvent event )
{
    mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(PAYLOAD3);
    mqtt.sendMessage( TOPIC_SEND, pubmsg);
}

void MqttClientApp::update()
{
}

void MqttClientApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
}

void MqttClientApp::cleanup()
{
    mqtt.disconnect();
}

void MqttClientApp::onDeliveryComplete( const mqtt::idelivery_token_ptr tok ) {

    CI_LOG_V( "Delivery complete: " << tok->get_message_id() );

}

void MqttClientApp::onMessageArrived( const std::string& topic, mqtt::message_ptr msg ) {

    CI_LOG_V( "Message arrived: " << msg.get()->get_payload() );

}

CINDER_APP( MqttClientApp, RendererGl )
