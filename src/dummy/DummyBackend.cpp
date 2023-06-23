/*
 * (C) 2020 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include "DummyBackend.hpp"
#include <iostream>

YP_REGISTER_BACKEND(dummy, DummyPhonebook);

DummyPhonebook::DummyPhonebook(thallium::engine engine, const json& config)
: m_engine(std::move(engine)),
  m_config(config) {

}

std::string DummyPhonebook::getConfig() const {
    return m_config.dump();
}


YP::RequestResult<uint32_t> DummyPhonebook::insert(std::string name, uint64_t number) {
    YP::RequestResult<uint32_t> result;
    m_content.emplace(std::move(name), number);
    result.value() = 0;
    return result;
}

YP::RequestResult<uint64_t> DummyPhonebook::lookup(std::string name) {
    YP::RequestResult<uint64_t> result;
    auto it = m_content.find(name);
    result.value()= (it == m_content.end()) ? 0 : it->second;
    return result;
}


YP::RequestResult<bool> DummyPhonebook::destroy() {
    YP::RequestResult<bool> result;
    result.value() = true;
    // or result.success() = true
    return result;
}

std::unique_ptr<YP::Backend> DummyPhonebook::create(const thallium::engine& engine, const json& config) {
    (void)engine;
    return std::unique_ptr<YP::Backend>(new DummyPhonebook(engine, config));
}

std::unique_ptr<YP::Backend> DummyPhonebook::open(const thallium::engine& engine, const json& config) {
    (void)engine;
    return std::unique_ptr<YP::Backend>(new DummyPhonebook(engine, config));
}
