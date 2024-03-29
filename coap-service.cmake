#################################################################################
## Copyright 2020-2021 Pelion.
##
## SPDX-License-Identifier: Apache-2.0
##
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
##     http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
#################################################################################

if (NOT TARGET "mbed-nanostack-coap_service" AND NOT TARGET "mbed-nanostack")
# Targets not defined in upper level CMakeLists, define them here to allow unit tests local compilation
# Please note, targets are not linked anywhere

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

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNS_USE_EXTERNAL_MBED_TLS -DMBEDTLS_ECJPAKE_C -DMBEDTLS_KEY_EXCHANGE_ECJPAKE_ENABLED")
message(STATUS "CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}")

set(COAP_COMMON_TEST_STUBS
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

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test/stubs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/coap-service)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/source/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test/stub)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../nanostack/nanostack)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libService/exported-libs/mbed-client-libservice/mbed-client-libservice/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libService/exported-libs/mbed-client-libservice/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libService/exported-libs/mbed-trace)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libService/exported-libs/mbed-trace/mbed-trace)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../libService/exported-libs/mbed-client-randlib/mbed-client-randlib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../mbed-coap/mbed-coap)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../mbed-coap)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../event-loop/nanostack-event-loop)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../mbedtls/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../event-loop/source)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../mbed-coap/source/include)

# coap-connection-handler
set(COAP_CONNECTION_HANDLER_TEST_STUBS
    test/stub/coap_message_handler_stub.c
    test/stub/coap_security_handler_stub.c
    test/stub/coap_service_api_stub.c
    ${COAP_COMMON_TEST_STUBS}
)

set(COAP_CONNECTION_HANDLER_SOURCES
    source/coap_connection_handler.c
)

add_executable(coap_connection_handler_test EXCLUDE_FROM_ALL
    ${COAP_CONNECTION_HANDLER_SOURCES}
    test/coap_connection_handler/coap_connection_handlertest.cpp
    test/coap_connection_handler/test_coap_connection_handler.c
    ${COAP_CONNECTION_HANDLER_TEST_STUBS}
)

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

target_link_libraries(
    coap_connection_handler_test
    gtest_main
)

# GTest framework requires C++ version 11
set_target_properties(coap_connection_handler_test
PROPERTIES
    CXX_STANDARD 11
)

# coap-message-handler
set(COAP_MESSAGE_HANDLER_TEST_STUBS
    test/stub/coap_connection_handler_stub.c
    test/stub/coap_security_handler_stub.c
    test/stub/coap_service_api_stub.c
    ${COAP_COMMON_TEST_STUBS}
)

# coap_message_handler.c is included to the test file - no need to compile it separately
#set(COAP_MESSAGE_HANDLER_SOURCES
#    source/coap_message_handler.c
#)

add_executable(coap_message_handler_test EXCLUDE_FROM_ALL
    #${COAP_MESSAGE_HANDLER_SOURCES}
    test/coap_message_handler/coap_message_handlertest.cpp
    test/coap_message_handler/test_coap_message_handler.c
    ${COAP_MESSAGE_HANDLER_TEST_STUBS}
)

# c-file included in the test_coap_message_handler
target_include_directories(coap_message_handler_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source)

add_test(coap_message_handler_test coap_message_handler_test)

if (TARGET check)
    add_dependencies(check coap_message_handler_test)
else()
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                  DEPENDS coap_message_handler_test)
endif()

target_link_libraries(
    coap_message_handler_test
    gtest_main
)

set_target_properties(coap_message_handler_test
PROPERTIES
    CXX_STANDARD 11
)

# coap-security-handler
set(COAP_SECURITY_HANDLER_TEST_STUBS
    test/stub/coap_connection_handler_stub.c
    test/stub/coap_message_handler_stub.c
    test/stub/coap_service_api_stub.c
    ${COAP_COMMON_TEST_STUBS}
)

set(COAP_SECURITY_HANDLER_SOURCES
    source/coap_security_handler.c
)

add_executable(coap_security_handler_test EXCLUDE_FROM_ALL
    ${COAP_SECURITY_HANDLER_SOURCES}
    test/coap_security_handler/coap_security_handlertest.cpp
    test/coap_security_handler/test_coap_security_handler.c
    ${COAP_SECURITY_HANDLER_TEST_STUBS}
)

add_test(coap_security_handler_test coap_security_handler_test)

if (TARGET check)
    add_dependencies(check coap_security_handler_test)
else()
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                  DEPENDS coap_security_handler_test)
endif()

target_link_libraries(
    coap_security_handler_test
    gtest_main
)

set_target_properties(coap_security_handler_test
PROPERTIES
    CXX_STANDARD 11
)

# coap-service-api
set(COAP_SERVICE_API_TEST_STUBS
    test/stub/coap_connection_handler_stub.c
    test/stub/coap_message_handler_stub.c
    test/stub/coap_security_handler_stub.c
    ${COAP_COMMON_TEST_STUBS}
)
# coap-service-api.c is includsed directly to test code
#set(COAP_SERVICE_API_SOURCES
#    source/coap_service_api.c
#)

add_executable(coap_service_api_test EXCLUDE_FROM_ALL
    #${COAP_SERVICE_API_SOURCES}
    test/coap_service_api/coap_service_apitest.cpp
    test/coap_service_api/test_coap_service_api.c
    ${COAP_SERVICE_API_TEST_STUBS}
)

# c-file included directly to the test_coap_service_api.c
target_include_directories(coap_service_api_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source)

add_test(coap_service_api_test coap_service_api_test)

if (TARGET check)
    add_dependencies(check coap_service_api_test)
else()
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
                  DEPENDS coap_service_api_test)
endif()

target_link_libraries(
    coap_service_api_test
    gtest_main
)

set_target_properties(coap_service_api_test
PROPERTIES
    CXX_STANDARD 11
)

include(GoogleTest)
gtest_discover_tests(coap_connection_handler_test EXTRA_ARGS --gtest_output=xml: XML_OUTPUT_DIR coap_connection_handler)
gtest_discover_tests(coap_message_handler_test EXTRA_ARGS --gtest_output=xml: XML_OUTPUT_DIR coap_message_handler)
gtest_discover_tests(coap_security_handler_test EXTRA_ARGS --gtest_output=xml: XML_OUTPUT_DIR coap_security_handler_test)
gtest_discover_tests(coap_service_api_test EXTRA_ARGS --gtest_output=xml: XML_OUTPUT_DIR coap_service_api_test)

if (enable_coverage_data AND ${CMAKE_PROJECT_NAME} STREQUAL "coap-service-unit-test")
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/html")

    add_test(NAME ls_cov WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMAND ${BASH} -c "gcovr -r . -e ${CMAKE_CURRENT_SOURCE_DIR}/build -e '.*test.*' --html --html-details -o build/html/coverity_index.html"
    )
endif ()
