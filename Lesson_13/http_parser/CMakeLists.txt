SET( SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} )

SET( TARGET_HTTP http_parser )
SET( SOURCES_HTTP ${SOURCE_DIR}/http_parser.c )
ADD_LIBRARY( ${TARGET_HTTP} SHARED ${SOURCES_HTTP} )

SET( TARGET_PICO pico_parser )
SET( SOURCES_PICO ${SOURCE_DIR}/picohttpparser.c )
ADD_LIBRARY( ${TARGET_PICO} SHARED ${SOURCES_PICO} )

