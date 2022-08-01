Gas-Particles-Simulator
======
This project is a simulator that replicates the behavior of ideal gas inside a container. I assumed gas particles as balls with the same mass that collide elastically. At first, all balls have a random speed in random directions, and then they begin colliding with each other.
I programmed this in C++ and used the SDL library for visualization.
While the simulation is running, the velocitieies of all particles are saved into a file. I used this data to analyze the distribution of velocity in this particles. My analysis showed that very soon after the simulation starts, the distribution approaches a certain curve, which is very simillar to a Maxwell-Boltzman distribution.
Special thanks to my friend Negin Hashemzadeh for helping with the analysis.

https://user-images.githubusercontent.com/54746341/182053237-44e2f7bb-493e-4b27-8952-c6ba38f02817.mp4

A version of the video with better quality can be found in the repo.

![image](https://user-images.githubusercontent.com/54746341/182052228-b2ebee8f-f8fa-46b0-9ded-5873e8a8675e.png)





