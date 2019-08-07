//
//  Api.h
//  CameraControllerApi
//
//  Created by Tobias Scheck on 09.08.13.
//  Copyright (c) 2013 scheck-media. All rights reserved.
//

#ifndef __CameraControllerApi__Api__
#define __CameraControllerApi__Api__

#include "CameraController.h"
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

#define CCA_ERROR_MESSAGE_FILE "error_messages.xml"

namespace CameraControllerApi {

    using std::map;
    using std::string;
    using boost::property_tree::ptree;
    using boost::property_tree::basic_ptree;

    typedef enum {
        CCA_API_RESPONSE_SUCCESS = 1,
        CCA_API_RESPONSE_INVALID = -1,
        CCA_API_RESPONSE_CAMERA_NOT_FOUND = -2,
        CCA_API_RESPONSE_CAMERA_BUSY = -3,
    } CCA_API_RESPONSE;

    typedef enum {
        CCA_OUTPUT_TYPE_XML,
        CCA_OUTPUT_TYPE_JSON
    } CCA_API_OUTPUT_TYPE;

    /**
     @class Api
     @\brief responsible for the interaction between a command and the camera
     */
    class Api {
    private:

        /**
         @brief CameraControler Instance
         */
        CameraController *_cc;

        /**
         @brief creates a "camera not found" method
         @param[in]     resp
         @param[in]     CCA_API_OUTPUT_TYPE
         @param[out]    output
         */
        bool _buildCameraNotFound(CCA_API_RESPONSE resp, CCA_API_OUTPUT_TYPE type, string &output);

        /**
         @brief sets a value in camera config
         @param[in]     key - config value key
         @param[in]     value - value for key
         @param[in]     CCA_API_OUTPUT_TYPE
         @param[out]    output
         */
        bool _set_settings_value(string key, string value, CCA_API_OUTPUT_TYPE type, string &output);
        bool _check(CCA_API_OUTPUT_TYPE type, string &output);
    public:
        Api(CameraController *cc);
        static void buildResponse(ptree data, CCA_API_OUTPUT_TYPE type, CCA_API_RESPONSE resp, string &output);
        static void errorMessage(CCA_API_RESPONSE errnr, string &message);
        bool status(CCA_API_OUTPUT_TYPE type, string &output);
        bool init(CCA_API_OUTPUT_TYPE type, string &output);
        bool list_settings(CCA_API_OUTPUT_TYPE type, string &output);
        bool list_files(CCA_API_OUTPUT_TYPE type, string &output);
        bool get_settings_by_key(string key, CCA_API_OUTPUT_TYPE type, string &output);
        bool get_file(string file, string path, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_focus_point(string focus_point, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_aperture(string aperture, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_speed(string speed, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_iso(string iso, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_whitebalance(string wb, CCA_API_OUTPUT_TYPE type, string &output);
        bool shot(CCA_API_OUTPUT_TYPE type, string &output);
        bool autofocus(CCA_API_OUTPUT_TYPE type, string &output);
        bool bulb(CCA_API_OUTPUT_TYPE type, string &output);
        bool timelapse(int interval, time_t start, time_t end, CCA_API_OUTPUT_TYPE type, string &output);
        bool burst(int number_of_images, CCA_API_OUTPUT_TYPE type, string &output);

        bool set_datetime(string datetime, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_reviewtime(string reviewtime, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_movierecordtarget(string movierecordtarget, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_evfmode(string evfmode, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_ownername(string ownername, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_ouput(string artist, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_copyright(string copyright, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_focusinfo(string focusinfo, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_focusarea(string focusarea, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_autopoweroff(string autopoweroff, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_depthoffield(string depthoffield, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_capturetarget(string capturetarget, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_imageformat(string imageformat, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_imageformatsd(string imageformatsd, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_imageformatcf(string imageformatcf, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_whitebalanceadjusta(string whitebalanceadjusta, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_whitebalancexa(string whitebalancexa, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_whitebalancexb(string whitebalancexb, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_colorspace(string colorspace, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_autoexposuremode(string autoexposuremode, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_drivemode(string drivemode, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_picturestyle(string picturestyle, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_shutterspeed(string shutterspeed, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_meteringmode(string meteringmode, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_bracketmode(string bracketmode, CCA_API_OUTPUT_TYPE type, string &output);
        bool set_aeb(string aeb, CCA_API_OUTPUT_TYPE type, string &output);

        bool set_config(string comment,string data, CCA_API_OUTPUT_TYPE type, string &output);





    };
}

#endif /* defined(__CameraControllerApi__Api__) */
