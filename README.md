#JWM Settings Manager
Build Depends on Debian/Ubuntu
- cmake
- gcc-multilib [amd64]
- g++-multilib [amd64]
- libc6
- libfltk-images1.3
- libfltk1.3
- libfltk1.3-dev
- libfltk1.3-compat-headers
- libgcc1
- libstdc++6
- libx11-dev
- libxpm-dev
- fluid
- pkg-config

This program requires an out of source build, so create a build directory, for example:
`mkdir -p bin/Release`
then enter the directory and configure it with cmake
```
cd bin/Release
cmake ../..
```
Then once it configures run make
You can then run
`sudo make install`
to install all the common things (themes, etc...)
For command line options you can use the common help options
`-h` `--help` `-?`
You may also view the functions and variable status by using the `--debug` option
This can be used to document any issues you encounter.
For example
`./jwm-settings-manager --debug > jwm-settings-manager.log`
will save all the output to a file.
