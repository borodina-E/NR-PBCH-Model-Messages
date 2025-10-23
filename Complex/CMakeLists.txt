cmake_minimum_required(VERSION 4.0)
project(Complex)

set(CMAKE_CXX_STANDARD 20)

# Поиск пакета GoogleTest
find_package(GTest REQUIRED)
find_package(Eigen3 REQUIRED)
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
        polarCoding.cpp
        PolarCodingInterleaverPattern.cpp
        PolarCodingInterleaverPattern.h
        PolarSequenceReliability.cpp
        kron.cpp
        kron.h
        MatrixVecMult.cpp
        MatrixVecMult.h
        polarCoding.h
        polarDecoding.cpp
        convertToEigenVector.cpp
        convertToEigenVector.h
        convertToEigenMatrix.cpp
        convertToEigenMatrix.h
        convertRowVectorToUint8.cpp
        convertRowVectorToUint8.h
        test_polar.cpp
        test_kron.cpp
        RateMatching.cpp
        RateMatchingInterleavingPattern.cpp
        RateMatchingInterleavingPattern.h
        RateRecovery.cpp
        RateRecovery.h
        test_ratematching.cpp
)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/asn1
        ${EIGEN3_INCLUDE_DIRS}
)
# линковка с GoogleTest
target_link_libraries(Complex
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libsib1.so
        GTest::gtest
        GTest::gtest_main
        Eigen3::Eigen
        pthread
)

# Автоматическое обнаружение тестов
include(GoogleTest)
gtest_discover_tests(Complex)

