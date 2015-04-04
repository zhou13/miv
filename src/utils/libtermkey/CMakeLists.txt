set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu11")

add_library(
    termkey
    driver-csi.c
    driver-ti.c
    termkey.c
)
