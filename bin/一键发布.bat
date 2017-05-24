

@echo off
set windeployqt="D:\qt\Qt5.7.1_MSVC2013\5.7\msvc2013\bin\windeployqt.exe"

set myissue="demo.exe"


echo 当前windeployqt路径是: %windeployqt%


echo --------------------------------------
echo --------------------------------------
echo 若不正确: 
echo 关闭当前脚本，并修改其中的Qt路径。
echo --------------------------------------
echo 若路径正确:
pause
echo --------------------------------------
echo --------------------------------------

%windeployqt% %myissue%

pause