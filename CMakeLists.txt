cmake_minimum_required(VERSION 3.20)

project(
		VelocityMath
		VERSION 0.1
		LANGUAGES CXX
)

# ----------------------------
# C++ configuration
# ----------------------------

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# MSVC runtime
if(MSVC)
	set(CMAKE_MSVC_RUNTIME_LIBRARY
			"MultiThreaded$<$<CONFIG:Debug>:Debug>"
	)
endif()


# ----------------------------
# Build options
# ----------------------------

option(
		PRODUCTION_BUILD
		"Build production version"
		OFF
)

option(
		MATH_BUILD_TESTS
		"Build JSONParserTests"
		OFF
)

option(
		MATH_BUILD_BENCHMARKS
		"Build JSONParserBenchmarks"
		OFF
)

# ----------------------------
# Sources
# ----------------------------

add_library(
		VelocityMath INTERFACE
)

add_library(
		math ALIAS VelocityMath
)

target_include_directories(
		VelocityMath
		INTERFACE
		"${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# ----------------------------
# Tests
# ----------------------------

if(MATH_BUILD_TESTS)

	add_executable(
			MathManualTests
			tests/main/main.cpp
	)

	target_link_libraries(
			MathManualTests
			PRIVATE
			VelocityMath
	)

	include(FetchContent)
	FetchContent_Declare(
			googletest
			URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
	)

	FetchContent_MakeAvailable(googletest)

	add_executable(
			MathTests
			tests/unit/mainTests.cpp
	)

	target_link_libraries(
			MathTests
			PRIVATE
			VelocityMath
			GTest::gtest_main
	)

	include(CTest)
	enable_testing()

	include(GoogleTest)
	gtest_discover_tests(MathTests)

endif()

# ----------------------------
# Benchmarks
# ----------------------------

if(MATH_BUILD_BENCHMARKS)

	include(FetchContent)
	FetchContent_Declare(
			googlebenchmark
			URL https://github.com/google/benchmark/archive/refs/tags/v1.9.5.zip
	)

	FetchContent_MakeAvailable(googlebenchmark)

	add_executable(
			MathBenchmarks
			tests/benchmarks/mainBenchmarks.cpp
	)

	target_link_libraries(
			MathBenchmarks
			PRIVATE
			VelocityMath
			benchmark::benchmark
	)

endif()

# ----------------------------
# Defines
# ----------------------------

target_compile_definitions(
		VelocityMath
		INTERFACE
		_CRT_SECURE_NO_WARNINGS
)


if(PRODUCTION_BUILD)

	target_compile_definitions(
			VelocityMath
			INTERFACE
			PRODUCTION_BUILD=1
			DEVELOPMENT_BUILD=0
	)

else()

	target_compile_definitions(
			VelocityMath
			INTERFACE
			PRODUCTION_BUILD=0
			DEVELOPMENT_BUILD=1
	)

endif()



# ----------------------------
# Compiler warnings
# ----------------------------

if(MSVC)

	target_compile_options(
			VelocityMath
			INTERFACE
			/W4
	)

else()

	target_compile_options(
			VelocityMath
			INTERFACE
			-Wall
			-Wextra
			-Wpedantic
	)

endif()

# ----------------------------
# Optimizations
# ----------------------------

if(PRODUCTION_BUILD)

	include(CheckIPOSupported)

	check_ipo_supported(
			RESULT ipo_supported
	)

	if(ipo_supported)
		set_target_properties(
				VelocityMath
				PROPERTIES
				INTERPROCEDURAL_OPTIMIZATION TRUE
		)
	endif()

	if(MSVC)
		target_compile_options(VelocityMath INTERFACE /O2 /fp:fast)
	else()
		target_compile_options(VelocityMath INTERFACE -O3 -ffast-math -march=native)
	endif()

endif()