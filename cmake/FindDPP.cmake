find_path(DPP_INCLUDE_DIR NAMES dpp/dpp.h HINTS ${DPP_ROOT_DIR})

find_library(DPP_LIBRARIES NAMES dpp "dpp.lib" "libdpp.a" HINTS ${DPP_ROOT_DIR})

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(DPP DEFAULT_MSG DPP_LIBRARIES DPP_INCLUDE_DIR)

if(DPP_FOUND)
    if(TARGET_OS STREQUAL "windows")
        set(DPP_COPY_FILES "${PROJECT_SOURCE_DIR}/libs/DPP/bin/*.dll")
    endif()
endif()
