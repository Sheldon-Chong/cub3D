![image](https://github.com/user-attachments/assets/2cf08668-edff-499e-83a2-357890cfd0f8)

# Cub3D
cub3D is a raycasting-based project inspired by Wolfenstein 3D, where you create a first-person 3D renderer in C. 

## 📖 Concepts covered in Cub3D
- Raycasting, DDA (Digital Differential Analyzer) algorithm
- Signals, movement, player rotation and collisions
- Textures, wall heights using ray-distance, fixing fisheye
- Uses the minilibx library 

## ⬇️ Clone
```
git clone git@github.com:Sheldon-Chong/cub3D.git
```

## ⏯️ Compile and run
```
make
./cub3D <path_to_map>
```

## My experience with this project (Sheldon)
I found the main concept of Cub3D and raycasting in general difficult to grasp when I first started. The online resources present during my time working on this project were sufficient for me to follow-along and create a rayscaster, but didn't help me really understand the concept of raycasting and why it worked. 

What helped me break-through the blockage in my understanding of this project was to actually visualize the rays in a 2D grid, before converting them into 3D rays. Before creating the 3D game, I created a bare-bones Cub3D in 2d, coding a basic raycaster, and drawing the rays, grid and player onto the screen. This makes up 70% of the meat of the code. The last 30% is a matter of taking these realtime calculations and rendering them onto the screen in 3D-space
