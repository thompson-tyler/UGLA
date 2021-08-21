# UGLA
Untitled Game-Like Application

# CONTROLS
A/D: move left/right
<br>
W: jump
<br>
S: dive
<br>
UP: raise ground
<br>
LEFT/RIGHT: push ground
<br>
SPACE: ground jump
<br>
PLUS/MINUS: zoom in/out
<br>
ESC: exit
<br>
TILDE: pause

# SUMMARY
I play video games from time to time and I’m obsessed with world interactivity as a major game mechanic. Drawing inspiration from the interactivity of games like Breath of the Wild and the voxel style of Terraria, I wrote a proof of concept game whose primary mechanic is manipulating the ground to navigate and attack an enemy.
<br><br>
Though it's not a full-fledged game, I refined much of my understanding of OOP by writing everything but the graphics library from scratch, all in C++. This involved approach let me optimize entity and collision management, allowing for upwards of 100,000 voxels to be placed in the world with minimal CPU usage. Entities take damage and are sent flying when ground tiles are launched at them, and once tiles fall to the ground they become apart of the world again. Gameplay is snappy and I've spent tons of time just messing with the mechanics to see what the player can do.
