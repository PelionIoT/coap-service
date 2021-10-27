/*
 * Copyright (c) 2015-2018, Pelion and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "gtest/gtest.h"
#include "test_coap_security_handler.h"
#include "mbedtls_stub.h"
#include "nsdynmemLIB_stub.h"

class CoapSecurityHandlerTest : public testing::Test
{
    void SetUp() {
    }

    void TearDown() {
    }
};

TEST(CoapSecurityHandlerTest, test_thread_security_create)
{
    ASSERT_TRUE(test_thread_security_create());
}

TEST(CoapSecurityHandlerTest, test_thread_security_destroy)
{
    ASSERT_TRUE(test_thread_security_destroy());
}

#if 0 /* Requires MbedTLS 3.0 updates to coap-service */
TEST(CoapSecurityHandlerTest, test_coap_security_handler_connect)
{
    ASSERT_TRUE(test_coap_security_handler_connect());
}
#endif

#if 0 /* Requires MbedTLS 3.0 updates to coap-service */
TEST(CoapSecurityHandlerTest, test_coap_security_handler_continue_connecting)
{
    ASSERT_TRUE(test_coap_security_handler_continue_connecting());
}
#endif

TEST(CoapSecurityHandlerTest, test_coap_security_handler_send_message)
{
    ASSERT_TRUE(test_coap_security_handler_send_message());
}

TEST(CoapSecurityHandlerTest, test_thread_security_send_close_alert)
{
    ASSERT_TRUE(test_thread_security_send_close_alert());
}

TEST(CoapSecurityHandlerTest, test_coap_security_handler_read)
{
    ASSERT_TRUE(test_coap_security_handler_read());
}
