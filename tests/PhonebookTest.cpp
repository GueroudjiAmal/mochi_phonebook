/*
 * (C) 2020 The University of Chicago
 *
 * See COPYRIGHT in top-level directory.
 */
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_all.hpp>
#include <YP/Client.hpp>
#include <YP/Provider.hpp>
#include <YP/Admin.hpp>

static const std::string phonebook_type = "dummy";
static constexpr const char* phonebook_config = "{ \"path\" : \"mydb\" }";

TEST_CASE("Phonebook test", "[phonebook]") {
    auto engine = thallium::engine("na+sm", THALLIUM_SERVER_MODE);
    YP::Admin admin(engine);
    YP::Provider provider(engine);
    std::string addr = engine.self();
    auto phonebook_id = admin.createPhonebook(addr, 0, phonebook_type, phonebook_config);

    SECTION("Create PhonebookHandle") {
        YP::Client client(engine);
        std::string addr = engine.self();

        auto rh = client.makePhonebookHandle(addr, 0, phonebook_id);

        SECTION("Send Hello RPC") {
            REQUIRE_NOTHROW(rh.sayHello());
        }
        SECTION("Send Sum RPC") {
            int32_t result = 0;
            REQUIRE_NOTHROW(rh.computeSum(42, 51, &result));
            REQUIRE(result == 93);

            REQUIRE_NOTHROW(rh.computeSum(42, 51));

            YP::AsyncRequest request;
            REQUIRE_NOTHROW(rh.computeSum(42, 52, &result, &request));
            REQUIRE_NOTHROW(request.wait());
            REQUIRE(result == 94);
        }

        auto bad_id = YP::UUID::generate();
        REQUIRE_THROWS_AS(client.makePhonebookHandle(addr, 0, bad_id),
                          YP::Exception);

        REQUIRE_THROWS_AS(client.makePhonebookHandle(addr, 1, phonebook_id),
                         std::exception);
        REQUIRE_NOTHROW(client.makePhonebookHandle(addr, 0, bad_id, false));
        REQUIRE_NOTHROW(client.makePhonebookHandle(addr, 1, phonebook_id, false));
    }

    admin.destroyPhonebook(addr, 0, phonebook_id);
    engine.finalize();
}
