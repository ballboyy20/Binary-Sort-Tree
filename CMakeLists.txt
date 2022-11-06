cmake_minimum_required(VERSION 3.23)

project(binarysorttree LANGUAGES CXX VERSION 1.0.0)

configure_file(binarysorttreeConfig.h.in binarysorttreeConfig.h)
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

find_package(GTest REQUIRED)

add_library(binarysorttree SHARED)
target_compile_features(binarysorttree PUBLIC cxx_std_17)
target_sources(binarysorttree
    PRIVATE
        binarysorttree.cpp
        node.cpp
        BSTutils.cpp
        main.cpp
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS ${PROJECT_SOURCE_DIR}
            FILES binarysorttree.hpp
            node.hpp
            BSTutils.hpp
)
target_include_directories(binarysorttree
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(binarysorttree_unittests)
target_compile_features(binarysorttree_unittests PUBLIC cxx_std_17)
target_sources(binarysorttree_unittests PRIVATE binarysorttree_unittests.cpp)
target_include_directories(binarysorttree_unittests PRIVATE "${GTEST_INCLUDE_DIRS}")
target_link_libraries(binarysorttree_unittests
    PRIVATE
        ${GTEST_LIBRARIES}
        ${GTEST_MAIN_LIBRARIES}
        binarysorttree
)

install(TARGETS binarysorttree
    EXPORT binarysorttreeTargets
    FILE_SET HEADERS
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include)

install(EXPORT binarysorttreeTargets
    FILE binarysorttreeTargets.cmake
    NAMESPACE binarysorttree::
    DESTINATION lib/cmake/binarysorttree)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "binarysorttreeConfigVersion.cmake"
    VERSION ${binarysorttree_VERSION}
    COMPATIBILITY AnyNewerVersion)
install(
    FILES
        "binarysorttreeConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/binarysorttreeConfigVersion.cmake"
    DESTINATION lib/cmake/binarysorttree
)
