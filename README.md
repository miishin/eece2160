# eece2160
EECE2160: Controlling robotic arm with C programs + Simulink designs uploaded to Xilinux ZedBoard.

C++ program project synopsis:
Program arm to pick up a water bottle and use it to knock down
the other water bottles on the table. 

Robotic arm was controlled through memory addresses on the ZedBoard. 

Simulink program project synopsis:
Two water bottles are laid out in front of the robotic arm, with three spots 
on the table marked 1 to 3. The bottles occupy spaces 1 and 2. Move bottle from 
space 2 to space 3, then the bottle from space 1 to space 2, and then the 
bottle from space 3 to space 1. 

This was done in Simulink so circuit designs were uploaded directly to 
the ZedBoard (no programming). Timing was done through clock cycles and robot 
arm motors controlled with Pulse-width modulation (PWM) signals. 
