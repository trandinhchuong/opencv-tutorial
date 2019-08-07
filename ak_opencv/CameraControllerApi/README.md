CameraControllerApi
===================
The CameraControlerApi is an attempt to control a DSLR via REST functionality. At the moment is it possible
to change the camera settings (ISO, aperture, time), take pictures and stream the live view of the camera (only tested with a Nikon D90).

###Web-Interface###

`http://device_ip:port/webif/`


###Demonstration###

[![a demonstration for the CameraControlerApi](http://img.youtube.com/vi/tkMP7_gnoiU/3.jpg)](http://www.youtube.com/watch?v=tkMP7_gnoiU)


How to use
-----------
You will get all valid data for a command from the "list" action.

###Settings###

**List the configuration with validate values**

`http://device_ip:port/settings?action=list`



**ISO**

`http://device_ip:port/settings?action=iso&amp;value=200`
 http://localhost:8888/settings?action=iso&amp&value=200


**Aperture**

`http://device_ip:port/settings?action=aperture&amp;value=f/22`



**Shutter Speed**

`http://device_ip:port/settings?action=speed&amp;value=1/1000`



**Whitebalance**

`http://device_ip:port/settings?action=whitebalance&amp;value=Cloudy`



###Capture###

**take a picture**

`http://device_ip:port/capture?action=shot`



**autofocus**

`http://device_ip:port/capture?action=autofocus`


###File system###

**list of the available images on camera**

`http://device_ip:port/fs?action=list`



**get an image**

`http://device_ip:port/fs?action=get&value=filename.jpg&path=/path/to/file`




Each method will response with a JSON file. If you want a XML response you have to put the command "&amp;type=xml" on the end of the upper commands


####Live View
live view will be generated as mjpeg-stream. you can easy implement this stream in html inside an image tag e.g:
```
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Live View</title>
</head>

<body>
<img src="http://localhost:8888/liveview" />
</body>

</html>
```



##Dependencies##
```apt-get install libboost-dev libboost-system-dev libmicrohttpd-dev libgphoto2-dev libexiv2-dev```

+ libgphoto
+ libboost
+ libboost-system
+ libmicrohttpd
+ libexiv2


