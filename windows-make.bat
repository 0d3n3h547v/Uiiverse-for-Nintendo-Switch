@echo off
echo.
echo.   Automated makefile (with nxlink) by Waifro
echo.
make
echo.
echo.   Prompting to send nro to NetLoader
echo.
nxlink -a 192.168.188.38 uiiverse.nro
echo.
echo.           ### ATTENTION ###
echo.      unused files will be deleted
echo.

rmdir build /s