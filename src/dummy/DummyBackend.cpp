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

void DummyPhonebook::sayHello() {
    std::cout << "Hello World" << std::endl;
}

std::string DummyPhonebook::getConfig() const {
    return m_config.dump();
}

YP::RequestResult<int32_t> DummyPhonebook::computeSum(int32_t x, int32_t y) {
    YP::RequestResult<int32_t> result;
    result.value() = x + y;
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
