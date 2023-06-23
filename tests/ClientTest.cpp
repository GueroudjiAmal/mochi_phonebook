/*
 * (C) 2020 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include <YP/Client.hpp>
#include <YP/Provider.hpp>
#include <YP/PhonebookHandle.hpp>
#include <YP/Admin.hpp>

static constexpr const char* phonebook_config = "{ \"path\" : \"mydb\" }";
static const std::string phonebook_type = "dummy";

TEST_CASE("Client test", "[client]") {

    auto engine = thallium::engine("na+sm", THALLIUM_SERVER_MODE);
    // Initialize the provider
    YP::Provider provider(engine);
    YP::Admin admin(engine);
    std::string addr = engine.self();
    auto phonebook_id = admin.createPhonebook(addr, 0, phonebook_type, phonebook_config);

    SECTION("Open phonebook") {
        YP::Client client(engine);
        std::string addr = engine.self();

        YP::PhonebookHandle my_phonebook = client.makePhonebookHandle(addr, 0, phonebook_id);
        REQUIRE(static_cast<bool>(my_phonebook));

        auto bad_id = YP::UUID::generate();
        REQUIRE_THROWS_AS(client.makePhonebookHandle(addr, 0, bad_id), YP::Exception);
    }

    admin.destroyPhonebook(addr, 0, phonebook_id);
    engine.finalize();
}
