To compile with g++ your should only need to do g++ tic.cpp main.cpp, thats how I compiled it and it works fine for me.
To start you're game from the begining make sure the file save.txt is empty or just make the first line of save.txt Choosing
line 8 is attack after your create you're save file and are moved passed Choosing you can close the program and make it a higher number, 

the most health an enemy has is 1000 if you set it to 2000 you will get through everything in 1 hit its not ideal for testing 
individual battles but if you want to test endings quickly it works
  
There is a warning that the program can reach end of non void function without returning, disregard that it will not happen.
An int function was used for the adventure game because it is supposed to reset your save after you win and I don't believe it would've worked
with a void function as after setting the currentArea back to choosing the game would just start again
  
After each area the game will be saved to save.txt.
