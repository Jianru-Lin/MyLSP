@if not exist build (mkdir build)
@cd build
@if not exist x86 (mkdir x86)
@cd x86
@cmake ..\.. -G "Visual Studio 12"
@cd ..
@if not exist x64 (mkdir x64)
@cd x64
@cmake ..\.. -G "Visual Studio 12 Win64"
@cd ..
@pause