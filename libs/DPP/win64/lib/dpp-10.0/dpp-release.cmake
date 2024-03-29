#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "dpp::dpp" for configuration "Release"
set_property(TARGET dpp::dpp APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(dpp::dpp PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/dpp-10.0/dpp.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/dpp.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS dpp::dpp )
list(APPEND _IMPORT_CHECK_FILES_FOR_dpp::dpp "${_IMPORT_PREFIX}/lib/dpp-10.0/dpp.lib" "${_IMPORT_PREFIX}/bin/dpp.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
