#pragma once

#include "client.h"
#include "connect_options.h"
#include "message.h"
#include "exception.h"

#define ADDRESS     "tcp://localhost:1883"
#define CLIENTID    "ExampleClientPub"
#define TOPIC       "MQTT Examples"
#define PAYLOAD1     "Hello World 1!"
#define PAYLOAD2     "Hello World 2!"
#define PAYLOAD3     "Hello World 3!"
#define QOS         1


namespace coc {
    
    
    class cocPahoMqtt {
        
    public:
        
        void setup() {

            //todo: suss persist dir as 3rd arg
            mqtt::client client(ADDRESS, CLIENTID );


            //todo: get callback working
//            mqtt::callback cb;
//            client.set_callback(cb);
            
            mqtt::connect_options connOpts;
            connOpts.set_keep_alive_interval(20);
            connOpts.set_clean_session(true);
            
            try {
                std::cout << "Connecting..." << std::flush;
                client.connect(connOpts);
                std::cout << "OK" << std::endl;
                
                // First use a message pointer.
                
                std::cout << "Sending message..." << std::flush;
                mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(PAYLOAD1);//was mqtt::message_ptr pubmsg = std::make_shared(PAYLOAD1);
                pubmsg->set_qos(QOS);
                client.publish(TOPIC, pubmsg);
                std::cout << "OK" << std::endl;
                
                // Now try with itemized publish.
                
                std::cout << "Sending next message..." << std::flush;
                client.publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2)+1, 0, false);
                std::cout << "OK" << std::endl;
                
                // Now try with a listener, but no token
                
                std::cout << "Sending final message..." << std::flush;
                pubmsg = std::make_shared<mqtt::message>(PAYLOAD3);//was pubmsg = std::make_shared(PAYLOAD3);
                pubmsg->set_qos(QOS);
                client.publish(TOPIC, pubmsg);
                std::cout << "OK" << std::endl;
                
                // Disconnect
                std::cout << "Disconnecting..." << std::flush;
                client.disconnect();
                std::cout << "OK" << std::endl;
            }
            catch (const mqtt::persistence_exception& exc) {
                std::cerr << "Persistence Error: " << exc.what() << " ["
                << exc.get_reason_code() << "]" << std::endl;
//                return 1;
            }
            catch (const mqtt::exception& exc) {
                std::cerr << "Error: " << exc.what() << " ["
                << exc.get_reason_code() << "]" << std::endl;
//                return 1;
            }
            
//            return 0;
        }
        
        void update() {
            
        }
        
    };
}