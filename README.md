[![Build Status](https://travis-ci.org/yangga/zamlib.png)](https://travis-ci.org/yangga/zamlib)
[![Build Status](https://ci.appveyor.com/api/projects/status/github/yangga/zamlib?svg=true)](https://ci.appveyor.com/project/yangga/zamlib)

zamlib
======
> Library for game server.

Setting
-------
#### # initialize to submodules
    git submodule update --init --recursive

or

    git pull --recurse-submodules

#### # install dependent libraries
* mac
  * brew install boost
  * brew install jsoncpp
* ...

#### # more help for Windows
> It's pretty hard to cmake detect dependencies automatically.
##### You should focus on these additional entries to use cmake
###### Boost
* BOOST_ROOT - root path of boost library
###### Jsoncpp
* JSONCPP_INCLUDE_DIR_ROOT - include path of jsoncpp
* JSONCPP_LIBRARY - release ".lib" file path of jsoncpp
* JSONCPP_LIBRARY_DEBUG - debug ".lib" file path of jsoncpp 


Dependency
-------
* Boost
* Jsoncpp
* JsonValueCaster
