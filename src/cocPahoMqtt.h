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

#pragma once

#include "cinder/Log.h"
#include "cinder/Utilities.h"

#include "client.h"


namespace coc {

    class cocPahoMqtt : public virtual mqtt::callback,
                        public virtual mqtt::iaction_listener
    {

    public:

        void setIsVerbose( bool _b = true ) { mIsVerbose = _b; }
        bool getIsVerbose() { return mIsVerbose; }

        bool connect( std::string address, int port, std::string clientId, std::string persistDir = "" );
        void disconnect();
        bool getIsConnected();

        void subscribe( std::string topic );
        void unsubscribe( std::string topic );

        void sendMessage( std::string topic, mqtt::message_ptr pubmsg );
        void sendMessage( std::string topic, std::string payload );


    protected:

        //not using try_lock, blocking:
        void lock() { mMutex.lock(); }
//        bool lock() { mMutex.try_lock(); }
        void unlock() { mMutex.unlock(); }

    private:

        // CALLBACKS

        virtual void connection_lost(const std::string& cause){};
        virtual void message_arrived(const std::string& topic, mqtt::message_ptr msg){};
        virtual void delivery_complete(mqtt::idelivery_token_ptr tok){};
        virtual void on_failure(const mqtt::itoken& tok){};
        virtual void on_success(const mqtt::itoken& tok){};

        mqtt::client    *mClient = nullptr;
        bool            mIsVerbose = false;
        std::mutex      mMutex;
        std::string     mPersistDir = "";

    };
}
