cmake_minimum_required(VERSION 4.0)
project(qpsk_demodulate)

set(CMAKE_CXX_STANDARD 20)

# Поиск пакета GoogleTest
find_package(GTest REQUIRED)
find_package(Eigen3 REQUIRED)

# Включение тестирования
enable_testing()

# Основная программа
add_executable(qpsk_demodulate main.cpp
        qpskDemodulator.cpp
        scrambling.cpp
        scram.h
        sequenceScrambling.cpp
        attachParityBits.cpp
        verifyParityBits.cpp
        dlsch_info.cpp
        dlsch_info.h
        segmented.cpp
        attachPbitsMatrix.cpp
        desegmented.cpp
        verifyPbitsMatrix.cpp

)

include_directories(
        ${EIGEN3_INCLUDE_DIRS}
)
# Отдельный исполняемый файл для тестов 1   qpskDemodulation
add_executable(qpsk_tests test_qpskDemod.cpp
        qpskDemodulator.cpp

)

# Отдельный исполняемый файл для тестов 2   Scrambling
add_executable(scrambling_tests test_scrambling.cpp
        scrambling.cpp
        sequenceScrambling.cpp

)

# Отдельный исполняемый файл для тестов 3   Scrambling sequence
add_executable(scrambling_sequence_tests test_scrambling_sequence.cpp
        sequenceScrambling.cpp

)

# Отдельный исполняемый файл для тестов 4 AttachParityBits
add_executable(parity_tests test_attachParity.cpp
        attachParityBits.cpp
        verifyParityBits.cpp

)

# Отдельный исполняемый файл для тестов 5 Segmented
add_executable(segmented_tests test_segment.cpp
        segmented.cpp
        desegmented.cpp
        attachParityBits.cpp
        dlsch_info.cpp
        attachPbitsMatrix.cpp
        verifyPbitsMatrix.cpp
        verifyParityBits.cpp

)

# линковка с GoogleTest (подключение) 0
target_link_libraries(qpsk_demodulate
        Eigen3::Eigen
)


# линковка с GoogleTest (подключение) 1
target_link_libraries(qpsk_tests
        GTest::gtest
        GTest::gtest_main
        pthread
)

# Автоматическое обнаружение тестов 1
include(GoogleTest)
gtest_discover_tests(qpsk_tests)


# линковка с GoogleTest (подключение) 2
target_link_libraries(scrambling_tests
        GTest::gtest
        GTest::gtest_main
        pthread
)

# Автоматическое обнаружение тестов 2
include(GoogleTest)
gtest_discover_tests(scrambling_tests)


# линковка с GoogleTest (подключение) 3
target_link_libraries(scrambling_sequence_tests
        GTest::gtest
        GTest::gtest_main
        pthread
)

# Автоматическое обнаружение тестов 3
include(GoogleTest)
gtest_discover_tests(scrambling_sequence_tests)


# линковка с GoogleTest (подключение) 4
target_link_libraries(parity_tests
        GTest::gtest
        GTest::gtest_main
        pthread
)

# Автоматическое обнаружение тестов 4
include(GoogleTest)
gtest_discover_tests(parity_tests)

# линковка с GoogleTest (подключение) 5
target_link_libraries(segmented_tests
        GTest::gtest
        GTest::gtest_main
        pthread
)

# Автоматическое обнаружение тестов 5
include(GoogleTest)
gtest_discover_tests(segmented_tests)