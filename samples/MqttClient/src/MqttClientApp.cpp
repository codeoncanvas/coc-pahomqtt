#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "ciPahoMqtt.h"

//#define ADDRESS     "tcp://localhost"
#define ADDRESS		"tcp://iot.eclipse.org"
#define PORT        1883
#define CLIENTID    "ExampleClientPub"
#define TOPIC       "MQTT Examples"
#define PAYLOAD1     "Hello World 1!"
#define PAYLOAD2     "Hello World 2!"
#define PAYLOAD3     "Hello World 3!"

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

    ci::signals::ScopedConnection   cbOnDeliveryComplete;

    void onDeliveryComplete( const mqtt::idelivery_token_ptr  tok);

    coc::ciPahoMqtt    mqtt;
};

void MqttClientApp::setup()
{

    cbOnDeliveryComplete =  mqtt.getSignalOnDeliveryComplete().connect( std::bind( &MqttClientApp::onDeliveryComplete, this, std::placeholders::_1 ) );


    mqtt.setIsVerbose(true);
    mqtt.connect(ADDRESS,PORT,CLIENTID);
    
    mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(PAYLOAD1);
    mqtt.sendMessage( TOPIC, pubmsg);
    
    mqtt.sendMessage( TOPIC, PAYLOAD2);

    
}

void MqttClientApp::mouseDown( MouseEvent event )
{
    mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(PAYLOAD3);
    mqtt.sendMessage( TOPIC, pubmsg);
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

CINDER_APP( MqttClientApp, RendererGl )
