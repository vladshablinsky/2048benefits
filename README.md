2048benefits
============

How to play: 
Use arrow keys to move the numbers. 

Game types:

1. Two numbers merge if they are equal into one twice as big as each of merged.

2. Two numbers merge if they are i-th and (i+1)-th Fibbonachi numbers. The result is the (i+2)-th Fibbonachi number.

3. You give the rules when two numbers merge. 'regulations.txt' contains these rules.

Format of the 'regulations.txt':

'regulations.txt' has N lines, each line contains three numbers (i, j, k, separeted by space) where k is i merged with j.
'regulations.txt' can't contain two lines (1: i_1, j_1, k_1 and 2: i_2, j_2, k_2), where i_1 = i_2 and j_1 = j_2.
When your 'regulations.txt' are set up, you can play according to them chosing the third option in the start menu of the game.
  

The full project in one file: https://www.dropbox.com/s/84iapnj2fe0rm9k/Game.rar
Runs best on Windows with Code::Blocks: http://www.codeblocks.org/downloads 

Created by Vladislav Shablinsky. Similar to http://gabrielecirulli.github.io/2048/
