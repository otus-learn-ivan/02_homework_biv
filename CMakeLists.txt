cmake_minimum_required(VERSION 3.13)

set(PATCH_VERSION "2" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.1.${PATCH_VERSION})

project(ip_filter_prg VERSION ${PROJECT_VESRION})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(ip_filter main.cpp)
add_library(ip_filter_prg lib.cpp)
add_executable(test_ip_filter test_ip_filter.cpp)

set_target_properties(ip_filter ip_filter_prg test_ip_filter PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(ip_filter_prg
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_ip_filter PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)
target_link_libraries(ip_filter PRIVATE
    ip_filter_prg
)
target_link_libraries(test_ip_filter
    ${Boost_LIBRARIES}
    ip_filter_prg
)
configure_file(
  "ip_filter.tsv"
  "${CMAKE_CURRENT_BINARY_DIR}/" COPYONLY
)

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(ip_filter_prg PRIVATE
        /W4
    )
    target_compile_options(test_ip_filter PRIVATE
        /W4
    )
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip_filter_prg PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_ip_filter test_ip_filter)
