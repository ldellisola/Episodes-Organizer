# Episodes Organizer

CAUTION: It shouldn't delete any of your files, I wanted to make sure that the only way the program got to the rename part was after everything was checked, but still I may have missed something, so use it under your own risk.

Also, the latest commit doesn't quite work well (i think), i should probably try to add a release...

This is a small program to rename all the episodes of a given season in a second (or a few). We get out data from https://epguides.com and we used a library user talh123 @ sourceforge created to parse cvs files.(https://sourceforge.net/projects/cccsvparser/)

Right now it is fairly basic, it won't rename any file if there are not the same ammount of files than episode names. One example would be TV shows that have 2 in 1 episodes, but in the DVD release they wouldn't merge them together.

I'm planning on solving this limitations but I don't have the time.

TO DO:
  - find a way to retrieve metadata or some other way to know the lenght of the video file. This is the last big thing.
  - check if the files have different name and thus asking again where the episode is in the name.
  - in the long future, create a GUI with allegro to make this much more comfortable.
  - another thing i would want to do is to rename a whole tv show, but this is also in the long future.



Ps: It is indifferent to upper or lower cases.
