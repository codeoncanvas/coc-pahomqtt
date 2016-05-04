#pragma once

#include "cinder/Log.h"
#include "cinder/Utilities.h"

#include "client.h"
#include "connect_options.h"
#include "message.h"
#include "exception.h"


namespace coc {
    
    class cocPahoMqtt : public virtual mqtt::callback,
                        public virtual mqtt::iaction_listener
    {
        
    public:
        
        void connect( std::string address, int port, std::string clientId );
        void disconnect();
        
        void sendMessage( std::string topic, mqtt::message_ptr pubmsg );
        void sendMessage( std::string topic, std::string payload );

        bool setIsVerbose( bool _b = true ) { mIsVerbose = _b; }
        bool getIsVerbose() { return mIsVerbose; }
        
    private:
        
        // CALLBACKS

        virtual void connection_lost(const std::string& cause){};
        virtual void message_arrived(const std::string& topic, mqtt::message_ptr msg){};
        virtual void delivery_complete(mqtt::idelivery_token_ptr tok){};
        virtual void on_failure(const mqtt::itoken& tok){};
        virtual void on_success(const mqtt::itoken& tok){};

        mqtt::client    *mClient = nullptr;
        bool            mIsVerbose = false;

    };
}