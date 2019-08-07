//
//  Command.cpp
//  CameraControllerApi
//
//  Created by Tobias Scheck on 09.08.13.
//  Copyright (c) 2013 scheck-media. All rights reserved.
//

#include "Command.h"
#include "Api.h"
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>

#include "debug.h"
using namespace CameraControllerApi;

struct validate_data {
    string api;
    string action;
};

Command::Command(Api *api){

    //ex:http://localhost:8888/settings?action=focus_mode&amp&value=1
/*
http://localhost:8888/settings?action=list
http://localhost:8888/settings?action=aperture&amp&value=1.8
http://localhost:8888/settings?action=speed&amp&value=1/8                   //shutterspeed
http://localhost:8888/settings?action=iso&amp&value=200
http://localhost:8888/settings?action=whitebalance&amp&value=Tungsten
http://localhost:8888/settings?action=focus_point
http://localhost:8888/settings?action=imageformat&amp&value=Tiny JPEG
*/
    this->_api = api;
    set<string> params;
    string param_camera[] = {"status", "initialize"};
    string param_settings[] = {"list", "aperture", "speed", "iso", "whitebalance","focus_point","focus_mode", "by_key",
                               "datetime", "reviewtime", "output", "movierecordtarget", "evfmode", "ownername", "artist",
                               "copyright","focusinfo", "focusarea", "autopoweroff", "depthoffield", "capturetarget",
                               "imageformat", "imageformatsd", "imageformatcf", "colortemperature", "whitebalanceadjusta",
                               "whitebalanceadjustb", "whitebalancexa", "whitebalancexb", "colorspace", "autoexposuremode",
                               "drivemode", "picturestyle", "aperture", "shutterspeed", "meteringmode", "bracketmode","aeb"
                               };
    string param_execute[] = {"shot", "bulb", "timelapse","autofocus", "manualfocus"};
    string param_files[] = {"list", "get", "delete"};
    _valid_commands["/camera"] = set<string>(param_camera, param_camera + 2);
    _valid_commands["/settings"] = set<string>(param_settings, param_settings + 8);
    _valid_commands["/capture"] = set<string>(param_execute, param_execute + 5);
    _valid_commands["/fs"] = set<string>(param_files, param_files + 3);
}

int Command::execute(const string &url, const map<string, string> &argvals, string &response){
    string param;
    CCA_API_OUTPUT_TYPE type = CCA_OUTPUT_TYPE_JSON;
    validate_data vdata;
    vdata.api = url;
    map<string,string>::const_iterator iterator = argvals.find("action");

    if(iterator != argvals.end()){
        param = iterator->second;
        boost::trim(param);
    }

    iterator = argvals.find("type");
    if(iterator != argvals.end()){
        const string out_type = iterator->second;
        if(strcasecmp(out_type.c_str(), "xml") == 0)
            type = CCA_OUTPUT_TYPE_XML;
    }

    vdata.action = param;

    if ( !this->_validate(&vdata) || param.empty()) {
        ptree p;
        CCA_API_RESPONSE ret = CCA_API_RESPONSE_INVALID;
        Api::buildResponse(p, type, ret, response);
        CMD_DBG("return %d\n",ret);
        return ret;
    }
    CMD_DBG("return this\n");
    return this->_executeAPI(url, param, argvals, type, response);
}

bool Command::_executeAPI(const string &url, string action, const map<string, string> &urlparams, CCA_API_OUTPUT_TYPE type, string &response){
    bool ret = CCA_CMD_SUCCESS;

    string value = Command::find_url_param(urlparams, "value");
    CMD_DBG("_executeAPI url=%s action=%s value=%s urlparams=%s\n",url.c_str(),action.c_str(),value.c_str(),urlparams.value_comp());

/*
 * http://localhost:8888/camera?action=status
 * http://localhost:8888/camera?action=initialize
 */

    if(url == "/camera"){
        if(action.compare("status") == 0){
            ret = this->_api->status(type, response);
        } else if(action.compare("initialize") == 0){
            ret = this->_api->init(type, response);
        }
    }

     else if(url == "/settings"){
        if(action.compare("list") == 0){
            ret = this->_api->list_settings(type, response);
        } else if(action.compare("focus_point") == 0){
            ret = this->_api->set_focus_point(value, type, response);
        } else if(action.compare("aperture") == 0){
            ret = this->_api->set_aperture(value, type, response);
        } else if(action.compare("speed") == 0){
            ret = this->_api->set_speed(value, type, response);
        } else if(action.compare("isoi") == 0){
            ret = this->_api->set_iso(value, type, response);
             printf("\nret:%d\n",ret);
        } else if(action.compare("whitebalance") == 0){
            ret = this->_api->set_whitebalance(value, type, response);
        } else if(action.compare("key") == 0){
            ret = this->_api->get_settings_by_key(value, type, response);
        } else if(action.compare("imageformat") == 0){
            ret = this->_api->set_imageformat(value,type, response);
            printf("\nret:%d\n",ret);
        } else
        {   CMD_DBG("auto seach paramter");
            ret = this->_api->set_config(action,value,type,response);
        }
    } else if(url == "/capture"){
        if(action.compare("shot") == 0){
           ret = this->_api->shot(type, response);
        } else if(action.compare("autofocus") == 0){
            ret = this->_api->autofocus(type, response);
        } else if(action.compare("bulb") == 0){
            ret = this->_api->bulb(type, response);
        } else if(action.compare("timelapse") == 0){
            string interval = Command::find_url_param(urlparams, "interval");
            string start = Command::find_url_param(urlparams, "start");
            string end = Command::find_url_param(urlparams, "end");

            if(interval.empty()||end.empty())
                return false;

            int seconds = std::stoi(interval);
            time_t start_time, end_time;

            if(start.empty()) time(&start_time);
            else start_time = std::stoi(start);

            end_time = std::stoi(end);

             CMD_DBG("seconds=%d start_time=%lld  end_time=%lld \n",seconds,start_time,end_time);
             ret = this->_api->timelapse(seconds, start_time, end_time, type, response);


        }
    } else if(url == "/fs"){
        if(action.compare("list") == 0){
            ret = this->_api->list_files(type, response);
        } else if(action.compare("get") == 0){
            string path = Command::find_url_param(urlparams, "path");
            if(!path.empty())
                ret = this->_api->get_file(value, path, type, response);
            else
                ret = false;
        }
    }

   // http://localhost:8888/settings?action=kill&amp&value=200

    else if(url == "/kill"){
        CMD_DBG("kill");
    }
    else
        CMD_DBG("no URL");




    return ret;
}

string Command::find_url_param(const map<string, string>&params, const char *keyword){
    std::map<std::string, std::string>::const_iterator it = params.find(keyword);
    if(it != params.end()){
        string value;
        value = it->second;
        boost::trim(value);
        return value;
    }

    return "";
}

bool Command::_validate(const void *data){
    const validate_data *vdata = static_cast<const validate_data *>(data);
    map<string, set<string> >::iterator it = this->_valid_commands.find(vdata->api);

    if(it == this->_valid_commands.end()){
        return false;
    }

    return true;
}
