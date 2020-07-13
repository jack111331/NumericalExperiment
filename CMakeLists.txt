cmake_minimum_required(VERSION 3.16)
project(NumericalExperiment)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_LIST)
set(HEADER_LIST)

list(APPEND SOURCE_LIST
        EulerMethod.cpp
        MidpointMethod.cpp
        FunctionOne.cpp
        ObjectiveFunctionOne.cpp
        QuasiNewtonMethod.cpp)

list(APPEND HEADER_LIST
        EulerMethod.h
        MidpointMethod.h
        Derivative.h
        FunctionOne.h
        ObjectiveFunctionOne.h
        QuasiNewtonMethod.h)

add_executable(NumericalExperiment main.cpp ${HEADER_LIST} ${SOURCE_LIST})