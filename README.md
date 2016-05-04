# README #

Install using Tinderbox.

C compiled libs are from:
https://projects.eclipse.org/projects/technology.paho/downloads

C++ source files are from:
https://github.com/eclipse/paho.mqtt.cpp


## OSX ##

Add a run script at end of build phase with:

```
install_name_tool -change libpaho-mqtt3a.so.1 @executable_path/libpaho-mqtt3a.so.1 "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"
install_name_tool -change libpaho-mqtt3as.so.1 @executable_path/libpaho-mqtt3as.so.1 "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"
install_name_tool -change libpaho-mqtt3c.so.1 @executable_path/libpaho-mqtt3c.so.1 "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"
install_name_tool -change libpaho-mqtt3cs.so.1 @executable_path/libpaho-mqtt3cs.so.1 "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"
```
Note that downloaded compiled libs were renamed from *.1.0 to *.1


## WIN ##


Untested.
