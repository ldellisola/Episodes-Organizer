# Episodes Organizer

CAUTION: It shouldn't delete any of your files, I wanted to make sure that the only way the program got to the rename part was after everything was checked, but still I may have missed something, so use it under your own risk.

This is a small program to rename allthe episodes of a given season in a second (or a few). We get out data from https://epguides.com and we used a library user talh123 @ sourceforge created to parse cvs files.(https://sourceforge.net/projects/cccsvparser/)

Right now it is fairly basic, it won't rename any file if there are not the same ammount of files than episode names. One example would be TV shows that have 2 in 1 episodes, but in the DVD release they wouldn't merge them together. Another limitation is that you have to be very specific while typing the name of the show. For example, if you want to rename 'Friends' episodes, you'll have to type "Friends (1994)" as there is another series called Friends. In the same manner, if you want to do it with 'The Office', you have to tell the program which adaptation it is. For the American version, you'll have to type "The Office (US)".

I'm planning on solving this limitations but I don't have the time.



Ps: It is indifferent to upper or lower cases.
