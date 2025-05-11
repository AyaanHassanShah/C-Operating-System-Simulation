<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  
</head>
<body>

<h1>💻 OS Simulator - Operating System Project in C</h1>

<p><img src="https://img.shields.io/badge/Language-C-blue.svg" alt="Language"></p>

<p>
  <strong>OS Simulator</strong> is a terminal-based mini operating system built in C. It demonstrates essential OS concepts such as multitasking, memory management, process creation, and scheduling — using a user-friendly batch interface for preparing the environment.
</p>

<hr>

<h2>📜 Project Overview</h2>
<p>
  The system starts with a boot screen and accepts custom hardware configuration from the user (RAM, Hard Drive, CPU Cores). It then displays a list of available system tasks (like Calculator, Notepad, Snake Game, etc.). Each task runs as a separate process using <code>exec</code>-like behavior, simulating parallel execution and multitasking.
</p>

<h2>🚀 Features</h2>
<ul>
  <li>✅ Simulated OS boot with loading screen</li>
  <li>✅ Resource setup: RAM, Hard Disk, Cores</li>
  <li>✅ Process-based multitasking (new terminal per task)</li>
  <li>✅ User Mode & Kernel Mode switching</li>
  <li>✅ Support for minimizing or terminating tasks</li>
  <li>✅ Interrupt handling & context switching</li>
  <li>✅ Process scheduling and memory allocation</li>
  <li>✅ 15+ Interactive and background tasks</li>
</ul>

<h2>🧠 OS Concepts Demonstrated</h2>
<ul>
  <li>Process Creation using fork/exec</li>
  <li>Multitasking with terminal windows</li>
  <li>Context Switching</li>
  <li>Mutual Exclusion & Semaphores</li>
  <li>RAM/CPU Resource Allocation</li>
  <li>Multilevel Scheduling Queues</li>
  <li>User Mode vs Kernel Mode operations</li>
  <li>Simulated Interrupts and Blocked State</li>
</ul>

<h2>📁 Included Tasks (15+)</h2>
<ul>
  <li>AlarmClock</li>
  <li>BatteryStatus</li>
  <li>Calculator</li>
  <li>Calendar</li>
  <li>Chrome</li>
  <li>CountdownTimer</li>
  <li>MiniFileExplorer</li>
  <li>Notepad</li>
  <li>SimpleTaskManager</li>
  <li>SnakeGame</li>
  <li>TemperatureConverter</li>
  <li>TicTacToe</li>
  <li>TodoList</li>
  <li>TypingSpeed</li>
  <li>Xor_Cipher</li>
</ul>

<h2>🛠️ Getting Started</h2>

<h3>1. Clone the Repository</h3>
<pre><code>git clone https://github.com/your-username/&lt;your-folder-name&gt;.git
cd &lt;your-folder-name&gt;
</code></pre>

<h3>2. Compile the Tasks (If Not Precompiled)</h3>
<p>Use this command for each task:</p>
<pre><code>gcc TaskName.c -o TaskName.exe</code></pre>

<h3>3. Setup Environment Using the Batch File</h3>
<p>Run the batch script to build and prepare everything:</p>
<ul>
  <li>Via terminal:
    <pre><code>start build_all.bat</code></pre>
  </li>
  <li>Or double-click on <strong>build_all.bat</strong> from your folder</li>
</ul>

<h3>4. Manually Launch the OS</h3>
<p>
  After the environment is set up, <strong>you must manually run the OS executable</strong>:
</p>
<pre><code>bin\foldername.exe</code></pre>

<p>This will:</p>
<ul>
  <li>Display the OS boot screen with animation</li>
  <li>Start the interface and task menu</li>
  <li>Allow launching and managing tasks in separate terminals</li>
</ul>

<blockquote><strong>💡 Note:</strong> Replace <code>&lt;your-folder-name&gt;</code> with your actual folder name. Keep <code>foldername.exe</code> inside the <code>bin</code> directory.</blockquote>

<h2>📚 Usage Instructions</h2>
<ul>
  <li>Run <code>build_all.bat</code> to initialize the environment</li>
  <li>Then manually launch the OS: <code>bin\foldername.exe</code></li>
  <li>Use the interface to launch tasks (apps, games, tools)</li>
  <li>Each task opens in its own terminal (process)</li>
  <li>Minimize or close tasks as coded</li>
  <li>Shutdown the OS to exit all running processes</li>
</ul>


<h2>🙌 Credits</h2>
<ul>
  <li>Project by: <strong>LAWS</strong></li>
  <li>Group Partner: <strong>Muhammad Luqman</strong></li>
  <li>Lab Instructor: <strong>Sir Hassan Ahmed</strong></li>
  <li>Course: <strong>CL2006 - Operating Systems Lab (Spring 2025)</strong></li>
</ul>

<h2>📌 License</h2>
<p>This project is intended for educational use only.</p>

</body>
</html>
