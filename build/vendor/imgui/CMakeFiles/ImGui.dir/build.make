# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jano/dev/nvim/GameOfLifeCPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jano/dev/nvim/GameOfLifeCPP/build

# Include any dependencies generated for this target.
include vendor/imgui/CMakeFiles/ImGui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include vendor/imgui/CMakeFiles/ImGui.dir/compiler_depend.make

# Include the progress variables for this target.
include vendor/imgui/CMakeFiles/ImGui.dir/progress.make

# Include the compile flags for this target's objects.
include vendor/imgui/CMakeFiles/ImGui.dir/flags.make

vendor/imgui/CMakeFiles/ImGui.dir/imgui.cpp.o: vendor/imgui/CMakeFiles/ImGui.dir/flags.make
vendor/imgui/CMakeFiles/ImGui.dir/imgui.cpp.o: /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui.cpp
vendor/imgui/CMakeFiles/ImGui.dir/imgui.cpp.o: vendor/imgui/CMakeFiles/ImGui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/jano/dev/nvim/GameOfLifeCPP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object vendor/imgui/CMakeFiles/ImGui.dir/imgui.cpp.o"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/imgui/CMakeFiles/ImGui.dir/imgui.cpp.o -MF CMakeFiles/ImGui.dir/imgui.cpp.o.d -o CMakeFiles/ImGui.dir/imgui.cpp.o -c /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui.cpp

vendor/imgui/CMakeFiles/ImGui.dir/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ImGui.dir/imgui.cpp.i"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui.cpp > CMakeFiles/ImGui.dir/imgui.cpp.i

vendor/imgui/CMakeFiles/ImGui.dir/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ImGui.dir/imgui.cpp.s"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui.cpp -o CMakeFiles/ImGui.dir/imgui.cpp.s

vendor/imgui/CMakeFiles/ImGui.dir/imgui_demo.cpp.o: vendor/imgui/CMakeFiles/ImGui.dir/flags.make
vendor/imgui/CMakeFiles/ImGui.dir/imgui_demo.cpp.o: /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui_demo.cpp
vendor/imgui/CMakeFiles/ImGui.dir/imgui_demo.cpp.o: vendor/imgui/CMakeFiles/ImGui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/jano/dev/nvim/GameOfLifeCPP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object vendor/imgui/CMakeFiles/ImGui.dir/imgui_demo.cpp.o"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/imgui/CMakeFiles/ImGui.dir/imgui_demo.cpp.o -MF CMakeFiles/ImGui.dir/imgui_demo.cpp.o.d -o CMakeFiles/ImGui.dir/imgui_demo.cpp.o -c /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui_demo.cpp

vendor/imgui/CMakeFiles/ImGui.dir/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ImGui.dir/imgui_demo.cpp.i"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui_demo.cpp > CMakeFiles/ImGui.dir/imgui_demo.cpp.i

vendor/imgui/CMakeFiles/ImGui.dir/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ImGui.dir/imgui_demo.cpp.s"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui_demo.cpp -o CMakeFiles/ImGui.dir/imgui_demo.cpp.s

vendor/imgui/CMakeFiles/ImGui.dir/imgui_draw.cpp.o: vendor/imgui/CMakeFiles/ImGui.dir/flags.make
vendor/imgui/CMakeFiles/ImGui.dir/imgui_draw.cpp.o: /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui_draw.cpp
vendor/imgui/CMakeFiles/ImGui.dir/imgui_draw.cpp.o: vendor/imgui/CMakeFiles/ImGui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/jano/dev/nvim/GameOfLifeCPP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object vendor/imgui/CMakeFiles/ImGui.dir/imgui_draw.cpp.o"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/imgui/CMakeFiles/ImGui.dir/imgui_draw.cpp.o -MF CMakeFiles/ImGui.dir/imgui_draw.cpp.o.d -o CMakeFiles/ImGui.dir/imgui_draw.cpp.o -c /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui_draw.cpp

