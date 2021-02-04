# SPDX-FileCopyrightText: 2021 Number6174
# SPDX-License-Identifier: GPL-3.0-or-later

#[=======================================================================[.rst:
CompilerSetup
-------

Provides functions to turn on lots of compiler warnings for a specified target,
enable color output, and so forth

Functions
^^^^^^^^^^^^^^^^

This module provides the following functions:

``enable_warnings_for(<target>)``
  Turns on warnings for the specified target

``colorize_output()``
  Turns on color diagnostics, sometimes needed

#]=======================================================================]

include(CheckCXXCompilerFlag)

macro(_add_flag _flag)
  string(REGEX REPLACE "[^A-Za-z0-9]" "" _flagvar "${_flag}")
  check_cxx_compiler_flag(${_flag} SUPPORTS_WARNING_${_flagvar})
  if(SUPPORTS_WARNING_${_flagvar})
    target_compile_options(${target} PRIVATE "${_flag}")
  endif()
endmacro()

function(enable_warnings_for target)
  # Maybe these should be generator expressions instead, but this seems to
  # work just fine
  if("${CMAKE_CXX_COMPILER_ID}}" MATCHES "Clang")
    # Matches is used to allow for Clang or AppleClang

    # Use theory of turn on all warnings, but disable ones that we don't care about
    _add_flag(${target} PRIVATE -Weverything)
    _add_flag(${target} PRIVATE -Wno-c++98-compat)
    _add_flag(${target} PRIVATE -Wno-c++98-compat-pedantic)
    _add_flag(${target} PRIVATE -Wno-padded)
    _add_flag(${target} PRIVATE -Wno-documentation-unknown-command)
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # Large warning groups
    _add_flag("-Wall")
    _add_flag(${target} PRIVATE -Wextra)
    _add_flag(${target} PRIVATE -Wpedantic)
    # Individual warnings
    _add_flag(${target} PRIVATE -Walloc-zero)
    _add_flag(${target} PRIVATE -Wcast-align)
    _add_flag(${target} PRIVATE -Wcast-qual)
    _add_flag(${target} PRIVATE -Wconditionally-supported)
    _add_flag(${target} PRIVATE -Wconversion)
    _add_flag(${target} PRIVATE -Wctor-dtor-privacy)
    _add_flag(${target} PRIVATE -Wdate-time)
    _add_flag(${target} PRIVATE -Wdeprecated-copy-dtor)
    _add_flag(${target} PRIVATE -Wdouble-promotion)
    _add_flag(${target} PRIVATE -Wduplicated-branches)
    _add_flag(${target} PRIVATE -Wduplicated-cond)
    _add_flag(${target} PRIVATE -Wextra-semi)
    _add_flag(${target} PRIVATE -Wfloat-equal)
    _add_flag(${target} PRIVATE -Wformat=2)
    _add_flag(${target} PRIVATE -Wlogical-op)
    _add_flag(${target} PRIVATE -Wmissing-declarations)
    _add_flag(${target} PRIVATE -Wmissing-profile)
    _add_flag(${target} PRIVATE -Wno-long-long)
    _add_flag(${target} PRIVATE -Wno-pmf-conversions)
    _add_flag(${target} PRIVATE -Wnoexcept)
    _add_flag(${target} PRIVATE -Wnon-virtual-dtor)
    _add_flag(${target} PRIVATE -Wnormalized)
    _add_flag(${target} PRIVATE -Wnull-dereference)
    _add_flag(${target} PRIVATE -Wold-style-cast)
    _add_flag(${target} PRIVATE -Woverloaded-virtual)
    _add_flag(${target} PRIVATE -Wpacked)
    _add_flag(${target} PRIVATE -Wparentheses)
    _add_flag(${target} PRIVATE -Wredundant-decls)
    _add_flag(${target} PRIVATE -Wshadow)
    _add_flag(${target} PRIVATE -Wsign-conversion)
    _add_flag(${target} PRIVATE -Wsign-promo)
    _add_flag(${target} PRIVATE -Wstrict-null-sentinel)
    _add_flag(${target} PRIVATE -Wsuggest-attribute=const)
    _add_flag(${target} PRIVATE -Wsuggest-attribute=malloc)
    _add_flag(${target} PRIVATE -Wsuggest-attribute=noreturn)
    _add_flag(${target} PRIVATE -Wsuggest-attribute=pure)
    _add_flag(${target} PRIVATE -Wsuggest-final-methods)
    _add_flag(${target} PRIVATE -Wsuggest-final-types)
    _add_flag(${target} PRIVATE -Wsuggest-override)
    _add_flag(${target} PRIVATE -Wswitch-enum)
    _add_flag(${target} PRIVATE -Wuninitialized)
    _add_flag(${target} PRIVATE -Wundef)
    _add_flag(${target} PRIVATE -Wunsafe-loop-optimizations)
    _add_flag(${target} PRIVATE -Wunused)
    _add_flag(${target} PRIVATE -Wunused-macros)
    _add_flag(${target} PRIVATE -Wuseless-cast)
    _add_flag(${target} PRIVATE -Wvla)
    _add_flag(${target} PRIVATE -Wwrite-strings)
    _add_flag(${target} PRIVATE -Wzero-as-null-pointer-constant)

  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    _add_flag(${target} PRIVATE /W3)
  else()
    message(WARNING "Unknown compiler '${CMAKE_CXX_COMPILER_ID}', no warnings set")
  endif()
endfunction()

function(colorize_output)
  # In some situations Ninja may not detect it can output using ANSI colors
  if (CMAKE_GENERATOR STREQUAL "Ninja")
    if("${CMAKE_CXX_COMPILER_ID}}" MATCHES "Clang")
      add_compile_options(-fcolor-diagnostics)
    elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
      add_compile_options(-fdiagnostics-color)
    endif()
  endif()
endfunction()
