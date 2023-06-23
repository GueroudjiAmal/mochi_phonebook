/*
 * (C) 2020 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#ifndef __YP_PHONEBOOK_HANDLE_HPP
#define __YP_PHONEBOOK_HANDLE_HPP

#include <thallium.hpp>
#include <memory>
#include <unordered_set>
#include <nlohmann/json.hpp>
#include <YP/Client.hpp>
#include <YP/Exception.hpp>
#include <YP/AsyncRequest.hpp>

namespace YP {

namespace tl = thallium;

class Client;
class PhonebookHandleImpl;

/**
 * @brief A PhonebookHandle object is a handle for a remote phonebook
 * on a server. It enables invoking the phonebook's functionalities.
 */
class PhonebookHandle {

    friend class Client;

    public:

    /**
     * @brief Constructor. The resulting PhonebookHandle handle will be invalid.
     */
    PhonebookHandle();

    /**
     * @brief Copy-constructor.
     */
    PhonebookHandle(const PhonebookHandle&);

    /**
     * @brief Move-constructor.
     */
    PhonebookHandle(PhonebookHandle&&);

    /**
     * @brief Copy-assignment operator.
     */
    PhonebookHandle& operator=(const PhonebookHandle&);

    /**
     * @brief Move-assignment operator.
     */
    PhonebookHandle& operator=(PhonebookHandle&&);

    /**
     * @brief Destructor.
     */
    ~PhonebookHandle();

    /**
     * @brief Returns the client this phonebook has been opened with.
     */
    Client client() const;


    /**
     * @brief Checks if the PhonebookHandle instance is valid.
     */
    operator bool() const;
    
    /**
     * @brief Requests the target phonebook to insert a new entry.
     * If result is null, it will be ignored. If req is not null, this call
     * will be non-blocking and the caller is responsible for waiting on
     * the request.
     *
     * @param[in] name name of the caller
     * @param[in] number number of the caller
     * @param[out] result 0 if inserted 99 else
     * @param[out] req request for a non-blocking operation
     */
    void insert(std::string name, uint64_t number,
                    uint32_t* result = nullptr,
                    AsyncRequest* req = nullptr);

    /**
     * @brief Requests the target phonebook to lookup for a name and returns the number.
     * If result is null, it will be ignored. If req is not null, this call
     * will be non-blocking and the caller is responsible for waiting on
     * the request.
     *
     * @param[in] name name of the caller
     * @param[out] result number of the caller
     * @param[out] req request for a non-blocking operation
     */
    void lookup(std::string name,
                    uint64_t* result = nullptr,
                    AsyncRequest* req = nullptr) const;    


    private:

    /**
     * @brief Constructor is private. Use a Client object
     * to create a PhonebookHandle instance.
     *
     * @param impl Pointer to implementation.
     */
    PhonebookHandle(const std::shared_ptr<PhonebookHandleImpl>& impl);

    std::shared_ptr<PhonebookHandleImpl> self;
};

}

#endif
