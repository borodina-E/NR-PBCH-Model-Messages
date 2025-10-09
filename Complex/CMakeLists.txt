cmake_minimum_required(VERSION 4.0)
project(Complex)

set(CMAKE_CXX_STANDARD 20)

# Поиск пакета GoogleTest
find_package(GTest REQUIRED)
# Включение тестирования
enable_testing()

add_executable(Complex Complex.cpp
        Complex.h
        qpskModulator.cpp
        test_complex.cpp
        test_qpskMod.cpp
        qpskModulator.h
        perEncoder.cpp
        src/cellinfo_init.c
        perEncoder.h
        main.cpp
        perDecoder.cpp
        perDecoder.h
)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/asn1
)
# линковка с GoogleTest
target_link_libraries(Complex
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsib1.so
        GTest::gtest
        GTest::gtest_main
        pthread
)
# Автоматическое обнаружение тестов
include(GoogleTest)
gtest_discover_tests(Complex)
