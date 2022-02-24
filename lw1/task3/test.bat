@echo off
echo Running tests
set PROGRAM="%~1"

echo Test 1: incorrect amount arguments
%PROGRAM% matrix1.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-incorrect-amount-arguments.txt > nul
if ERRORLEVEL 1 goto err

echo Test 2: non existing file name
%PROGRAM% non-existing-file-name.txt matrix1.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-input-file-is-missing.txt > nul
if ERRORLEVEL 1 goto err


@REM echo Test 2: incorrect value arguments
@REM %PROGRAM% 5 2 M > "%TEMP%\console_output.txt"
@REM if NOT ERRORLEVEL 1 goto err
@REM fc.exe "%TEMP%\console_output.txt" expected-output-when-incorrect-value-arguments.txt > nul
@REM if ERRORLEVEL 1 goto err
@REM
@REM %PROGRAM% 5 name L > "%TEMP%\console_output.txt"
@REM if NOT ERRORLEVEL 1 goto err
@REM fc.exe "%TEMP%\console_output.txt" expected-output-when-incorrect-value-arguments.txt > nul
@REM if ERRORLEVEL 1 goto err
@REM
@REM %PROGRAM% 256 2 L > "%TEMP%\console_output.txt"
@REM if NOT ERRORLEVEL 1 goto err
@REM fc.exe "%TEMP%\console_output.txt" expected-output-when-incorrect-value-arguments.txt > nul
@REM if ERRORLEVEL 1 goto err
@REM
@REM %PROGRAM% filename.txt 2 L > "%TEMP%\console_output.txt"
@REM if NOT ERRORLEVEL 1 goto err
@REM fc.exe "%TEMP%\console_output.txt" expected-output-when-incorrect-value-arguments.txt > nul
@REM if ERRORLEVEL 1 goto err
@REM
@REM echo Test 3: simple left shift
@REM %PROGRAM% 2 1 L > %TEMP%\console_output.txt
@REM if ERRORLEVEL 1 goto err
@REM fc.exe "%TEMP%\console_output.txt" expected-output-when-run-left-1-bit-shift-with-2.txt > nul
@REM if ERRORLEVEL 1 goto err
@REM
@REM echo Test 4: simple right shift
@REM %PROGRAM% 8 1 R > %TEMP%\console_output.txt
@REM if ERRORLEVEL 1 goto err
@REM fc.exe "%TEMP%\console_output.txt" expected-output-when-run-right-1-bit-shift-with-8.txt > nul
@REM if ERRORLEVEL 1 goto err
@REM
@REM echo Test 5: circle left shift
@REM %PROGRAM% 2 8 L > %TEMP%\console_output.txt
@REM if ERRORLEVEL 1 goto err
@REM fc.exe "%TEMP%\console_output.txt" expected-output-when-run-left-8-bit-with-2.txt > nul
@REM if ERRORLEVEL 1 goto err
@REM
@REM echo Test 6: circle right shift
@REM %PROGRAM% 2 8 R > %TEMP%\console_output.txt
@REM if ERRORLEVEL 1 goto err
@REM fc.exe "%TEMP%\console_output.txt" expected-output-when-run-right-8-bit-with-2.txt > nul
@REM if ERRORLEVEL 1 goto err
@REM
@REM echo Test 7: boundary left shift
@REM %PROGRAM% 128 1 L > %TEMP%\console_output.txt
@REM if ERRORLEVEL 1 goto err
@REM fc.exe "%TEMP%\console_output.txt" expected-output-when-run-left-1-bit-shift-with-128.txt > nul
@REM if ERRORLEVEL 1 goto err
@REM
@REM echo Test 8: boundary right shift
@REM %PROGRAM% 1 1 R > %TEMP%\console_output.txt
@REM if ERRORLEVEL 1 goto err
@REM fc.exe "%TEMP%\console_output.txt" expected-output-when-run-right-1-bit-shift-with-1.txt > nul
@REM if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
