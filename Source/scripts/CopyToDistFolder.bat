SET distPath="%~1\dist"
CALL :checkExistenceAndCreate %distPath%
SET nativePath="%distPath%\native"
CALL :checkExistenceAndCreate %nativePath%
CALL :copyBuiltNodeExtension "%~2*.node"

:checkExistenceAndCreate
IF NOT EXIST %~1 (
    ECHO Create %~1 folder.
    MD %~1
) ELSE (
    ECHO %~1 folder exists.
)
EXIT /B 0

:copyBuiltNodeExtension
XCOPY /y /i %~1 %nativePath%
EXIT /B 0