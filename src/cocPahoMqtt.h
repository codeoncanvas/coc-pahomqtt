#pragma once

#include "cinder/Log.h"
#include "cinder/Utilities.h"

#include "client.h"
#include "connect_options.h"
#include "message.h"
#include "exception.h"

#define QOS         1


namespace coc {
    
    class callback : public virtual mqtt::callback
    {
    public:
        virtual void connection_lost(const std::string& cause) {
            std::cout << "\nConnection lost" << std::endl;
            if (!cause.empty())
                std::cout << "\tcause: " << cause << std::endl;
        }
        
        // We're not subscrived to anything, so this should never be called.
        virtual void message_arrived(const std::string& topic, mqtt::message_ptr msg) {
        }
        
        virtual void delivery_complete(mqtt::idelivery_token_ptr tok) {
            std::cout << "\n\t[Delivery complete for token: "
            << (tok ? tok->get_message_id() : -1) << "]" << std::endl;
        }
    };
    
    
    class cocPahoMqtt : mqtt::callback {
        
    public:

        
        void connect( std::string address, int port, std::string clientId) {
            
            
            std::string addressStr = address + ":" + ci::toString(port);
            mClient = new mqtt::client(addressStr.c_str(), clientId.c_str() );

            
            //CALLBACKS
            
            mClient->set_callback(mCb);
            
            
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
        
        void disconnect() {
            if (!mClient->is_connected()) return;
            mClient->disconnect();
            CI_LOG_I( "Disonnected" );
        }
        
        //mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(PAYLOAD1);//was mqtt::message_ptr pubmsg = std::make_shared(PAYLOAD1);
        void sendMessage( std::string topic, mqtt::message_ptr pubmsg, bool listen = true ) {
            
            if (!mClient->is_connected()) return;
            
            //use a message pointer.
            
            if (listen) pubmsg->set_qos(QOS);
            mClient->publish(topic.c_str(), pubmsg);
            CI_LOG_V("Sent message");

        }
        
        void sendMessage( std::string topic, std::string payload ) {
            
            if (!mClient->is_connected()) return;
            
            // with itemized publish.
            
            CI_LOG_V("Sending message...");
            mClient->publish(topic.c_str(), payload.c_str(), payload.size()+1, 0, false);
            CI_LOG_V("Sent message");
            
            
        }
        
    private:
        
        // CALLBACKS
        
        void connection_lost(const std::string& cause) {
            std::cout << "\nConnection lost" << std::endl;
            if (!cause.empty())
                std::cout << "\tcause: " << cause << std::endl;
        }
        
        // We're not subscrived to anything, so this should never be called.
        void message_arrived(const std::string& topic, mqtt::message_ptr msg) {
        }
        
        void delivery_complete(mqtt::idelivery_token_ptr tok) {
            std::cout << "\n\t[Delivery complete for token: "
            << (tok ? tok->get_message_id() : -1) << "]" << std::endl;
        }

        mqtt::client    *mClient;
        coc::callback   mCb;
        
    };
}