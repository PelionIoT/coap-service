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
#include "test_coap_message_handler.h"

class CoapMessageHandlerTest : public testing::Test {
    void SetUp()
    {
    }

    void TearDown()
    {
    }
};

TEST_F(CoapMessageHandlerTest, test_coap_message_handler_init)
{
    ASSERT_TRUE(test_coap_message_handler_init());
}

TEST_F(CoapMessageHandlerTest, test_coap_message_handler_destroy)
{
    ASSERT_TRUE(test_coap_message_handler_destroy());
}

TEST_F(CoapMessageHandlerTest, test_coap_message_handler_find_transaction)
{
    ASSERT_TRUE(test_coap_message_handler_find_transaction());
}

TEST_F(CoapMessageHandlerTest, test_coap_message_handler_coap_msg_process)
{
    ASSERT_TRUE(test_coap_message_handler_coap_msg_process());
}

TEST_F(CoapMessageHandlerTest, test_coap_message_handler_request_send)
{
    ASSERT_TRUE(test_coap_message_handler_request_send());
}

TEST_F(CoapMessageHandlerTest, test_coap_message_handler_response_send)
{
    ASSERT_TRUE(test_coap_message_handler_response_send());
}

TEST_F(CoapMessageHandlerTest, test_coap_message_handler_request_delete)
{
    ASSERT_TRUE(test_coap_message_handler_request_delete());
}

TEST_F(CoapMessageHandlerTest, test_coap_message_handler_request_delete_by_service_id)
{
    ASSERT_TRUE(test_coap_message_handler_request_delete_by_service_id());
}

TEST_F(CoapMessageHandlerTest, test_coap_message_handler_exec)
{
    ASSERT_TRUE(test_coap_message_handler_exec());
}


