@echo off

set wildcard=*.hpp *.cpp

echo ------------------------------------------------------------------------------
echo statics FOUND:
echo ------------------------------------------------------------------------------
FINDSTR /S /N /I /L /C:"static " %wildcard%
echo ------------------------------------------------------------------------------
echo.
echo ------------------------------------------------------------------------------
echo GLOBALS FOUND:
echo ------------------------------------------------------------------------------
FINDSTR /S /N /I /L "GLOBAL" %wildcard%
echo ------------------------------------------------------------------------------
