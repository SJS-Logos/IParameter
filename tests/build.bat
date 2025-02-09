@echo off
where cmake >nul 2>&1
if errorlevel 1 set path=%path%;"C:\Program Files\Microsoft Visual Studio\2022\Professional\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\"

if not exist build (
  md build
  cd build
  cmake.exe .. 
) else (
  cd build
  cmake.exe .. 
)
cmake.exe --build .

cd ..