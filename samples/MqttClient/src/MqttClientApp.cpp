#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "cocPahoMqtt.h"

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
    mqtt.setup();
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
