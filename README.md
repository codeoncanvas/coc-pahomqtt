# README #

Install using Tinderbox, only 64 bit support maintained although 32 bit should be trivial.

C++ source files are from:
https://github.com/eclipse/paho.mqtt.cpp


## OSX ##

C compiled libs are from:
https://projects.eclipse.org/projects/technology.paho/downloads

Must add a run script at end of build phase with:

```
install_name_tool -change libpaho-mqtt3a.so.1 @executable_path/libpaho-mqtt3a.so.1 "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"
install_name_tool -change libpaho-mqtt3as.so.1 @executable_path/libpaho-mqtt3as.so.1 "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"
install_name_tool -change libpaho-mqtt3c.so.1 @executable_path/libpaho-mqtt3c.so.1 "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"
install_name_tool -change libpaho-mqtt3cs.so.1 @executable_path/libpaho-mqtt3cs.so.1 "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"
```
Note that downloaded compiled libs were renamed from *.1.0 to *.1


## WIN ##

C libs were compiled from master branch here, with visual studio project taken from develeop branch for x64 support:
https://github.com/eclipse/paho.mqtt.c.git

Had to edit `$(OpenSSLDir)` for 2 of the 4 lib projects to point to this install:
https://slproweb.com/download/Win64OpenSSL-1_0_2h.exe

