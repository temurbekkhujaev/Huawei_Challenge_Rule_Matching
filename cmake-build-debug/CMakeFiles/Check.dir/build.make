# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\temur\repos\Huawei-Challenge-Rule-Matching

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\temur\repos\Huawei-Challenge-Rule-Matching\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Check.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/Check.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Check.dir/flags.make

CMakeFiles/Check.dir/check.cpp.obj: CMakeFiles/Check.dir/flags.make
CMakeFiles/Check.dir/check.cpp.obj: ../check.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\temur\repos\Huawei-Challenge-Rule-Matching\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Check.dir/check.cpp.obj"
	C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Check.dir\check.cpp.obj -c C:\Users\temur\repos\Huawei-Challenge-Rule-Matching\check.cpp

CMakeFiles/Check.dir/check.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Check.dir/check.cpp.i"
	C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\temur\repos\Huawei-Challenge-Rule-Matching\check.cpp > CMakeFiles\Check.dir\check.cpp.i

CMakeFiles/Check.dir/check.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Check.dir/check.cpp.s"
	C:\PROGRA~1\CODEBL~1\MinGW\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\temur\repos\Huawei-Challenge-Rule-Matching\check.cpp -o CMakeFiles\Check.dir\check.cpp.s

# Object files for target Check
Check_OBJECTS = \
"CMakeFiles/Check.dir/check.cpp.obj"

# External object files for target Check
Check_EXTERNAL_OBJECTS =

Check.exe: CMakeFiles/Check.dir/check.cpp.obj
Check.exe: CMakeFiles/Check.dir/build.make
Check.exe: CMakeFiles/Check.dir/linklibs.rsp
Check.exe: CMakeFiles/Check.dir/objects1.rsp
Check.exe: CMakeFiles/Check.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\temur\repos\Huawei-Challenge-Rule-Matching\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Check.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Check.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Check.dir/build: Check.exe
.PHONY : CMakeFiles/Check.dir/build

CMakeFiles/Check.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Check.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Check.dir/clean

CMakeFiles/Check.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\temur\repos\Huawei-Challenge-Rule-Matching C:\Users\temur\repos\Huawei-Challenge-Rule-Matching C:\Users\temur\repos\Huawei-Challenge-Rule-Matching\cmake-build-debug C:\Users\temur\repos\Huawei-Challenge-Rule-Matching\cmake-build-debug C:\Users\temur\repos\Huawei-Challenge-Rule-Matching\cmake-build-debug\CMakeFiles\Check.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Check.dir/depend
