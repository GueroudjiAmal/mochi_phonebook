/*
 * (C) 2020 The University of Chicago
 * 
 * See COPYRIGHT in top-level directory.
 */
#ifndef __YP_CLIENT_IMPL_H
#define __YP_CLIENT_IMPL_H

#include <thallium.hpp>
#include <thallium/serialization/stl/unordered_set.hpp>
#include <thallium/serialization/stl/unordered_map.hpp>
#include <thallium/serialization/stl/string.hpp>

namespace YP {

namespace tl = thallium;

class ClientImpl {

    public:

    tl::engine           m_engine;
    tl::remote_procedure m_check_phonebook;
    tl::remote_procedure m_say_hello;
    tl::remote_procedure m_compute_sum;
    tl::remote_procedure m_insert;
    tl::remote_procedure m_lookup;

    ClientImpl(const tl::engine& engine)
    : m_engine(engine)
    , m_check_phonebook(m_engine.define("YP_check_phonebook"))
    , m_insert(m_engine.define("YP_insert"))
    , m_lookup(m_engine.define("YP_lookup"))
    {}

    ClientImpl(margo_instance_id mid)
    : ClientImpl(tl::engine(mid)) {}

    ~ClientImpl() {}
};

}

#endif
