@echo off
set Cwd=%cd%
set PkgDir=pkg\ShardOfAgony

mkdir pkg
mkdir %PkgDir%

copy /b plugin\package.json %PkgDir%\package.json
copy /b plugin\ShardOfAgony.js %PkgDir%\ShardOfAgony.js
copy /b plugin\ShardOfAgony.png %PkgDir%\ShardOfAgony.png
copy /b plugin\ShardOfAgony.png %PkgDir%\icon.png
copy /b plugin\ShardOfAgony.ogg %PkgDir%\ShardOfAgony.ogg
copy /b bin\helper.node %PkgDir%\helper.node

cd pkg
7z a ShardOfAgony.zip ShardOfAgony

cd %Cwd%
