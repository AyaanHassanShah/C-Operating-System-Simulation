@echo off
mkdir Bin 2>nul
gcc src\main.c src\pcb.c -o bin\MyOS.exe
gcc Tasks\AlarmClock.c -o Bin\AlarmClock.exe
gcc Tasks\BatteryStatus.c -o Bin\BatteryStatus.exe
gcc Tasks\Calculator.c -o Bin\Calculator.exe
gcc Tasks\Calendar.c -o Bin\Calendar.exe
gcc Tasks\Chrome.c -o Bin\Chrome.exe
gcc Tasks\Countdowntimer.c -o Bin\Countdowntimer.exe
gcc Tasks\MiniFileExplorer.c -o Bin\MiniFileExplorer.exe
gcc Tasks\Notepad.c -o Bin\Notepad.exe
gcc Tasks\SimpleTaskManager.c -o Bin\SimpleTaskManager.exe
gcc Tasks\SnakeGame.c -o Bin\SnakeGame.exe
gcc Tasks\TemperatureConverter.c -o Bin\TemperatureConverter.exe
gcc Tasks\TicTacToe.c -o Bin\TicTacToe.exe
gcc Tasks\TodoList.c -o Bin\TodoList.exe
gcc Tasks\TypingSpeed.c -o Bin\TypingSpeed.exe
gcc Tasks\Xor_Cipher.c -o Bin\Xor_Cipher.exe

echo.
echo ✅ Compilation finished. All .exe files are in the Bin folder.
pause
