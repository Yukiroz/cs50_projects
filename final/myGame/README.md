# Project Turned-Based RPG
#### Video Demo:  https://www.youtube.com/watch?v=qyeC2HEnZaM
#### Description:

Project Turned-Based RPG (PTBRPG) is my Final Project for CS50x. The project took 8 days to complete, from 15/6/2023 to 24/6/2023 (early in the morning). Project PTBRPG is a video game made with the lua programming language and using the Löve or LOVE2D framework. Learning the syntax was easier than expected because of many similarities with Python. I used VSCODE for code editing since it was almost identical with the cs50 online code editor environment.

The project had many different parts listed here:

Learning the basics of lua and love2d
Learning the basics of vscode
Mapping the Project
    Creating an Environment
        Learning to Use Tiled for the environment
    Creating a player Character
        Learning asprite to make and edit sprites
    Creating Player Movement and coliders
        Learning the sti library
    Making animations for the player and the npcs
        Learning the anim8 library
    Implementing a camera
        Learning the cam library
    Implementing colliders to interact with the environment
        Learning sti, windfield and flux libraries
    Creating the 3 levels of the Game and adding colliders for borders
    Creating transition points using the colliders to go from an area to another
    Creating colliders for on screen objects and adjusting draw priority to create a false sense of 3d in the 2d environment
    Making a sound effect to indicate the collisions in Bfxr
    Creating 3 new songs for the Project using Flstudio. One for the overworld map, one for the cave and the boss area and one for battles
    Creating the level.lua file to allow the draw and update function to check for triggers and level changes
    Creating the game.lua file to allow the draw and update function to check for triggers and state changes
    Implementing Battle
        Creating HP tracking for player and enemies, drawing each when necessary
        Creating movement and animations for the different turns using flux and anim8
        Creating 2 different states, command and battle to track player controls
        Drawing the border sprite, and using anim8 implementing the commands with pixelart
        Tracking player exp and levels and adding exp when succesfully defeating an enemy
        Implementing the attack functionality
        Implementing the escape functionality
        Moving, removing, and editing colliders to adjust player position in and out of battle
Implementing every step