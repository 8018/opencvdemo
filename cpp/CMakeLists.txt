cmake_minimum_required(VERSION 3.0)  
    project(opencvdemo)  
    find_package( OpenCV REQUIRED )

    #ADD_EXECUTABLE(LoadImage LoadImage.cpp)
    #target_link_libraries(LoadImage ${OpenCV_LIBS} )

    SET(CMAKE_BUILD_TYPE "Debug")
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

    file( GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}  *.cpp )
    foreach( sourcefile ${APP_SOURCES} )
        string( REPLACE ".cpp" "" executable ${sourcefile} )

        add_executable( ${executable} ${sourcefile} )
        # Make sure YourLib is linked to each app
        target_link_libraries( ${executable} ${OpenCV_LIBS}  )
    endforeach( sourcefile ${APP_SOURCES} )

