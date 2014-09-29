jwm-settings-manager
====================

A simple settings manager for configuring JWM.
This project is tailored originally for Tori OS.
This means it works in Ubuntu 12.04 - 14.04

It has been built successfully using pbuilder and the normal Debian tools.
There may be some work to do to get it to build successfully on other distributions.

The base for this is C++, tinyxml2, and fltk
You will also need fontconfig and the X11 libraries for color.

You can look at /debian/control for the Ubuntu specific requirements, however the CMakeLists.txt
 *should* work for you
 
 Any help cleaning up the code or working on new features and implementing unfinished features would be appreciated
 :)
 
 
 'A live dog is better than a dead Lion'
