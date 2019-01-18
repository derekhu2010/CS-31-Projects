# CS-31-Projects
These are some of the projects I coded in my Com Sci 31- Introduction to Computer Science class at UCLA. Below I will include a short description of each project.

POLL
In this project, I was provided with an input of polling data from one or more states. This project has 2 main components: checking that a poll data string has proper syntax, and tallying up how many votes a party received. A poll data string with proper syntax contains one or more state forecasts separated by a comma. A state forecast contains a state code, such as CA, followed by party results not separated by any characters. A party result is one or two digits followed by a single letter representing the party. For example, 15D is a valid party result that indicates that party D received 15 votes. This project is not case sensitive.

For example, given a poll data string Ca15d6R1i,vA5D1g7R the program would return that it has proper syntax and that party d has 20 votes (15 from California and 5 from Virginia).  In contrast, the program would deem that a poll data string CA15Dem5Rep,VA6Dem7Rep does not have proper syntax because parties are denoted by more than one letter in this case.

The focus of this project was extracting information from a string by identifying certain markers (e.g. the state codes, commas, and party codes) and traversing the string accordingly in order to count the number of votes.

RATE
This project involved 2 C-string arrays and 1 integer array of the same size that described “patterns.” All the elements at index 0 would be one pattern, the elements at index 1 would be another, etc. The integer represents how many words separate the two words. The first part of the project requires making the patterns proper, meaning deleting invalid patterns (i.e. patterns with words that contain non letters or empty strings, patterns with negative separation, and patterns that repeat) and moving valid patterns to the front of their arrays. 

In the second part of the project, a document is given in the form of a C-string. My task was to “rate” the document by counting how many patterns from occurred in the document. For example, “I like to code.” contains the pattern {“like”, “code”, 3} because the words “like” and “code” are separated by 3 or less words. In addition, any non-letters and non-spaces in a document were treated as if they did not exist. 

The focus of this project was to learn how to manipulate and traverse arrays smoothly and to edit their data properly. One particular challenge was formatting and editing the given document so that it contained only words separated by one space so that it could be properly “rated.”

ZOMBIES
This project is a game where a player is placed into an arena of zombies. The player and zombies alternate turns moving either up, down, left, or right. If a player is next to a zombie and moves in the direction of an adjacent zombie, that zombie is attacked. When a zombie is attacked, it loses one point and is moved one space in the direction is was attacked. If a zombie is hit twice or moves into a wall after getting hit once, it dies (hitting the wall serves as a second hit to the zombie). If a zombie moves onto the same space as the player when it is the zombies’ turn to move, the player dies.

The purpose of this project was creating multiple classes (e.g. zombie, player, arena, and game) and having them successfully interact with each other to create a game.
