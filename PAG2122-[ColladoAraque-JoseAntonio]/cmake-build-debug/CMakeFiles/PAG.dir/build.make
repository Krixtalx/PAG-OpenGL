# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.21

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
# Include any dependencies generated by the compiler for this target.
include CMakeFiles\PAG.dir\compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles\PAG.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\PAG.dir\flags.make

CMakeFiles\PAG.dir\main.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\main.cpp.obj: ..\main.cpp
CMakeFiles\PAG.dir\main.cpp.obj: CMakeFiles\PAG.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PAG.dir/main.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\PAG.dir\main.cpp.obj.d --working-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug --filter-prefix="Nota: inclusi�n del archivo: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\PAG.dir\main.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\main.cpp
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
CMakeFiles\PAG.dir\Renderer.cpp.obj: CMakeFiles\PAG.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/PAG.dir/Renderer.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\PAG.dir\Renderer.cpp.obj.d --working-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug --filter-prefix="Nota: inclusi�n del archivo: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\PAG.dir\Renderer.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Renderer.cpp
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

CMakeFiles\PAG.dir\ShaderProgram.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\ShaderProgram.cpp.obj: ..\ShaderProgram.cpp
CMakeFiles\PAG.dir\ShaderProgram.cpp.obj: CMakeFiles\PAG.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/PAG.dir/ShaderProgram.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\PAG.dir\ShaderProgram.cpp.obj.d --working-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug --filter-prefix="Nota: inclusi�n del archivo: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\PAG.dir\ShaderProgram.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\ShaderProgram.cpp
<<

CMakeFiles\PAG.dir\ShaderProgram.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAG.dir/ShaderProgram.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\PAG.dir\ShaderProgram.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\ShaderProgram.cpp
<<

CMakeFiles\PAG.dir\ShaderProgram.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAG.dir/ShaderProgram.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PAG.dir\ShaderProgram.cpp.s /c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\ShaderProgram.cpp
<<

CMakeFiles\PAG.dir\Shader.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\Shader.cpp.obj: ..\Shader.cpp
CMakeFiles\PAG.dir\Shader.cpp.obj: CMakeFiles\PAG.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/PAG.dir/Shader.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\PAG.dir\Shader.cpp.obj.d --working-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug --filter-prefix="Nota: inclusi�n del archivo: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\PAG.dir\Shader.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Shader.cpp
<<

CMakeFiles\PAG.dir\Shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAG.dir/Shader.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\PAG.dir\Shader.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Shader.cpp
<<

CMakeFiles\PAG.dir\Shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAG.dir/Shader.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PAG.dir\Shader.cpp.s /c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Shader.cpp
<<

CMakeFiles\PAG.dir\ShaderManager.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\ShaderManager.cpp.obj: ..\ShaderManager.cpp
CMakeFiles\PAG.dir\ShaderManager.cpp.obj: CMakeFiles\PAG.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/PAG.dir/ShaderManager.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\PAG.dir\ShaderManager.cpp.obj.d --working-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug --filter-prefix="Nota: inclusi�n del archivo: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\PAG.dir\ShaderManager.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\ShaderManager.cpp
<<

CMakeFiles\PAG.dir\ShaderManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAG.dir/ShaderManager.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\PAG.dir\ShaderManager.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\ShaderManager.cpp
<<

CMakeFiles\PAG.dir\ShaderManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAG.dir/ShaderManager.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PAG.dir\ShaderManager.cpp.s /c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\ShaderManager.cpp
<<

CMakeFiles\PAG.dir\Modelo.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\Modelo.cpp.obj: ..\Modelo.cpp
CMakeFiles\PAG.dir\Modelo.cpp.obj: CMakeFiles\PAG.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/PAG.dir/Modelo.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\PAG.dir\Modelo.cpp.obj.d --working-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug --filter-prefix="Nota: inclusi�n del archivo: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\PAG.dir\Modelo.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Modelo.cpp
<<

CMakeFiles\PAG.dir\Modelo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAG.dir/Modelo.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\PAG.dir\Modelo.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Modelo.cpp
<<

CMakeFiles\PAG.dir\Modelo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAG.dir/Modelo.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PAG.dir\Modelo.cpp.s /c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Modelo.cpp
<<

