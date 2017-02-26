SET arch=%1
SET configure=%2
SET addonName=%3

SET frontendFolder=..\..\bin\Electron\resources\app\
SET addonFolder=%frontendFolder%\build\%configure%\

IF NOT EXIST %addonFolder% DO (
    MD %addonFolder%
)

FOR %%f IN ("..\package.json", "..\index.html", "..\main.js", "..\nativeHandler.js", "..\audioPlugin.js", "..\EventEmitter.min.js") DO (
    XCOPY /Y %%f "%frontendFolder%"
) 

XCOPY /Y ".\%arch%\%configure%\%addonName%.node" "%addonFolder%"
