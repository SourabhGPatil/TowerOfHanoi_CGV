# SIMULATION OF TOWER OF HANOI PROBLEM USING OPENGL API
------------

> This project was done as a part of the **Computer Graphics and Visualization** subject.

------------
## Introduction
The process of designing, 2D, 3D, and animating an object is known as Computer Graphics. Modelling, simulation, and visualisation of an object or a problem are all possible with computer graphics. Since the advent of photography and television, interactive computer graphics has been the most popular means of creating images. It also has the benefit of being able to create images not only of concrete real-world objects but also of abstract, synthetic objects such as mathematical surfaces and data with no apparent geometry, such as survey results, using a computer.

## Objective
The aim of this project is to demonstrate how OpenGL can be used to simulate the Tower of Hanoi problem. The keyboard is the primary means of input in this project.

## OpenGL
OpenGL is a graphics rendering API that is independent of operating systems and produces high-quality colour images consisting of geometric and image primitives. This interface is made up of approximately 150 distinct commands that you can use to define the objects and operations used to create immersive three-dimensional applications. Silicon Graphics Inc. (SGI) created OpenGL in 1992, and it is commonly used in CAD, augmented reality, science visualisation, knowledge visualisation, and flight simulation. It's also used in computer games, where it competes with Direct3D on Microsoft's Windows platform.

## Tower of Hanoi's Problem Explanation
Three rods and n discs make up the Tower of Hanoi, a mathematical puzzle. The aim of the puzzle is to shift the whole stack to a different rod by following these basic rules:

1. At a given time, only one disc can be transferred.
2. Each move consists of taking the upper disk from one of the pegs and placing it on top of another peg i.e., a disk can only be moved if it is the uppermost disk on a stack.
3. A smaller disc cannot be mounted on top of a larger disc.

## Algorithm
	Step 1 - Start.
	Step 2 - Let the three towers be the Source, Destination, and Aux.
	Step 3 - Read the number of disks, n from the user.
	Step 4 - Move n-1 disks from Source to Aux.
	Step 5 - Move n-th disk from Source to Destination.
	Step 6 - Move n-1 disks from Aux to Destination.
	Step 7 - Repeat Steps 3 to 5, by decrementing n by 1.
	Step 8 - Stop. 
	
## Running the code on Ubuntu
1. Open the terminal and navigate to the directory (folder) containing the .cpp file (using the cd command).
2. Compile the code using the command `g++ tower.cpp`
3. Now execute the program using the command `./a.out tower.cpp`


## Output Screenshots
![TowerOfHanoi_1](https://user-images.githubusercontent.com/81312909/231516270-ed5b4f75-e258-47f5-a6fc-14bdb0fa2cb4.png)
------------
![TowerOfHanoi_2](https://user-images.githubusercontent.com/81312909/231516379-2e570103-b3ad-47de-9a30-4390b79d7b07.png)
------------
![TowerOfHanoi_3](https://user-images.githubusercontent.com/81312909/231516420-660864ad-44e4-4063-84a7-2f1891f8804b.png)
------------
![TowerOfHanoi_4](https://user-images.githubusercontent.com/81312909/231516422-c77d2050-cfb3-4c9d-97cd-4a282c0d9412.png)
------------
![TowerOfHanoi_5](https://user-images.githubusercontent.com/81312909/231516426-b6004459-e199-4f0e-971e-fe15ef4b1f58.png)
------------
![TowerOfHanoi_6](https://user-images.githubusercontent.com/81312909/231516428-f1242354-9cad-42f2-b6fe-ced588fc3c4b.png)
------------

