# =======================================
# Source / Header Files
# =======================================
file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.h)

add_library(r_utils ${SOURCES} ${HEADERS})

# =======================================
# Include Pfade
# =======================================
target_include_directories(r_utils PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>  # <- für find_package
)

# =======================================
# VS Filters
# =======================================
foreach(FILE ${SOURCES})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/src" "" GROUP_PATH "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP_PATH "${GROUP_PATH}")
    source_group("Source Files${GROUP_PATH}" FILES "${FILE}")
endforeach()

foreach(FILE ${HEADERS})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/include" "" GROUP_PATH "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP_PATH "${GROUP_PATH}")
    source_group("Header Files${GROUP_PATH}" FILES "${FILE}")
endforeach()

# =======================================
# Export / Installation
# =======================================
include(GNUInstallDirs)

install(TARGETS r_utils
    EXPORT r_utilsTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# CMake Config exportieren
install(EXPORT r_utilsTargets
    FILE r_utilsTargets.cmake
    NAMESPACE r_utils::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/r_utils
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/r_utilsConfigVersion.cmake"
    VERSION 1.0.0
    COMPATIBILITY AnyNewerVersion
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/r_utilsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/r_utilsConfig.cmake"
    @ONLY
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/r_utilsConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/r_utilsConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/r_utils
)