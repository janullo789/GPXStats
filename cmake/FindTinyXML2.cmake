set(FIND_TINYXML2_PATHS
        C:/tinyxml2)

find_path(TINYXML2_INCLUDE_DIR tinyxml2.h   # The variable to store the path in and the name of the header files
        PATH_SUFFIXES include               # The folder name containing the header files
        PATHS ${FIND_TINYXML2_PATHS})

find_library(TINYXML2_LIBRARY               # The variable to store where it found the .a files
        NAMES tinyxml2                      # The name of the .a file (without the extension and without the 'lib')
        PATH_SUFFIXES lib                   # The folder the .a file is in
        PATHS ${FIND_TINYXML2_PATHS})

