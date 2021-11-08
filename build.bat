@ECHO OFF
SET COMPILER_DIR=..\..\..\Compiler
SET PATH=%COMPILER_DIR%\WINDOWS\Other Utilities;%COMPILER_DIR%\WINDOWS\bin;%PATH%
rm -rf makefile
rm -rf release
mkdir release
copy makefile_windows makefile
make clean

for %%f in (firmware\*.bin) do (
    set /p val=<%%f
    SET AR_FIRM_FILE=%%~nf
    echo Building %%~nf
    mkdir out
    START /WAIT compile AR_FIRM_FILE=%AR_FIRM_FILE%
    MOVE "out\ar_patched*.bin" "release\ar_patched-satiator-rings_%%~nf.bin"
    make clean
)

rm makefile
copy makefile_linux makefile
exit