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
#include "test_coap_service_api.h"

class CoapServiceAPITest : public testing::Test {
    void SetUp()
    {
    }

    void TearDown()
    {
    }
};


TEST_F(CoapServiceAPITest, test_coap_service_initialize)
{
    ASSERT_TRUE(test_coap_service_initialize());
}

TEST_F(CoapServiceAPITest, test_coap_service_delete)
{
    ASSERT_TRUE(test_coap_service_delete());
}

TEST_F(CoapServiceAPITest, test_coap_service_virtual_socket_recv)
{
    ASSERT_TRUE(test_coap_service_virtual_socket_recv());
}

TEST_F(CoapServiceAPITest, test_coap_service_virtual_socket_set_cb)
{
    ASSERT_TRUE(test_coap_service_virtual_socket_set_cb());
}

TEST_F(CoapServiceAPITest, test_coap_service_register_uri)
{
    ASSERT_TRUE(test_coap_service_register_uri());
}

TEST_F(CoapServiceAPITest, test_coap_service_unregister_uri)
{
    ASSERT_TRUE(test_coap_service_unregister_uri());
}

TEST_F(CoapServiceAPITest, test_coap_service_request_send)
{
    ASSERT_TRUE(test_coap_service_request_send());
}

TEST_F(CoapServiceAPITest, test_coap_service_request_delete)
{
    ASSERT_TRUE(test_coap_service_request_delete());
}

TEST_F(CoapServiceAPITest, test_coap_service_request_delete_by_service_id)
{
    ASSERT_TRUE(test_coap_service_request_delete_by_service_id());
}

TEST_F(CoapServiceAPITest, test_coap_service_response_send)
{
    ASSERT_TRUE(test_coap_service_response_send());
}

TEST_F(CoapServiceAPITest, test_coap_callbacks)
{
    ASSERT_TRUE(test_coap_callbacks());
}

TEST_F(CoapServiceAPITest, test_eventOS_callbacks)
{
    ASSERT_TRUE(test_eventOS_callbacks());
}

TEST_F(CoapServiceAPITest, test_conn_handler_callbacks)
{
    ASSERT_TRUE(test_conn_handler_callbacks());
}

TEST_F(CoapServiceAPITest, test_certificate_set)
{
    ASSERT_TRUE(test_certificate_set());
}

TEST_F(CoapServiceAPITest, test_handshake_timeout_set)
{
    ASSERT_TRUE(test_handshake_timeout_set());
}

TEST_F(CoapServiceAPITest, test_coap_duplcate_msg_buffer_set)
{
    ASSERT_TRUE(test_coap_duplcate_msg_buffer_set());
}

TEST_F(CoapServiceAPITest, test_coap_service_get_internal_timer_ticks)
{
    ASSERT_TRUE(test_coap_service_get_internal_timer_ticks());
}

TEST_F(CoapServiceAPITest, test_coap_service_if_find_by_socket)
{
    ASSERT_TRUE(test_coap_service_if_find_by_socket());
}

TEST_F(CoapServiceAPITest, test_coap_service_handshake_limit_set)
{
    ASSERT_TRUE(test_coap_service_handshake_limit_set());
}

TEST_F(CoapServiceAPITest, test_coap_service_msg_prevalidate_cb_read_and_set)
{
    ASSERT_TRUE(test_coap_service_msg_prevalidate_cb_read_and_set());
}

