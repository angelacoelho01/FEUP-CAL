cmake_minimum_required(VERSION 3.17)
project(CAL-TP_classes)

# Build the Google tests
set(GOOGLETEST_PATH lib/googletest-master)
add_subdirectory(${GOOGLETEST_PATH})

# Add the source files of each TP class
file(GLOB TP8_FILES CONFIGURE_DEPENDS
        "TP8/*.cpp"
        )

add_executable(TP8
        main.cpp
        ${TP8_FILES}
        )

target_link_libraries(TP8 gtest_main gmock_main)
