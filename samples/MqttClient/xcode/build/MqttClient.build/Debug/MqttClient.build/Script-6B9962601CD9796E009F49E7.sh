#!/bin/sh
install_name_tool -change libpaho-mqtt3a.so.1 @executable_path/libpaho-mqtt3a.so.1 "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"
install_name_tool -change libpaho-mqtt3as.so.1 @executable_path/libpaho-mqtt3as.so.1 "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"
install_name_tool -change libpaho-mqtt3c.so.1 @executable_path/libpaho-mqtt3c.so.1 "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"
install_name_tool -change libpaho-mqtt3cs.so.1 @executable_path/libpaho-mqtt3cs.so.1 "$TARGET_BUILD_DIR/$PRODUCT_NAME.app/Contents/MacOS/$PRODUCT_NAME"
