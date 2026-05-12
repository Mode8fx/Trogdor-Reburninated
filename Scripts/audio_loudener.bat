@echo off
setlocal enabledelayedexpansion

:: Increase the gain of all WAV/OGG files in the current directory to their maximum amount without clipping.

set "OUTDIR=maximized_audio"
set "MARGIN=0.1"

if not exist "%OUTDIR%" mkdir "%OUTDIR%"

echo Analyzing and maximizing WAV/OGG files...
echo.

for %%F in (*.wav *.ogg) do (
    set "PEAK="

    for /f "tokens=5" %%A in ('ffmpeg -hide_banner -nostats -i "%%F" -af volumedetect -f null NUL 2^>^&1 ^| findstr /c:"max_volume"') do (
        set "PEAK=%%A"
    )

    if defined PEAK (
        for /f %%G in ('powershell -NoProfile -Command "$gain = -1 * [double]'!PEAK!' - %MARGIN%; if ($gain -gt 0) { [math]::Round($gain, 2) } else { 0 }"') do (
            set "GAIN=%%G"
        )

        echo %%F: peak=!PEAK! dB, gain=+!GAIN! dB

        ffmpeg -loglevel quiet -y -i "%%F" -af "volume=!GAIN!dB" "%OUTDIR%\%%F"
    ) else (
        echo Could not analyze %%F
    )
)

echo.
echo Done. Files saved to "%OUTDIR%".
pause