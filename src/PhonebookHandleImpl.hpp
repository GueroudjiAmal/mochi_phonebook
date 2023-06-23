/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#ifndef __YP_PHONEBOOK_HANDLE_IMPL_H
#define __YP_PHONEBOOK_HANDLE_IMPL_H

#include <YP/UUID.hpp>

namespace YP {

class PhonebookHandleImpl {

    public:

    UUID                        m_phonebook_id;
    std::shared_ptr<ClientImpl> m_client;
    tl::provider_handle         m_ph;

    PhonebookHandleImpl() = default;
    
    PhonebookHandleImpl(const std::shared_ptr<ClientImpl>& client, 
                       tl::provider_handle&& ph,
                       const UUID& phonebook_id)
    : m_phonebook_id(phonebook_id)
    , m_client(client)
    , m_ph(std::move(ph)) {}
};

}

#endif
