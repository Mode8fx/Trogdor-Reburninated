:: Ignoring those that are already at maximum gain, increase the gain of all WAV/OGG files in the current directory an equal amount, up to the point where one of them would clip.

@echo off
setlocal enabledelayedexpansion

set "OUTDIR=louder_audio_ignore_peaking"
set "MARGIN=0.1"

if not exist "%OUTDIR%" mkdir "%OUTDIR%"

echo Analyzing WAV/OGG files...
echo.

set "LOUDEST_PEAK_ELIGIBLE="

for %%F in (*.wav *.ogg) do (
    set "PEAK="
    set "SAFEGAIN="

    for /f "tokens=5" %%A in ('ffmpeg -hide_banner -nostats -i "%%F" -af volumedetect -f null NUL 2^>^&1 ^| findstr /c:"max_volume"') do (
        set "PEAK=%%A"
    )

    if defined PEAK (
        for /f %%G in ('powershell -NoProfile -Command "$gain = -1 * [double]'!PEAK!' - %MARGIN%; if ($gain -gt 0) { [math]::Round($gain, 2) } else { 0 }"') do (
            set "SAFEGAIN=%%G"
        )

        echo %%F: peak=!PEAK! dB, safe gain=+!SAFEGAIN! dB

        if not "!SAFEGAIN!"=="0" (
            if not defined LOUDEST_PEAK_ELIGIBLE (
                set "LOUDEST_PEAK_ELIGIBLE=!PEAK!"
            ) else (
                for /f %%B in ('powershell -NoProfile -Command "if ([double]'!PEAK!' -gt [double]'!LOUDEST_PEAK_ELIGIBLE!') { '!PEAK!' } else { '!LOUDEST_PEAK_ELIGIBLE!' }"') do (
                    set "LOUDEST_PEAK_ELIGIBLE=%%B"
                )
            )
        )
    ) else (
        echo Could not analyze %%F
    )
)

if not defined LOUDEST_PEAK_ELIGIBLE (
    echo.
    echo No files have positive safe gain. Copying all files unchanged.
    for %%F in (*.wav *.ogg) do copy /Y "%%F" "%OUTDIR%\%%F" >NUL
    pause
    exit /b
)

for /f %%G in ('powershell -NoProfile -Command "$gain = -1 * [double]'!LOUDEST_PEAK_ELIGIBLE!' - %MARGIN%; if ($gain -gt 0) { [math]::Round($gain, 2) } else { 0 }"') do (
    set "SHARED_GAIN=%%G"
)

echo.
echo Shared gain for eligible files: +!SHARED_GAIN! dB
echo.

for %%F in (*.wav *.ogg) do (
    set "PEAK="
    set "SAFEGAIN="

    for /f "tokens=5" %%A in ('ffmpeg -hide_banner -nostats -i "%%F" -af volumedetect -f null NUL 2^>^&1 ^| findstr /c:"max_volume"') do (
        set "PEAK=%%A"
    )

    for /f %%G in ('powershell -NoProfile -Command "$gain = -1 * [double]'!PEAK!' - %MARGIN%; if ($gain -gt 0) { [math]::Round($gain, 2) } else { 0 }"') do (
        set "SAFEGAIN=%%G"
    )

    if "!SAFEGAIN!"=="0" (
        echo %%F: copied unchanged
        copy /Y "%%F" "%OUTDIR%\%%F" >NUL
    ) else (
        echo %%F: +!SHARED_GAIN! dB
        ffmpeg -loglevel quiet -y -i "%%F" -af "volume=!SHARED_GAIN!dB" "%OUTDIR%\%%F"
    )
)

echo.
echo Done. Files saved to "%OUTDIR%".
pause