vendor/imgui/CMakeFiles/ImGui.dir/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ImGui.dir/imgui_draw.cpp.i"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui_draw.cpp > CMakeFiles/ImGui.dir/imgui_draw.cpp.i

vendor/imgui/CMakeFiles/ImGui.dir/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ImGui.dir/imgui_draw.cpp.s"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui_draw.cpp -o CMakeFiles/ImGui.dir/imgui_draw.cpp.s

vendor/imgui/CMakeFiles/ImGui.dir/imgui_widgets.cpp.o: vendor/imgui/CMakeFiles/ImGui.dir/flags.make
vendor/imgui/CMakeFiles/ImGui.dir/imgui_widgets.cpp.o: /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui_widgets.cpp
vendor/imgui/CMakeFiles/ImGui.dir/imgui_widgets.cpp.o: vendor/imgui/CMakeFiles/ImGui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/jano/dev/nvim/GameOfLifeCPP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object vendor/imgui/CMakeFiles/ImGui.dir/imgui_widgets.cpp.o"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT vendor/imgui/CMakeFiles/ImGui.dir/imgui_widgets.cpp.o -MF CMakeFiles/ImGui.dir/imgui_widgets.cpp.o.d -o CMakeFiles/ImGui.dir/imgui_widgets.cpp.o -c /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui_widgets.cpp

vendor/imgui/CMakeFiles/ImGui.dir/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ImGui.dir/imgui_widgets.cpp.i"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui_widgets.cpp > CMakeFiles/ImGui.dir/imgui_widgets.cpp.i

vendor/imgui/CMakeFiles/ImGui.dir/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ImGui.dir/imgui_widgets.cpp.s"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui/imgui_widgets.cpp -o CMakeFiles/ImGui.dir/imgui_widgets.cpp.s

# Object files for target ImGui
ImGui_OBJECTS = \
"CMakeFiles/ImGui.dir/imgui.cpp.o" \
"CMakeFiles/ImGui.dir/imgui_demo.cpp.o" \
"CMakeFiles/ImGui.dir/imgui_draw.cpp.o" \
"CMakeFiles/ImGui.dir/imgui_widgets.cpp.o"

# External object files for target ImGui
ImGui_EXTERNAL_OBJECTS =

bin/libImGui.a: vendor/imgui/CMakeFiles/ImGui.dir/imgui.cpp.o
bin/libImGui.a: vendor/imgui/CMakeFiles/ImGui.dir/imgui_demo.cpp.o
bin/libImGui.a: vendor/imgui/CMakeFiles/ImGui.dir/imgui_draw.cpp.o
bin/libImGui.a: vendor/imgui/CMakeFiles/ImGui.dir/imgui_widgets.cpp.o
bin/libImGui.a: vendor/imgui/CMakeFiles/ImGui.dir/build.make
bin/libImGui.a: vendor/imgui/CMakeFiles/ImGui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/jano/dev/nvim/GameOfLifeCPP/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library ../../bin/libImGui.a"
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && $(CMAKE_COMMAND) -P CMakeFiles/ImGui.dir/cmake_clean_target.cmake
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ImGui.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
vendor/imgui/CMakeFiles/ImGui.dir/build: bin/libImGui.a
.PHONY : vendor/imgui/CMakeFiles/ImGui.dir/build

vendor/imgui/CMakeFiles/ImGui.dir/clean:
	cd /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui && $(CMAKE_COMMAND) -P CMakeFiles/ImGui.dir/cmake_clean.cmake
.PHONY : vendor/imgui/CMakeFiles/ImGui.dir/clean

vendor/imgui/CMakeFiles/ImGui.dir/depend:
	cd /home/jano/dev/nvim/GameOfLifeCPP/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jano/dev/nvim/GameOfLifeCPP /home/jano/dev/nvim/GameOfLifeCPP/vendor/imgui /home/jano/dev/nvim/GameOfLifeCPP/build /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui /home/jano/dev/nvim/GameOfLifeCPP/build/vendor/imgui/CMakeFiles/ImGui.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : vendor/imgui/CMakeFiles/ImGui.dir/depend

