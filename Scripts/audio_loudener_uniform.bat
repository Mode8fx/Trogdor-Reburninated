:: Increase the gain of all WAV/OGG files in the current directory an equal amount, up to the point where one of them would clip. If at least one file is already at maximum gain, then nothing changes.

@echo off
setlocal enabledelayedexpansion

set "OUTDIR=louder_audio"
set "MARGIN=0.1"

if not exist "%OUTDIR%" mkdir "%OUTDIR%"

echo Analyzing WAV/OGG files...
echo.

set "LOUDEST_PEAK="

for %%F in (*.wav *.ogg) do (
    set "PEAK="

    for /f "tokens=5" %%A in ('ffmpeg -hide_banner -nostats -i "%%F" -af volumedetect -f null NUL 2^>^&1 ^| findstr /c:"max_volume"') do (
        set "PEAK=%%A"
    )

    if defined PEAK (
        echo %%F: peak=!PEAK! dB

        if not defined LOUDEST_PEAK (
            set "LOUDEST_PEAK=!PEAK!"
        ) else (
            for /f %%B in ('powershell -NoProfile -Command "if ([double]'!PEAK!' -gt [double]'!LOUDEST_PEAK!') { '!PEAK!' } else { '!LOUDEST_PEAK!' }"') do (
                set "LOUDEST_PEAK=%%B"
            )
        )
    ) else (
        echo Could not analyze %%F
    )
)

if not defined LOUDEST_PEAK (
    echo.
    echo No files could be analyzed.
    pause
    exit /b
)

for /f %%G in ('powershell -NoProfile -Command "$gain = -1 * [double]'!LOUDEST_PEAK!' - %MARGIN%; if ($gain -gt 0) { [math]::Round($gain, 2) } else { 0 }"') do (
    set "GAIN=%%G"
)

echo.
echo Loudest peak: !LOUDEST_PEAK! dB
echo Shared gain: +!GAIN! dB
echo.
echo Creating louder copies...
echo.

for %%F in (*.wav *.ogg) do (
    echo %%F: +!GAIN! dB
    ffmpeg -loglevel quiet -y -i "%%F" -af "volume=!GAIN!dB" "%OUTDIR%\%%F"
)

echo.
echo Done. Files saved to "%OUTDIR%".
pause