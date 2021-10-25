# Copyright (c) 2020-2021 ARM Limited. All rights reserved.
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.0...3.19)

if (NOT TARGET "mbed-nanostack-coap_service" AND NOT TARGET "mbed-nanostack")
# Targets not defined in upper level CMakeLists, define them here to allow unit tests local compilation
# Please note, targets are not linked anywhere

project("coap-service-unit-test")

include(FindUnixCommands)

include(repositories.cmake)

option(enable_coverage_data "Enable Coverage data" OFF)

add_library(mbed-nanostack-coap_service source/coap_connection_handler.c)
add_library(mbed-nanostack source/coap_connection_handler.c)

endif()

target_include_directories(mbed-nanostack-coap_service
    INTERFACE
        .
        ./coap-service
        ./source/include
)

target_sources(mbed-nanostack-coap_service
    INTERFACE
        source/coap_connection_handler.c
        source/coap_message_handler.c
        source/coap_security_handler.c
        source/coap_service_api.c
)

target_link_libraries(mbed-nanostack
    INTERFACE
        mbed-coap
)

#Tests after this line
enable_testing()

if (enable_coverage_data)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif ()

set(COAP_CONNECTION_HANDLER_SOURCES
    source/coap_connection_handler.c
)

set(COAP_SOURCES
    ${COAP_CONNECTION_HANDLER_SOURCES}
    source/coap_message_handler.c
    source/coap_security_handler.c
    source/coap_service_api.c)

set(COAP_CONNECTION_HANDLER_TEST_STUBS
    test/stub/coap_message_handler_stub.c
    test/stub/coap_security_handler_stub.c
    test/stub/coap_service_api_stub.c
    test/stub/common_functions_stub.c
    test/stub/eventOS_event_stub.c
    test/stub/mbedtls_stub.c
    test/stub/mbed_trace_stub.c
    test/stub/nsdynmemLIB_stub.c
    test/stub/ns_list_stub.c
    test/stub/ns_timer_stub.c
    test/stub/randLIB_stub.c
    test/stub/sn_coap_builder_stub.c
    test/stub/sn_coap_parser_stub.c
    test/stub/sn_coap_protocol_stub.c
    test/stub/socket_api_stub.c
    test/stub/system_timer_stub.c
    test/stub/timeout_stub.c
)

add_executable(coap_connection_handler_test EXCLUDE_FROM_ALL
    ${COAP_CONNECTION_HANDLER_SOURCES}
    test/coap_connection_handler/coap_connection_handlertest.cpp
    test/coap_connection_handler/test_coap_connection_handler.c
    ${COAP_CONNECTION_HANDLER_TEST_STUBS}
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99 -DNS_USE_EXTERNAL_MBED_TLS=ON")
message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")

# make check, this must be after add_executable!
add_test(coap_connection_handler_test coap_connection_handler_test)
if (TARGET check)
    add_dependencies(check coap_connection_handler_test)
else()
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                  DEPENDS coap_connection_handler_test)
endif()

# define includes after add_executable
message(STATUS "CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/coap-service)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source/include)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/test/stub)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../nanostack/nanostack)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../libService/exported-libs/mbed-client-libservice/mbed-client-libservice/)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../libService/exported-libs/mbed-client-libservice/)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../libService/libService)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../libService/exported-libs/mbed-trace)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../libService/exported-libs/mbed-trace/mbed-trace)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../libService/exported-libs/mbed-client-randlib/mbed-client-randlib)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../mbed-coap/mbed-coap)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../mbed-coap)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../event-loop/nanostack-event-loop)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../mbedtls/include)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../mbedtls/include/mbedtls)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../event-loop/source)
target_include_directories(coap_connection_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../mbed-coap/source/include)




target_link_libraries(
    coap_connection_handler_test
    gtest_main
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test/stubs)

# GTest framework requires C++ version 11
set_target_properties(coap_connection_handler_test
PROPERTIES
    CXX_STANDARD 11
)

include(GoogleTest)
gtest_discover_tests(coap_connection_handler_test EXTRA_ARGS --gtest_output=xml: XML_OUTPUT_DIR coap_connection_handler)

if (enable_coverage_data AND ${CMAKE_PROJECT_NAME} STREQUAL "coap-service-unit-test")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html")

    add_test(NAME ls_cov WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${BASH} -c "gcovr -r . -e ${CMAKE_CURRENT_SOURCE_DIR}/build -e '.*test.*' --html --html-details -o build/html/coverity_index.html"
    )
endif ()
