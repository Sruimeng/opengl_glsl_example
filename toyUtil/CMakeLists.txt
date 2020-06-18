aux_source_directory(. DIR_LIB_SRCS)

message(${DIR_LIB_SRCS})

add_executable(toyUtil ${DIR_LIB_SRCS})