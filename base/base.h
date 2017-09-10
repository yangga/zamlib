//
// Created by SungWoo Yang on 2017. 8. 31..
//

#ifndef ZAM_BASE_STDAFX_H
#define ZAM_BASE_STDAFX_H

#include <boost/config.hpp>

#ifdef BOOST_MSVC
#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>
#include <Winsock2.h>
#endif
#endif

#include <boost/assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/filesystem.hpp>
#include <boost/shared_ptr.hpp>

#include <iostream>

#endif //ZAM_BASE_STDAFX_H
