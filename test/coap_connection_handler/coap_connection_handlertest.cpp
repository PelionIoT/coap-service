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
#include "test_coap_connection_handler.h"

class CoapConnectionHandlerTest : public testing::Test
{
    void SetUp() {
    }

    void TearDown() {
    }
};

TEST_F(CoapConnectionHandlerTest, testConnectionHandlerCreate)
{
    ASSERT_TRUE(test_connection_handler_create());
}

TEST_F(CoapConnectionHandlerTest, testConnectionHandlerDestroy)
{
    ASSERT_TRUE(test_connection_handler_destroy());
}

TEST_F(CoapConnectionHandlerTest, testConnectionHandlerConnection)
{
    ASSERT_TRUE(test_coap_connection_handler_open_connection());
}

TEST_F(CoapConnectionHandlerTest, testConnectionHandlerSendData)
{
    ASSERT_TRUE(test_coap_connection_handler_send_data());
}

TEST_F(CoapConnectionHandlerTest, testConnectionHandlerVirtualRecv)
{
    ASSERT_TRUE(test_coap_connection_handler_virtual_recv());
}

TEST_F(CoapConnectionHandlerTest, testConnectionHandlerSocketBelongsTo)
{
    ASSERT_TRUE(test_coap_connection_handler_socket_belongs_to());
}

TEST_F(CoapConnectionHandlerTest, testTimerCallbacks)
{
    ASSERT_TRUE(test_timer_callbacks());
}

TEST_F(CoapConnectionHandlerTest, testSocketApiCallbacks)
{
    ASSERT_TRUE(test_socket_api_callbacks());
}

TEST_F(CoapConnectionHandlerTest, testSecurityCallbacks)
{
    ASSERT_TRUE(test_security_callbacks());
}

TEST_F(CoapConnectionHandlerTest, testConnectionHandlerMsgPrevalidateCbReadAndSet)
{
    ASSERT_TRUE(test_coap_connection_handler_msg_prevalidate_cb_read_and_set());
}

TEST_F(CoapConnectionHandlerTest, testConnectionHandlerFindBySocketPort)
{
    ASSERT_TRUE(test_coap_connection_handler_find_by_socket_port());
}
