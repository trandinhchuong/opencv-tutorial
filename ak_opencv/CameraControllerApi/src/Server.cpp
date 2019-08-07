//
//  Server.cpp
//  CameraControllerApi
//
//  Created by Tobias Scheck on 09.08.13.
//  Copyright (c) 2013 scheck-media. All rights reserved.
//

#include <pthread.h>
#include "Settings.h"
#include "Server.h"
#include <map>
#include <string>
#include <limits.h>
#include <unistd.h>
#include "Command.h"
#include <regex>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <boost/algorithm/string/replace.hpp>

#include "debug.h"



using std::map;
using std::regex;
using std::string;
using namespace CameraControllerApi;

#define PAGE "<html><head><title>Error</title></head><body></body></html>"

Server* Server::_instance = NULL;

Server::Server()
{
    this->_live_stream = new std::stringstream(std::ios::app | std::ios::in | std::ios::out);
}

Server* Server::getInstance(){
    if(_instance == NULL){
        _instance = new Server();
    }

    return _instance;
}

void Server::run(int port) {
    SEV_DBG("run(port:%d\n",port);

    this->_port = port;
    this->_shoulNotExit = 1;

    string auth = Settings::get_value("server.auth");
    string webif = Settings::get_value("general.webif");


    if(auth.compare("true") == 0)
        this->_auth = true;
    else
        this->_auth = false;

    if(webif.compare("true") == 0)
        this->_webif = true;
    else
        this->_webif = false;

    pthread_t tServer;
    if (0 != pthread_create(&tServer, NULL, Server::initial, this)) {
        exit(0);
    }

    pthread_join(tServer, NULL);
}

void *Server::initial(void *context){
    SEV_DBG("initial\n\a");
    Server *s = (Server *)context;
    s->cc = CameraController::getInstance();

    if(s->cc->is_initialized()){
        s->api = new Api(s->cc);
        s->cmd = new Command(s->api);
        s->http();
    }

    return 0;
}

void Server::terminate(int sig){
    SEV_DBG("terminate\n\a");
    this->_shoulNotExit = 0;
    CameraController *cc = CameraController::getInstance();
    cc->release();
}

int Server::send_bad_response( struct MHD_Connection *connection)
{   SEV_DBG("send_bad_response\n\a");
    static char *bad_response = (char *)PAGE;
    int bad_response_len = static_cast< int >(strlen(bad_response));
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer ( bad_response_len,
                                                bad_response,MHD_RESPMEM_PERSISTENT);
    if (response == 0){
        return MHD_NO;
    }
    ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
    MHD_destroy_response (response);
    return ret;
}

int Server::send_auth_fail( struct MHD_Connection *connection)
{   SEV_DBG("send_auth_fail\n\a");
    static char *bad_response = (char *)PAGE;
    int bad_response_len = static_cast< int >(strlen(bad_response));
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer ( bad_response_len,
                                                bad_response,MHD_RESPMEM_PERSISTENT);
    if (response == 0){
        return MHD_NO;
    }
    ret = MHD_queue_basic_auth_fail_response(connection, "CameraControlerApi", response);
    MHD_destroy_response (response);
    return ret;
}


int Server::get_url_args(void *cls, MHD_ValueKind kind, const char *key , const char* value){
    SEV_DBG("get_url_args: \n\a");
    map<string, string> *args = static_cast<map<string,string>*>(cls);
    if(args->find(key) == args->end()){
        if(!value){
            (*args)[key] = "";
        } else {
            (*args)[key] = value;
        }
    }

    return MHD_YES;
}

