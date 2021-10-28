SET COMPILER_DIR=..\..\Compiler
SET PATH=%COMPILER_DIR%\WINDOWS\Other Utilities;%COMPILER_DIR%\WINDOWS\bin;%PATH%
SET sh-none-elf-gcc=%COMPILER_DIR%\WINDOWS\sh-elf-gcc.exe
make
pause