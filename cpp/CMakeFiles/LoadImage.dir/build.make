# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.17.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.17.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/michaelliu/code/opencvdemo/cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/michaelliu/code/opencvdemo/cpp

# Include any dependencies generated for this target.
include CMakeFiles/LoadImage.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LoadImage.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LoadImage.dir/flags.make

CMakeFiles/LoadImage.dir/LoadImage.cpp.o: CMakeFiles/LoadImage.dir/flags.make
CMakeFiles/LoadImage.dir/LoadImage.cpp.o: LoadImage.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/michaelliu/code/opencvdemo/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LoadImage.dir/LoadImage.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/LoadImage.dir/LoadImage.cpp.o -c /Users/michaelliu/code/opencvdemo/cpp/LoadImage.cpp

CMakeFiles/LoadImage.dir/LoadImage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LoadImage.dir/LoadImage.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/michaelliu/code/opencvdemo/cpp/LoadImage.cpp > CMakeFiles/LoadImage.dir/LoadImage.cpp.i

CMakeFiles/LoadImage.dir/LoadImage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LoadImage.dir/LoadImage.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/michaelliu/code/opencvdemo/cpp/LoadImage.cpp -o CMakeFiles/LoadImage.dir/LoadImage.cpp.s

# Object files for target LoadImage
LoadImage_OBJECTS = \
"CMakeFiles/LoadImage.dir/LoadImage.cpp.o"

# External object files for target LoadImage
LoadImage_EXTERNAL_OBJECTS =

LoadImage: CMakeFiles/LoadImage.dir/LoadImage.cpp.o
LoadImage: CMakeFiles/LoadImage.dir/build.make
LoadImage: /usr/local/lib/libopencv_dnn.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_gapi.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_highgui.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_ml.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_objdetect.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_photo.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_stitching.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_video.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_videoio.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_imgcodecs.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_calib3d.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_features2d.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_flann.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_imgproc.4.3.0.dylib
LoadImage: /usr/local/lib/libopencv_core.4.3.0.dylib
LoadImage: CMakeFiles/LoadImage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/michaelliu/code/opencvdemo/cpp/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable LoadImage"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LoadImage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LoadImage.dir/build: LoadImage

.PHONY : CMakeFiles/LoadImage.dir/build

CMakeFiles/LoadImage.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/LoadImage.dir/cmake_clean.cmake
.PHONY : CMakeFiles/LoadImage.dir/clean

CMakeFiles/LoadImage.dir/depend:
	cd /Users/michaelliu/code/opencvdemo/cpp && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/michaelliu/code/opencvdemo/cpp /Users/michaelliu/code/opencvdemo/cpp /Users/michaelliu/code/opencvdemo/cpp /Users/michaelliu/code/opencvdemo/cpp /Users/michaelliu/code/opencvdemo/cpp/CMakeFiles/LoadImage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LoadImage.dir/depend

