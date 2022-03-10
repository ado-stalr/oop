@echo off
echo Running tests
set PROGRAM="%~1"

echo Test 1: incorrect amount arguments
%PROGRAM% %TEMP%\output.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-incorrect-amount-arguments.txt > nul
if ERRORLEVEL 1 goto err

echo Test 2: non existing input filename
%PROGRAM% pack non-existing-file-name.txt %TEMP%\output.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-input-file-is-missing.txt > nul
if ERRORLEVEL 1 goto err

echo Test 3: output file is busy
%PROGRAM% pack input.txt %PROGRAM% > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-output-file-is-busy.txt > nul
if ERRORLEVEL 1 goto err

echo Test 4: incorrect command pack\unpack
%PROGRAM% pask input.txt %TEMP%\output.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-unknown-command.txt > nul
if ERRORLEVEL 1 goto err

echo Test 5: incorrect data for unpack
echo  -- odd bites
%PROGRAM% unpack input-odd-bites-data-for-unpack.txt %TEMP%\output.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-odd-bites-for-unpack.txt > nul
if ERRORLEVEL 1 goto err

echo  -- zero count bite
%PROGRAM% unpack input-zero-counter-bites-data-for-unpack.txt %TEMP%\output.txt > "%TEMP%\console_output.txt"
if NOT ERRORLEVEL 1 goto err
fc.exe "%TEMP%\console_output.txt" expected-output-when-odd-bites-for-unpack.txt > nul
if ERRORLEVEL 1 goto err

echo Test 6: simple pack - unpack
%PROGRAM% pack input-simple-pack.txt "%TEMP%"\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-simple-pack-input.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% unpack "%TEMP%"\output.txt "%TEMP%"\output2.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output2.txt" input-simple-pack.txt > nul
if ERRORLEVEL 1 goto err

echo Test 7: 255 same bites pack - unpack
%PROGRAM% pack input-255-chars.txt "%TEMP%"\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-when-input-255-same-chars.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% unpack "%TEMP%"\output.txt "%TEMP%"\output2.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output2.txt" input-255-chars.txt > nul
if ERRORLEVEL 1 goto err

echo Test 8: 256 same bites pack - unpack
%PROGRAM% pack input-256-chars.txt "%TEMP%"\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-when-input-256-same-chars.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% unpack "%TEMP%"\output.txt "%TEMP%"\output2.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output2.txt" input-256-chars.txt > nul
if ERRORLEVEL 1 goto err

echo Test 9: 257 same bites pack - unpack
%PROGRAM% pack input-257-chars.txt "%TEMP%"\output.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output.txt" expected-output-when-input-257-same-chars.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% unpack "%TEMP%"\output.txt "%TEMP%"\output2.txt
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output2.txt" input-257-chars.txt > nul
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
