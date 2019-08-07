//
//  main.cpp
//  CameraControllerApi
//  Created by Tobias Scheck on 09.08.13.
//  Copyright (c) 2013 scheck-media. All rights reserved.
//

#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include "Settings.h"
#include "Server.h"
#include <boost/filesystem.hpp>

#include "debug.h"
#include "api_app.h"
using namespace CameraControllerApi;
Server *srv;
#define SYS_DBG_EN == 1;
void sighandler(int sig){
    if(srv != NULL)
        srv->terminate(sig);
}

int api()
{
        SYS_PRINT("debug\n",sys_dbg_get_time());

        string port;
        Settings *cfg = Settings::getInstance();
        std::string sub="./settings.xml";
        cfg->base_path(sub.substr(0, sub.find_last_of("/")));
        bool ret = cfg->get_value("server.port", port);

        std::cout << "CameraControllerApi listening port " << port << std::endl;

        if(ret){
            SYS_PRINT("ret %d\n",ret);
            int http_port = atoi(port.c_str());
            srv = Server::getInstance();
            srv->run(http_port);
            signal(SIGTERM, sighandler);
        }

        cfg->release();
    return 0;
}