int Server::url_handler (void *cls,
                        struct MHD_Connection *connection,
                        const char *url,
                        const char *method,
                        const char *version,
                        const char *upload_data, size_t *upload_data_size, void **ptr){
    SEV_DBG("url_handler:%s method:%s \n ",url,method);
    int ret;
    map<string, string> url_args;
    string respdata;

    static int aptr;
    std::string urlString(url);



    struct MHD_Response *response;

    if (0 != strcmp(method, "GET")) {
        return MHD_NO;
    }

    if(&aptr != *ptr){
        *ptr = &aptr;
        return MHD_YES;
    }

    Server s = *(Server *)cls;

    if(s._auth){
        Settings *settings = Settings::getInstance();
        string username, password;
        settings->get_value("server.username", username);
        settings->get_value("server.password", password);

        char *user, *pass;
        pass = NULL;
        user = MHD_basic_auth_get_username_password(connection, &pass);
        bool auth_fail = ((user == NULL) || (0 != username.compare(user)) || (0 != password.compare(pass)));
        if(auth_fail)
            return Server::send_auth_fail(connection);

    }

    if(MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, Server::get_url_args, &url_args) < 0){
        return Server::send_bad_response(connection);
    }

    if( urlString.find("webif") != std::string::npos && s._webif){
        response = handle_webif(cls, connection, url);
    } else if(urlString.find("liveview") != std::string::npos) {
      response = MHD_create_response_from_callback (MHD_SIZE_UNKNOWN,
                                                      512 * 1024,
                                                      Server::handle_mjpeg, cls, Server::free_mjpeg);
        MHD_add_response_header(response, "Content-Type", "multipart/x-mixed-replace;boundary=CCA_LV_FRAME");
    } else if(urlString.find("preview") != std::string::npos) {
        const char *data;

        int size = s.cc->preview(&data);
        response = MHD_create_response_from_buffer(size, (void *)data, MHD_RESPMEM_MUST_COPY);
          MHD_add_response_header(response, "Content-Type", "image/jpeg");

    }else if(urlString.find("kill") != std::string::npos) {
        SEV_DBG("kill/n");

        }

    else {
        response = handle_api(cls, url, url_args, respdata, ptr);
    }


    ret = MHD_queue_response (connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

MHD_Response* Server::handle_webif(void *cls,
                        struct MHD_Connection *connection,
                        const char *url) {
    SEV_DBG("handle_webif\n\a");
    std::string path(url);
    struct stat buff;
    int fd;
    MHD_Response *response;

    boost::replace_all(path, "webif", "");
    boost::replace_all(path, "webif/", "");
    if(path.compare("/") == 0) path = "/index.html";
    path.insert(0, "./webif");

    if ( (-1 == (fd = open (path.c_str(), O_RDONLY))) || (0 != fstat (fd, &buff))){
           if (fd != -1) close (fd);
           Server::send_bad_response(connection);
           return NULL;
    }

    std::string ext = path.substr(path.find_last_of(".") + 1);

    std::string mime;
    if(ext.compare("js") == 0)
           mime = "text/javascript";
    else if(ext.compare("css") == 0)
           mime = "text/css";
    else if(ext.compare("jpg") == 0 || ext.compare(".jpeg") == 0 || ext.compare(".jpe") == 0)
           mime = "image/jpeg";
    else if(ext.compare("gif") == 0)
           mime = "image/gif";
    else if(ext.compare("png") == 0)
           mime = "image/png";
    else
           mime = "text/html";

    response = MHD_create_response_from_fd (buff.st_size, fd);
    MHD_add_response_header (response, "Content-Type", mime.c_str());

    return response;
}

ssize_t Server::handle_mjpeg(void *cls, uint64_t pos, char *buf, size_t max){
    SEV_DBG("handle_mjpeg\n\a");
    Server *s = static_cast<Server*>(cls);
    s->_live_stream->seekg(pos);

    std::streamsize available = s->_live_stream->rdbuf()->in_avail();

    if(available < max) {
        const char *data;
        int size = s->cc->preview(&data);
        if(size < GP_OK)
            return MHD_CONTENT_READER_END_OF_STREAM;

        *s->_live_stream << "--CCA_LV_FRAME\r\nContent-Type: image/jpeg\r\n\r\n";
        *s->_live_stream << std::string(data, size);
        *s->_live_stream << "\r\n";
        delete data;
    }


    s->_live_stream->read(buf, max);
    return max;
}

void Server::free_mjpeg(void *cls) {
    SEV_DBG("handle_mjpeg\n\a");
    Server *s = static_cast<Server *>(cls);
    s->_live_stream->str("");
    s->_live_stream->clear();
}

MHD_Response* Server::handle_api(void *cls,
                 const char *url,
                map<string, string> url_args,
                string respdata,
                 void **ptr){
     SEV_DBG("handle_api\n\a");
    Server s = *(Server *)cls;
    map<string, string>::iterator  it;
    const char *typexml = "xml";
    const char *typejson = "json";
    const char *type = typejson;
    char *me;
    MHD_Response *response;

    s.cmd->execute(url, url_args, respdata);


    *ptr = 0;
    me = (char *)malloc(respdata.size() + 1);
    if(me == 0)
            return MHD_NO;

    strncpy(me, respdata.c_str(), respdata.size() + 1);

    response = MHD_create_response_from_buffer(strlen(me), (void *)me, MHD_RESPMEM_MUST_COPY);

    if(response == 0){
            free(me);
            return MHD_NO;
    }

    it = url_args.find("type");
    if (it != url_args.end() && strcasecmp(it->second.c_str(), "xml")) {
            type = typexml;
    }

    if(type == typejson){
            MHD_add_response_header(response, "Content-Type", "application/json");
            //MHD_add_response_header(response, "Content-Disposition", "attachment;filename=\"cca.json\"");
    } else {
            MHD_add_response_header(response, "Content-Type", "application/xml");
            //MHD_add_response_header(response, "Content-Disposition", "attachment;filename=\"cca.xml\"");
    }

    MHD_add_response_header (response, "Access-Control-Allow-Origin", "*");
    return response;
 }

void Server::http(){
    SEV_DBG("http\n\a");
    struct MHD_Daemon *d;
    d = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, this->_port,
                         0, 0, Server::url_handler, (void*)this ,MHD_OPTION_END);
    if(d == NULL){
        return;
    }

    while (this->_shoulNotExit) {
        sleep(1);
    }


    MHD_stop_daemon(d);
    return;
}

