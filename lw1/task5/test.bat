@echo off
echo Running tests
set PROGRAM="%~1"

echo Test 1: incorrect amount arguments
%PROGRAM% %TEMP%\output.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-incorrect-amount-arguments.txt > nul
if ERRORLEVEL 1 goto err

echo Test 2: non existing input filename
%PROGRAM% non-existing-file-name.txt %TEMP%\output.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-input-file-is-missing.txt > nul
if ERRORLEVEL 1 goto err

echo Test 3: output file is busy
%PROGRAM% input.txt %PROGRAM% > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-output-file-is-busy.txt > nul
if ERRORLEVEL 1 goto err

echo Test 4: fill without borders
%PROGRAM% input-without-borders.txt "%TEMP%"\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-filling-without-borders.txt > nul
if ERRORLEVEL 1 goto err

echo Test 5: fill outside borders
%PROGRAM% input-filling-outside-borders.txt "%TEMP%"\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-filling-outside-borders.txt > nul
if ERRORLEVEL 1 goto err

echo Test 6: fill inside broken borders
%PROGRAM% input-filling-inside-broken-borders.txt "%TEMP%"\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-filling-inside-broken-borders.txt > nul
if ERRORLEVEL 1 goto err

echo Test 7: fill inside borders
%PROGRAM% input-filling-inside-borders.txt "%TEMP%"\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-filling-inside-borders.txt > nul
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
