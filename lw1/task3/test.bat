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

echo Test 3: incorrect format of matrix file
%PROGRAM% matrix2x2.txt matrix1.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-input-file-has-incorrect-format.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% matrix4x4.txt matrix1.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-input-file-has-incorrect-format.txt > nul
if ERRORLEVEL 1 goto err

echo Test 4: multiplying with zero-matrix
%PROGRAM% matrix1.txt zero-matrix.txt > "%TEMP%\console_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-multiplying-zero-matrix.txt > nul
if ERRORLEVEL 1 goto err

echo Test 5: multiplying matrix1 with matrix2
%PROGRAM% matrix1.txt matrix2.txt > "%TEMP%\console_output.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-multiplying-matrixes.txt > nul
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
