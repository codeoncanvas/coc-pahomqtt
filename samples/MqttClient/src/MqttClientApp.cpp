#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cocPahoMqtt.h"

#define ADDRESS     "tcp://localhost"
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
    
    coc::cocPahoMqtt    mqtt;
};

void MqttClientApp::setup()
{
    mqtt.connect(ADDRESS,PORT,CLIENTID);
    
    mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(PAYLOAD1);
    mqtt.sendMessage( TOPIC, pubmsg);
    
    mqtt.sendMessage( TOPIC, PAYLOAD2);
    
    pubmsg = std::make_shared<mqtt::message>(PAYLOAD3);
    mqtt.sendMessage( TOPIC, pubmsg);
    
    mqtt.disconnect();
    
}

void MqttClientApp::mouseDown( MouseEvent event )
{
}

void MqttClientApp::update()
{
}

void MqttClientApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) );
}

CINDER_APP( MqttClientApp, RendererGl )
