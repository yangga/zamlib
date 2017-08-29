#!/bin/bash
rm -rf ZamConfig.h
rm -rf build

SUB_PRJS=". base net"
for D in $SUB_PRJS
do
	rm -rf ${D}/CMakeFiles
	rm -rf ${D}/CMakeCache.txt
	rm -rf ${D}/Makefile
	rm -rf ${D}/cmake_install.cmake
	rm -rf ${D}/cmake-build-debug
done
