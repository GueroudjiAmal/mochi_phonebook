/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#include "YP/PhonebookHandle.hpp"
#include "YP/RequestResult.hpp"
#include "YP/Exception.hpp"

#include "AsyncRequestImpl.hpp"
#include "ClientImpl.hpp"
#include "PhonebookHandleImpl.hpp"

#include <thallium/serialization/stl/string.hpp>
#include <thallium/serialization/stl/pair.hpp>

namespace YP {

PhonebookHandle::PhonebookHandle() = default;

PhonebookHandle::PhonebookHandle(const std::shared_ptr<PhonebookHandleImpl>& impl)
: self(impl) {}

PhonebookHandle::PhonebookHandle(const PhonebookHandle&) = default;

PhonebookHandle::PhonebookHandle(PhonebookHandle&&) = default;

PhonebookHandle& PhonebookHandle::operator=(const PhonebookHandle&) = default;

PhonebookHandle& PhonebookHandle::operator=(PhonebookHandle&&) = default;

PhonebookHandle::~PhonebookHandle() = default;

PhonebookHandle::operator bool() const {
    return static_cast<bool>(self);
}

Client PhonebookHandle::client() const {
    return Client(self->m_client);
}

void PhonebookHandle::insert(
        std::string name, uint64_t number,
        uint32_t* result,
        AsyncRequest* req)
{
    if(not self) throw Exception("Invalid YP::PhonebookHandle object");
    auto& rpc = self->m_client->m_insert;
    auto& ph  = self->m_ph;
    auto& phonebook_id = self->m_phonebook_id;
    if(req == nullptr) { // synchronous call
        RequestResult<int32_t> response = rpc.on(ph)(phonebook_id, name, number);
        if(response.success()) {
            if(result) *result = response.value();
        } else {
            throw Exception(response.error());
        }
    } else { // asynchronous call
        auto async_response = rpc.on(ph).async(phonebook_id, name, number);
        auto async_request_impl =
            std::make_shared<AsyncRequestImpl>(std::move(async_response));
        async_request_impl->m_wait_callback =
            [result](AsyncRequestImpl& async_request_impl) {
                RequestResult<int32_t> response =
                    async_request_impl.m_async_response.wait();
                    if(response.success()) {
                        if(result) *result = response.value();
                    } else {
                        throw Exception(response.error());
                    }
            };
        *req = AsyncRequest(std::move(async_request_impl));
    }
}

void PhonebookHandle::lookup(
        std::string name, 
        uint64_t* result,
        AsyncRequest* req) const
{
    if(not self) throw Exception("Invalid YP::PhonebookHandle object");
    auto& rpc = self->m_client->m_lookup;
    auto& ph  = self->m_ph;
    auto& phonebook_id = self->m_phonebook_id;
    if(req == nullptr) { // synchronous call
        RequestResult<int32_t> response = rpc.on(ph)(phonebook_id, name);
        if(response.success()) {
            if(result) *result = response.value();
        } else {
            throw Exception(response.error());
        }
    } else { // asynchronous call
        auto async_response = rpc.on(ph).async(phonebook_id, name);
        auto async_request_impl =
            std::make_shared<AsyncRequestImpl>(std::move(async_response));
        async_request_impl->m_wait_callback =
            [result](AsyncRequestImpl& async_request_impl) {
                RequestResult<int32_t> response =
                    async_request_impl.m_async_response.wait();
                    if(response.success()) {
                        if(result) *result = response.value();
                    } else {
                        throw Exception(response.error());
                    }
            };
        *req = AsyncRequest(std::move(async_request_impl));
    }
}

}
