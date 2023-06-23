add_executable (AdminTest AdminTest.cpp)
target_link_libraries (AdminTest PRIVATE Catch2::Catch2WithMain YP-server YP-admin)
add_test (NAME AdminTest COMMAND ./AdminTest)

add_executable (ClientTest ClientTest.cpp)
target_link_libraries (ClientTest PRIVATE Catch2::Catch2WithMain YP-server YP-client YP-admin)
add_test (NAME ClientTest COMMAND ./ClientTest)

add_executable (PhonebookTest PhonebookTest.cpp)
target_link_libraries (PhonebookTest PRIVATE Catch2::Catch2WithMain YP-server YP-client YP-admin)
add_test (NAME PhonebookTest COMMAND ./PhonebookTest)
