# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\PAG.dir\depend.make
# Include the progress variables for this target.
include CMakeFiles\PAG.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\PAG.dir\flags.make

CMakeFiles\PAG.dir\main.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PAG.dir/main.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\PAG.dir\main.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\main.cpp
<<

CMakeFiles\PAG.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAG.dir/main.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\PAG.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\main.cpp
<<

CMakeFiles\PAG.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAG.dir/main.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PAG.dir\main.cpp.s /c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\main.cpp
<<

CMakeFiles\PAG.dir\Renderer.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\Renderer.cpp.obj: ..\Renderer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PAG.dir/Renderer.cpp.obj"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\PAG.dir\Renderer.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Renderer.cpp
<<

CMakeFiles\PAG.dir\Renderer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAG.dir/Renderer.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\PAG.dir\Renderer.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Renderer.cpp
<<

CMakeFiles\PAG.dir\Renderer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAG.dir/Renderer.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PAG.dir\Renderer.cpp.s /c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Renderer.cpp
<<

# Object files for target PAG
PAG_OBJECTS = \
"CMakeFiles\PAG.dir\main.cpp.obj" \
"CMakeFiles\PAG.dir\Renderer.cpp.obj"

# External object files for target PAG
PAG_EXTERNAL_OBJECTS =

PAG.exe: CMakeFiles\PAG.dir\main.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\Renderer.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\build.make
PAG.exe: C:\vcpkg\installed\x86-windows\debug\lib\glew32d.lib
PAG.exe: C:\vcpkg\installed\x86-windows\debug\lib\glfw3dll.lib
PAG.exe: CMakeFiles\PAG.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable PAG.exe"
	"C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\PAG.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\PAG.dir\objects1.rsp @<<
 /out:PAG.exe /implib:PAG.lib /pdb:C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\PAG.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  C:\vcpkg\installed\x86-windows\debug\lib\glew32d.lib C:\vcpkg\installed\x86-windows\debug\lib\glfw3dll.lib opengl32.lib glu32.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -noprofile -executionpolicy Bypass -file C:/vcpkg/scripts/buildsystems/msbuild/applocal.ps1 -targetBinary C:/Github/PAG/PAG2122-[ColladoAraque-JoseAntonio]/cmake-build-debug/PAG.exe -installedDir C:/vcpkg/installed/x86-windows/debug/bin -OutVariable out

# Rule to build all files generated by this target.
CMakeFiles\PAG.dir\build: PAG.exe
.PHONY : CMakeFiles\PAG.dir\build

CMakeFiles\PAG.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\PAG.dir\cmake_clean.cmake
.PHONY : CMakeFiles\PAG.dir\clean

CMakeFiles\PAG.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio] C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio] C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles\PAG.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\PAG.dir\depend

