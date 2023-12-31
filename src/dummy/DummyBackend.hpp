/*
 * (C) 2020 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#ifndef __DUMMY_BACKEND_HPP
#define __DUMMY_BACKEND_HPP

#include <YP/Backend.hpp>

using json = nlohmann::json;

/**
 * Dummy implementation of an YP Backend.
 */
class DummyPhonebook : public YP::Backend {

    thallium::engine m_engine;
    json             m_config;
    std::unordered_map<std::string,uint64_t> m_content;

    public:

    /**
     * @brief Constructor.
     */
    DummyPhonebook(thallium::engine engine, const json& config);

    /**
     * @brief Move-constructor.
     */
    DummyPhonebook(DummyPhonebook&&) = default;

    /**
     * @brief Copy-constructor.
     */
    DummyPhonebook(const DummyPhonebook&) = default;

    /**
     * @brief Move-assignment operator.
     */
    DummyPhonebook& operator=(DummyPhonebook&&) = default;

    /**
     * @brief Copy-assignment operator.
     */
    DummyPhonebook& operator=(const DummyPhonebook&) = default;

    /**
     * @brief Destructor.
     */
    virtual ~DummyPhonebook() = default;

    /**
     * @brief Get the phonebook's configuration as a JSON-formatted string.
     */
    std::string getConfig() const override;

    /**
     * @brief Inserts a new entry to the phonebook.
     *
     * @param name the name
     * @param number the number
     *
     * @return a RequestResult containing 0 if the inserssion is done.
     */
    YP::RequestResult<uint32_t> insert(std::string name, uint64_t number) override;

    /**
     * @brief lookup for a number in the phonebook.
     *
     * @param name the name
     *
     * @return a RequestResult containing the number if found 99 else.
     */
    YP::RequestResult<uint64_t> lookup(std::string name) override;


    /**
     * @brief Destroys the underlying phonebook.
     *
     * @return a RequestResult<bool> instance indicating
     * whether the database was successfully destroyed.
     */
    YP::RequestResult<bool> destroy() override;

    /**
     * @brief Static factory function used by the PhonebookFactory to
     * create a DummyPhonebook.
     *
     * @param engine Thallium engine
     * @param config JSON configuration for the phonebook
     *
     * @return a unique_ptr to a phonebook
     */
    static std::unique_ptr<YP::Backend> create(const thallium::engine& engine, const json& config);

    /**
     * @brief Static factory function used by the PhonebookFactory to
     * open a DummyPhonebook.
     *
     * @param engine Thallium engine
     * @param config JSON configuration for the phonebook
     *
     * @return a unique_ptr to a phonebook
     */
    static std::unique_ptr<YP::Backend> open(const thallium::engine& engine, const json& config);
};

#endif
