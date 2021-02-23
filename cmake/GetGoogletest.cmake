# SPDX-FileCopyrightText: 2021 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

#[=======================================================================[.rst:
GetGoogletest
-------

Downloads and configures Googletest library using the FetchContent CMake module.
This is an alternative to CMake's provided FindGTest.

Depending on updates to CMake and/or Googletest this may need to update. Additionally,
this approach downloads Google Test from Github and a network connection may not always
be acceptable

Imported Targets
^^^^^^^^^^^^^^^^

This module provides the following imported targets:

``GTest::GTest``
  The Googletest library, if found, matching FindGTest
``GTest::Main``
  The Google Test gtest_main library, if found, matching FindGTest

``GTest::gtest``
  The Googletest library, if found, matching Googletest's names
``GTest::gtest_main``
  The Google Test gtest_main library, if found, matching Googletest's names
``GTest::gmock``
  The Google Test gmock library, if found, matching Googletest's names
``GTest::gmock_main``
  The Google Test gmock_main library, if found, matching Googletest's names

Result Variables
^^^^^^^^^^^^^^^^

This will define the following variables:

``googletest_POPULATED``
  True if Googletest has been downloaded and configured

#]=======================================================================]


include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  #GIT_TAG release-1.10.0
)

FetchContent_GetProperties(googletest)
string(TOLOWER "googletest" lcName)
if(NOT ${lcName}_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${${lcName}_SOURCE_DIR} ${${lcName}_BINARY_DIR})

  # Some of these may become redundant in the future if/when
  # https://github.com/google/googletest/issues/2429 is fixed
  add_library(GTest::gtest ALIAS gtest)
  add_library(GTest::gtest_main ALIAS gtest_main)
  add_library(GTest::gmock ALIAS gmock)
  add_library(GTest::gmock_main ALIAS gmock_main)

  # Add alias names that match CMake's FindGTest module
  add_library(GTest::GTest ALIAS gtest)
  add_library(GTest::Main ALIAS gtest_main)
endif()
