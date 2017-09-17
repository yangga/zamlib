//
// Created by SungWoo Yang on 2017. 8. 31..
//

#ifndef ZAM_STDAFX_H
#define ZAM_STDAFX_H

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

#include <zam/base/io/ioSystem.h>

#ifdef zam_base_shared_EXPORTS
#define ZAMNET_API BOOST_SYMBOL_EXPORT
#else
#define ZAMNET_API BOOST_SYMBOL_VISIBLE
#endif

#endif //ZAM_STDAFX_H
