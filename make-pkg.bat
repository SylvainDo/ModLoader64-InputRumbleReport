@echo off
set Cwd=%cd%
set PkgDir=pkg\InputRumbleReport

mkdir pkg
mkdir %PkgDir%

copy /b plugin\package.json %PkgDir%\package.json
copy /b plugin\InputRumbleReport.js %PkgDir%\InputRumbleReport.js
copy /b plugin\stone_of_agony.png %PkgDir%\stone_of_agony.png
copy /b plugin\stone_of_agony.png %PkgDir%\icon.png
copy /b plugin\stone_of_agony.ogg %PkgDir%\stone_of_agony.ogg
copy /b bin\helper.node %PkgDir%\helper.node

cd pkg
7z a InputRumbleReport.zip InputRumbleReport

cd %Cwd%
