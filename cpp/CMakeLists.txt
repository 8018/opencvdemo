cmake_minimum_required(VERSION 3.0)  
    project(opencvdemo)  
    find_package( OpenCV REQUIRED )  
    ADD_EXECUTABLE(LoadImage LoadImage.cpp)
    ADD_EXECUTABLE(LoadVideo LoadVideo.cpp)

    target_link_libraries(LoadImage ${OpenCV_LIBS} )
    target_link_libraries(LoadVideo ${OpenCV_LIBS} )

