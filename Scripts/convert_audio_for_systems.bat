:: Convert all WAV/OGG files in the current directory to match what the game expects (useful for both music and sound effects). Converted songs are placed in the following directories:

:: most_systems_ogg: Recommended for most systems.
:: most_systems_wav: If you are playing on an extremely weak device, then WAV may have better performance (music) and initial load time (sound effects) than OGG.
:: 3ds_psp_ogg: Lower-quality OGG files (smaller and faster-loading). Recommended for use only on 3DS and PSP.
:: 3ds_psp_wav: Lower-quality WAV files. These are much larger than OGG, but have better initial load times for sound effects (makes little to no difference for music). Recommended for use only on 3DS and PSP.

@echo off
setlocal EnableExtensions DisableDelayedExpansion

where ffmpeg >nul 2>&1
if errorlevel 1 (
    echo FFmpeg was not found on PATH.
    echo Install FFmpeg or add it to PATH, then run this script again from the folder with your source audio files.
    pause
    exit /b 1
)

set "had_input="
set "had_errors="

if exist "*.wav" set "had_input=1"
if exist "*.ogg" set "had_input=1"

if not defined had_input (
    echo No WAV or OGG files were found in the current directory.
    pause
    exit /b 0
)

call :convert_for_system most_systems 44100
call :convert_for_system 3ds_psp 22050

echo.
if defined had_errors (
    echo Finished with one or more conversion errors.
    pause
    exit /b 1
)

echo Finished. Original files were left unchanged.
pause
exit /b 0

:convert_for_system
set "system_name=%~1"
set "sample_rate=%~2"

echo.
echo ==== %system_name% (%sample_rate% Hz) ====

if not exist "%system_name%_wav" mkdir "%system_name%_wav"
if not exist "%system_name%_ogg" mkdir "%system_name%_ogg"

for %%F in (*.wav *.ogg) do if exist "%%~fF" call :convert_one "%%~fF" "%%~nF" "%%~xF" "%system_name%" "%sample_rate%"
exit /b 0

:convert_one
set "input_path=%~1"
set "input_name=%~2"
set "input_ext=%~3"
set "system_name=%~4"
set "sample_rate=%~5"

set "source_label=%input_ext:.=%"
set "output_stem=%input_name%"

REM Avoid collisions if both foo.wav and foo.ogg exist in the same source folder.
if exist "%input_name%.wav" if exist "%input_name%.ogg" set "output_stem=%input_name%_from_%source_label%"

set "wav_output=%system_name%_wav\%output_stem%.wav"
set "ogg_output=%system_name%_ogg\%output_stem%.ogg"

echo [%system_name%] WAV  "%~nx1" -^> "%wav_output%"
ffmpeg -hide_banner -loglevel error -y -i "%input_path%" -vn -ar %sample_rate% -c:a pcm_s16le "%wav_output%"
if errorlevel 1 (
    echo Failed: "%wav_output%"
    set "had_errors=1"
) else (
    echo Done: "%wav_output%"
)

echo [%system_name%] OGG  "%~nx1" -^> "%ogg_output%"
ffmpeg -hide_banner -loglevel error -y -i "%input_path%" -vn -ar %sample_rate% -qscale:a 4 "%ogg_output%"
if errorlevel 1 (
    echo Failed: "%ogg_output%"
    set "had_errors=1"
) else (
    echo Done: "%ogg_output%"
)

exit /b 0