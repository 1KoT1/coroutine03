cmake_minimum_required(VERSION 3.10)

project(coroutine03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Poco 1.7.2 REQUIRED Foundation)

add_library(coroutine03
	src/Coroutine03/Core/QueueOneThread.cpp
	src/Coroutine03/Core/SourceEPoll.cpp
	src/Coroutine03/Core/TaskFD.cpp
	src/Coroutine03/Core/TaskRoot.cpp
	)

target_include_directories(coroutine03 PUBLIC
	include
	)

target_link_libraries(coroutine03 PUBLIC
	Poco::Foundation
	)
