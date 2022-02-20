@echo off
echo Running tests
set PROGRAM="%~1"

echo Test 1: incorrect amount arguments
%PROGRAM% %TEMP%\output.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-incorrect-amount-arguments.txt > nul
if ERRORLEVEL 1 goto err

echo Test 2: non existing file name
%PROGRAM% non-existing-file-name.txt multiline.txt %TEMP%\output.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-input-file-is-missing.txt > nul
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" empty.txt > nul
if ERRORLEVEL 1 goto err

echo Test 3: non writable output file
%PROGRAM% multiline.txt %PROGRAM% > %TEMP%\console_output.txt
if NOT ERRORLEVEL 1 goto err

echo Test 4: join one input file
%PROGRAM% multiline.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" multiline.txt > nul
if ERRORLEVEL 1 goto err

echo Test 5: join multiline and oneline input files
%PROGRAM% multiline.txt oneline.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-file-when-join-multiline-and-oneline.txt > nul
if ERRORLEVEL 1 goto err

echo Test 6: join oneline and oneline input files
%PROGRAM% oneline.txt oneline.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-file-when-join-oneline-and-oneline.txt > nul
if ERRORLEVEL 1 goto err

echo Test 7: join one empty input file
%PROGRAM% empty.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" empty.txt > nul
if ERRORLEVEL 1 goto err

echo Test 8: join two empty input files
%PROGRAM% empty.txt empty.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" empty.txt > nul
if ERRORLEVEL 1 goto err

echo Test 9: join multiline - empty - oneline input files
%PROGRAM% multiline.txt empty.txt oneline.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-file-when-join-multiline-and-oneline.txt > nul
if ERRORLEVEL 1 goto err

echo Test 10: join multiline - multiline2 input files
%PROGRAM% multiline.txt multiline2.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-file-when-join-multiline-multiline2.txt > nul
if ERRORLEVEL 1 goto err

echo Test 11: join oneline - multiline - multiline2 input files
%PROGRAM% oneline.txt multiline.txt multiline2.txt %TEMP%\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-file-when-join-oneline-multiline-and-multiline2.txt > nul
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
