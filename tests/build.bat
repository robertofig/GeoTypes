@echo off

SET CompileOptions=/nologo /W3 /WX /wd4101 /wd4146 /wd4305 /wd4800 /wd4819 /wd4996
SET DebugBuild=/Zi /DDEBUG_BUILD
SET TinyBasePath="Z:\TinyBase\src"

if not exist "..\build" mkdir "..\build"
pushd ..\build
call cl ..\tests\test-base.cpp %CompileOptions% /I %TinyBasePath% /I ..\src %DebugBuild% /link /INCREMENTAL:NO
call cl ..\tests\test-wkb.cpp %CompileOptions% /I %TinyBasePath% /I ..\src %DebugBuild% /link /INCREMENTAL:NO
call cl ..\tests\test-shp.cpp %CompileOptions% /I %TinyBasePath% /I ..\src %DebugBuild% /link /INCREMENTAL:NO
popd