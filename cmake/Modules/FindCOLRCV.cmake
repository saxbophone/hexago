# CMake find script for colrcv https://github.com/saxbophone/colrcv
# Based on https://raw.githubusercontent.com/cinemast/libjson-rpc-cpp/master/cmake/FindArgtable.cmake
# - Try to find COLRCV
# Once done this will define
#
#  COLRCV_FOUND - system has COLRCV
#  COLRCV_INCLUDE_DIRS - the COLRCV include directory
#  COLRCV_LIBRARIES - Link these to use COLRCV

# TODO: Get it to find the actual correct version of colrcv

# NOTE: This should use the version of colrcv requested but right now I don't have the energy to work out how to do it
find_path(
    COLRCV_INCLUDE_DIR
    NAMES "colrcv-0/colrcv.h"
    DOC "colrcv include dir"
)

find_library(
    COLRCV_LIBRARY
    NAMES colrcv
    DOC "colrcv library"
)

set(COLRCV_INCLUDE_DIRS ${COLRCV_INCLUDE_DIR})
set(COLRCV_LIBRARIES ${COLRCV_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
    colrcv DEFAULT_MSG COLRCV_INCLUDE_DIR COLRCV_LIBRARY
)
mark_as_advanced(COLRCV_INCLUDE_DIR COLRCV_LIBRARY)
