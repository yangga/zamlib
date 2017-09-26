[![Build Status](https://travis-ci.org/yangga/zamlib.svg?branch=master)](https://travis-ci.org/yangga/zamlib)
[![Build Status](https://ci.appveyor.com/api/projects/status/github/yangga/zamlib?svg=true)](https://ci.appveyor.com/project/yangga/zamlib)

zamlib
======
> C++ multi platform game server libraries. 

Setting
-------
#### # initialize to submodules
    git submodule update --init --recursive

or

    git pull --recurse-submodules

#### # install dependent libraries
* mac
  * brew install boost jsoncpp protobuf
* ubuntu
  * sudo apt-get install libboost-all-dev libjsoncpp-dev libprotobuf-dev
* ...

#### # more help for Windows
> It's pretty hard to cmake detects dependencies automatically.
##### You should focus on these additional entries to use cmake
###### Boost
* BOOST_ROOT - root path of boost library
###### Jsoncpp
* JSONCPP_INCLUDE_DIR_ROOT - include path of jsoncpp
* JSONCPP_LIBRARY - release ".lib" file path of jsoncpp
* JSONCPP_LIBRARY_DEBUG - debug ".lib" file path of jsoncpp 
###### Google Protobuf
* refer to <a href="https://cmake.org/cmake/help/v3.2/module/FindProtobuf.html">cmake::FindProtobuf</a>

Dependency
-------
###### Required
* Boost
* Jsoncpp
* JsonValueCaster
###### Optional
* Google Protobuf
