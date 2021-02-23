# SPDX-FileCopyrightText: 2020 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later


include(GoogleTest)

function(add_unittest test_name)
    add_executable(${test_name} ${ARGN})
    target_link_libraries(${test_name}
            GTest::gtest
            GTest::gtest_main
            ${TEST_LINK_COMPONENTS}
            )
    enable_warnings_for(${test_name})

    # Googletest's headers trigger some warnings we don't care about
    if("${CMAKE_CXX_COMPILER_ID}}" MATCHES "Clang")
        target_compile_options(${test_name} PRIVATE -Wno-global-constructors)
    endif()

    # Can either tell CTest about every single unit test, or only
    # tell it about the test executable
    #add_test(${test_name} ${CMAKE_BINARY_DIR}/${test_name})
    gtest_discover_tests(${test_name})
endfunction()

include_directories(../src)

add_subdirectory(common)