CMakeFiles\PAG.dir\Camara.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\Camara.cpp.obj: ..\Camara.cpp
CMakeFiles\PAG.dir\Camara.cpp.obj: CMakeFiles\PAG.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/PAG.dir/Camara.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\PAG.dir\Camara.cpp.obj.d --working-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug --filter-prefix="Nota: inclusi�n del archivo: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\PAG.dir\Camara.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Camara.cpp
<<

CMakeFiles\PAG.dir\Camara.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAG.dir/Camara.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\PAG.dir\Camara.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Camara.cpp
<<

CMakeFiles\PAG.dir\Camara.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAG.dir/Camara.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PAG.dir\Camara.cpp.s /c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Camara.cpp
<<

CMakeFiles\PAG.dir\Material.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\Material.cpp.obj: ..\Material.cpp
CMakeFiles\PAG.dir\Material.cpp.obj: CMakeFiles\PAG.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/PAG.dir/Material.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\PAG.dir\Material.cpp.obj.d --working-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug --filter-prefix="Nota: inclusi�n del archivo: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\PAG.dir\Material.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Material.cpp
<<

CMakeFiles\PAG.dir\Material.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAG.dir/Material.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\PAG.dir\Material.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Material.cpp
<<

CMakeFiles\PAG.dir\Material.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAG.dir/Material.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PAG.dir\Material.cpp.s /c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Material.cpp
<<

CMakeFiles\PAG.dir\MaterialManager.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\MaterialManager.cpp.obj: ..\MaterialManager.cpp
CMakeFiles\PAG.dir\MaterialManager.cpp.obj: CMakeFiles\PAG.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/PAG.dir/MaterialManager.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\PAG.dir\MaterialManager.cpp.obj.d --working-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug --filter-prefix="Nota: inclusi�n del archivo: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\PAG.dir\MaterialManager.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\MaterialManager.cpp
<<

CMakeFiles\PAG.dir\MaterialManager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAG.dir/MaterialManager.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\PAG.dir\MaterialManager.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\MaterialManager.cpp
<<

CMakeFiles\PAG.dir\MaterialManager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAG.dir/MaterialManager.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PAG.dir\MaterialManager.cpp.s /c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\MaterialManager.cpp
<<

CMakeFiles\PAG.dir\Luz.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\Luz.cpp.obj: ..\Luz.cpp
CMakeFiles\PAG.dir\Luz.cpp.obj: CMakeFiles\PAG.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/PAG.dir/Luz.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\PAG.dir\Luz.cpp.obj.d --working-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug --filter-prefix="Nota: inclusi�n del archivo: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\PAG.dir\Luz.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Luz.cpp
<<

CMakeFiles\PAG.dir\Luz.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAG.dir/Luz.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\PAG.dir\Luz.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Luz.cpp
<<

CMakeFiles\PAG.dir\Luz.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAG.dir/Luz.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PAG.dir\Luz.cpp.s /c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\Luz.cpp
<<

CMakeFiles\PAG.dir\lodepng.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\lodepng.cpp.obj: ..\lodepng.cpp
CMakeFiles\PAG.dir\lodepng.cpp.obj: CMakeFiles\PAG.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/PAG.dir/lodepng.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\PAG.dir\lodepng.cpp.obj.d --working-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug --filter-prefix="Nota: inclusi�n del archivo: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\PAG.dir\lodepng.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\lodepng.cpp
<<

CMakeFiles\PAG.dir\lodepng.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAG.dir/lodepng.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\PAG.dir\lodepng.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\lodepng.cpp
<<

CMakeFiles\PAG.dir\lodepng.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAG.dir/lodepng.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PAG.dir\lodepng.cpp.s /c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\lodepng.cpp
<<

CMakeFiles\PAG.dir\ModeloRevolucion.cpp.obj: CMakeFiles\PAG.dir\flags.make
CMakeFiles\PAG.dir\ModeloRevolucion.cpp.obj: ..\ModeloRevolucion.cpp
CMakeFiles\PAG.dir\ModeloRevolucion.cpp.obj: CMakeFiles\PAG.dir\compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/PAG.dir/ModeloRevolucion.cpp.obj"
	$(CMAKE_COMMAND) -E cmake_cl_compile_depends --dep-file=CMakeFiles\PAG.dir\ModeloRevolucion.cpp.obj.d --working-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug --filter-prefix="Nota: inclusi�n del archivo: " -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /showIncludes /FoCMakeFiles\PAG.dir\ModeloRevolucion.cpp.obj /FdCMakeFiles\PAG.dir\ /FS -c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\ModeloRevolucion.cpp
