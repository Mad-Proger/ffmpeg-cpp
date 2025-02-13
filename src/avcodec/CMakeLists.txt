pkg_search_module(AVCODEC REQUIRED libavcodec)
pkg_search_module(AVUTIL REQUIRED libavutil)

add_library(avcodec-cpp STATIC
    Codec.cpp
    CodecIterator.cpp
)
target_include_directories(avcodec-cpp PUBLIC 
    "${AVCODEC_INCLUDE_DIRS}"
    "${AVUTIL_INCLUDE_DIRS}"
    "${HEADER_DIR}/avcodec"
)
target_link_directories(avcodec-cpp PUBLIC "${AVCODEC_LIBRARY_DIRS}")
target_link_libraries(avcodec-cpp PUBLIC ${AVCODEC_LIBRARIES} common)
target_compile_features(avcodec-cpp PUBLIC cxx_std_20)
