# Aria-Robot-AI
<p>Artificial Intelligence built for simulated differential drive Pioneer robot. Built in C++ using Advanced Robot Interface for Applications (ARIA).</p>
<p>The AI uses FSM to switch between three types of behaviours (Wander, Avoid, Follow). Furthermore, it builds a scattermap of the environment based on the information retrieved from the robot's sensors.

<h2>Simulated Robot Path</h2>
<img src="https://github.com/marcin388/Aria-Robot-AI/blob/master/path.jpg">
<h2>AI Generated Scattergram Map</h2>
<img src="https://github.com/marcin388/Aria-Robot-AI/blob/master/Scattergram.png">

<h2>Running Project</h2>
<p>Project requires <a href="https://github.com/srmq/MobileSim">MobileSim</a> to run. MobileSim is a software that simulates mobile robots created using ARIA within user-created maps.</p>
<p>After downloading and installing MobileSim on your computer, run it and use it to open one of the maps found within maps folder of this project.</p>
<p>Once map and robot is loaded within the MobileSim program, run this (ARIA-ROBOT-AI) program using the debug mode on x86 memory format.
