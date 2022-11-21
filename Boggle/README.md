# Boggle

the rule:
	1.at least 4 letters long
		=> check word length
		
	2.is a word found in the English dictionary
		=> build a trie and check the word recursively.
		
	3.can be formed by connecting neighboring letter cubes (using any given cube only once)
		=> by using backtracing, check each letter from left to right, top to bottom
	
	4.has not already been formed by the player in this game (even if there are multiple paths on the board to form the same word, the word is counted at most once)
		=> store words into set where there are not multiples.
		
limited:
	cout can be used in playOneGame function.
	recursion and backtracking should happen in Boogle Class instead of bogglePlay
		
Human player's turn:
	
	type the word
	check if the word is in the dictionary
	check if the word exist in the set.
	backtracing on the grid from left to right, top to bottom.
	if the word is valid, cacluate point by length of the word, and put the word into the set.
	
	using clearConsole() between each entering


Computer player's turn:
	
	sweep over the dictionary can select the word which length is longer than 3
	check if it exist in the set of human
	
	backtracking on the grid from left-top to right-bottom.
	if the word is valid, cacluate point by length of the word, and put the word into the computer set.
	