<<

CMakeFiles\PAG.dir\ModeloRevolucion.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PAG.dir/ModeloRevolucion.cpp.i"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\PAG.dir\ModeloRevolucion.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\ModeloRevolucion.cpp
<<

CMakeFiles\PAG.dir\ModeloRevolucion.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PAG.dir/ModeloRevolucion.cpp.s"
	C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\PAG.dir\ModeloRevolucion.cpp.s /c C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\ModeloRevolucion.cpp
<<

# Object files for target PAG
PAG_OBJECTS = \
"CMakeFiles\PAG.dir\main.cpp.obj" \
"CMakeFiles\PAG.dir\Renderer.cpp.obj" \
"CMakeFiles\PAG.dir\ShaderProgram.cpp.obj" \
"CMakeFiles\PAG.dir\Shader.cpp.obj" \
"CMakeFiles\PAG.dir\ShaderManager.cpp.obj" \
"CMakeFiles\PAG.dir\Modelo.cpp.obj" \
"CMakeFiles\PAG.dir\Camara.cpp.obj" \
"CMakeFiles\PAG.dir\Material.cpp.obj" \
"CMakeFiles\PAG.dir\MaterialManager.cpp.obj" \
"CMakeFiles\PAG.dir\Luz.cpp.obj" \
"CMakeFiles\PAG.dir\lodepng.cpp.obj" \
"CMakeFiles\PAG.dir\ModeloRevolucion.cpp.obj"

# External object files for target PAG
PAG_EXTERNAL_OBJECTS =

PAG.exe: CMakeFiles\PAG.dir\main.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\Renderer.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\ShaderProgram.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\Shader.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\ShaderManager.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\Modelo.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\Camara.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\Material.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\MaterialManager.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\Luz.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\lodepng.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\ModeloRevolucion.cpp.obj
PAG.exe: CMakeFiles\PAG.dir\build.make
PAG.exe: C:\vcpkg\installed\x86-windows\debug\lib\glew32d.lib
PAG.exe: C:\vcpkg\installed\x86-windows\debug\lib\glfw3dll.lib
PAG.exe: C:\vcpkg\installed\x86-windows\debug\lib\assimp-vc142-mtd.lib
PAG.exe: C:\vcpkg\installed\x86-windows\share\polyclipping\..\..\debug\lib\polyclipping.lib
PAG.exe: C:\vcpkg\installed\x86-windows\debug\lib\Irrlicht.lib
PAG.exe: C:\vcpkg\installed\x86-windows\debug\lib\minizip.lib
PAG.exe: C:\vcpkg\installed\x86-windows\debug\lib\zlibd.lib
PAG.exe: C:\vcpkg\installed\x86-windows\debug\lib\kubazip.lib
PAG.exe: C:\vcpkg\installed\x86-windows\debug\lib\poly2tri.lib
PAG.exe: CMakeFiles\PAG.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable PAG.exe"
	"C:\Program Files\JetBrains\CLion 2021.2.1\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\PAG.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~1\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\PAG.dir\objects1.rsp @<<
 /out:PAG.exe /implib:PAG.lib /pdb:C:\Github\PAG\PAG2122-[ColladoAraque-JoseAntonio]\cmake-build-debug\PAG.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  C:\vcpkg\installed\x86-windows\debug\lib\glew32d.lib C:\vcpkg\installed\x86-windows\debug\lib\glfw3dll.lib C:\vcpkg\installed\x86-windows\debug\lib\assimp-vc142-mtd.lib opengl32.lib glu32.lib C:\vcpkg\installed\x86-windows\share\polyclipping\..\..\debug\lib\polyclipping.lib C:\vcpkg\installed\x86-windows\debug\lib\Irrlicht.lib C:\vcpkg\installed\x86-windows\debug\lib\minizip.lib C:\vcpkg\installed\x86-windows\debug\lib\zlibd.lib C:\vcpkg\installed\x86-windows\debug\lib\kubazip.lib C:\vcpkg\installed\x86-windows\debug\lib\poly2tri.lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
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

