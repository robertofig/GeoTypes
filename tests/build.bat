@echo off

SET TinyBasePath=""
SET CompileOptions=/nologo /I ..\src /I %TinyBasePath% /Zi /DDEBUG_BUILD /W3 /WX /wd4101 /wd4146 /wd4305 /wd4800 /wd4819 /wd4996
SET LinkOpts=/link /INCREMENTAL:NO

if not exist "..\build" mkdir "..\build"
pushd ..\build
call cl ..\tests\test-base.cpp %CompileOptions% %LinkOpts%
call cl ..\tests\test-wkb.cpp %CompileOptions% %LinkOpts%
call cl ..\tests\test-shp.cpp %CompileOptions% %LinkOpts%
del *.exp *.ilk *.obj
popd