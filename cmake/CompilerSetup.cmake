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


function(enable_warnings_for target)
  # Maybe these should be generator expressions instead, but this seems to
  # work just fine
  if("${CMAKE_CXX_COMPILER_ID}}" MATCHES "Clang")
    # Matches is used to allow for Clang or AppleClang

    # Use theory of turn on all warnings, but disable ones that we don't care about
    target_compile_options(${target} PRIVATE -Weverything)
    target_compile_options(${target} PRIVATE -Wno-c++98-compat)
    target_compile_options(${target} PRIVATE -Wno-c++98-compat-pedantic)
    target_compile_options(${target} PRIVATE -Wno-padded)
    target_compile_options(${target} PRIVATE -Wno-documentation-unknown-command)
  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # Large warning groups
    target_compile_options(${target} PRIVATE -Wall)
    target_compile_options(${target} PRIVATE -Werror)
    target_compile_options(${target} PRIVATE -Wextra)
    target_compile_options(${target} PRIVATE -Wpedantic)
    # Individual warnings
    target_compile_options(${target} PRIVATE -Walloc-zero)
    target_compile_options(${target} PRIVATE -Wcast-align)
    target_compile_options(${target} PRIVATE -Wcast-qual)
    target_compile_options(${target} PRIVATE -Wconditionally-supported)
    target_compile_options(${target} PRIVATE -Wconversion)
    target_compile_options(${target} PRIVATE -Wctor-dtor-privacy)
    target_compile_options(${target} PRIVATE -Wdate-time)
    target_compile_options(${target} PRIVATE -Wdeprecated-copy-dtor)
    target_compile_options(${target} PRIVATE -Wdouble-promotion)
    target_compile_options(${target} PRIVATE -Wduplicated-branches)
    target_compile_options(${target} PRIVATE -Wduplicated-cond)
    target_compile_options(${target} PRIVATE -Wextra-semi)
    target_compile_options(${target} PRIVATE -Wfloat-equal)
    target_compile_options(${target} PRIVATE -Wformat=2)
    target_compile_options(${target} PRIVATE -Wlogical-op)
    target_compile_options(${target} PRIVATE -Wmissing-declarations)
    target_compile_options(${target} PRIVATE -Wmissing-profile)
    target_compile_options(${target} PRIVATE -Wno-long-long)
    target_compile_options(${target} PRIVATE -Wno-pmf-conversions)
    target_compile_options(${target} PRIVATE -Wnoexcept)
    target_compile_options(${target} PRIVATE -Wnon-virtual-dtor)
    target_compile_options(${target} PRIVATE -Wnormalized)
    target_compile_options(${target} PRIVATE -Wnull-dereference)
    target_compile_options(${target} PRIVATE -Wold-style-cast)
    target_compile_options(${target} PRIVATE -Woverloaded-virtual)
    target_compile_options(${target} PRIVATE -Wpacked)
    target_compile_options(${target} PRIVATE -Wparentheses)
    target_compile_options(${target} PRIVATE -Wredundant-decls)
    target_compile_options(${target} PRIVATE -Wshadow)
    target_compile_options(${target} PRIVATE -Wsign-conversion)
    target_compile_options(${target} PRIVATE -Wsign-promo)
    target_compile_options(${target} PRIVATE -Wstrict-null-sentinel)
    target_compile_options(${target} PRIVATE -Wsuggest-attribute=const)
    target_compile_options(${target} PRIVATE -Wsuggest-attribute=malloc)
    target_compile_options(${target} PRIVATE -Wsuggest-attribute=noreturn)
    target_compile_options(${target} PRIVATE -Wsuggest-attribute=pure)
    target_compile_options(${target} PRIVATE -Wsuggest-final-methods)
    target_compile_options(${target} PRIVATE -Wsuggest-final-types)
    target_compile_options(${target} PRIVATE -Wsuggest-override)
    target_compile_options(${target} PRIVATE -Wswitch-enum)
    target_compile_options(${target} PRIVATE -Wuninitialized)
    target_compile_options(${target} PRIVATE -Wundef)
    target_compile_options(${target} PRIVATE -Wunsafe-loop-optimizations)
    target_compile_options(${target} PRIVATE -Wunused)
    target_compile_options(${target} PRIVATE -Wunused-macros)
    target_compile_options(${target} PRIVATE -Wuseless-cast)
    target_compile_options(${target} PRIVATE -Wvla)
    target_compile_options(${target} PRIVATE -Wwrite-strings)
    target_compile_options(${target} PRIVATE -Wzero-as-null-pointer-constant)

  elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(${target} PRIVATE /W3)
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
