//
// Created by SungWoo Yang on 2017. 9. 26..
//

#ifndef ZAMLIB_MACRO_H
#define ZAMLIB_MACRO_H

#define __concatenate__(_a, _b)		_a##_b
#define ZAM_CONCATENATE(_a, _b) __concatenate__(_a,_b)

#define ZAM_LOCK(_mutex) boost::lock_guard<std::decay_t<decltype(_mutex)>> ZAM_CONCATENATE(__lock_vari__, __LINE__)(_mutex)
#define ZAM_LOCK_SHARED(_shared_mutex) boost::shared_lock<decltype(_shared_mutex)> ZAM_CONCATENATE(__lock_vari__, __LINE__)(_shared_mutex)

#define ZAM_LOCK_UNIQUE(_mutex, _guard_name) boost::unique_lock<std::decay_t<decltype(_mutex)>> _guard_name(_mutex)

#endif //ZAMLIB_MACRO_H
