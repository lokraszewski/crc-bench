find_package(Threads REQUIRED)
find_package(boost REQUIRED)
# find_package(crc REQUIRED)

file(GLOB_RECURSE ALL_BENCH_CPP *.cpp)

foreach(ONE_BENCH_CPP ${ALL_BENCH_CPP})

   get_filename_component(ONE_BENCH_EXEC ${ONE_BENCH_CPP} NAME_WE)

   # Avoid name collision
   set(TARGET_NAME ${PROJECT_NAME}_${ONE_BENCH_EXEC})
   add_executable(${TARGET_NAME} ${ONE_BENCH_CPP})
   set_target_properties(${TARGET_NAME}
    PROPERTIES OUTPUT_NAME ${ONE_BENCH_EXEC}
    CXX_STANDARD 17
       )

   target_link_libraries(${TARGET_NAME}
         benchmark
         crc
         boost::boost
     ${CMAKE_THREAD_LIBS_INIT}
    )
endforeach()

