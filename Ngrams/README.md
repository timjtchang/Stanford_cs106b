Notes from the question:
	the map wraps around.
	#need to store first N-1 words
	
	prefix and suffix random test with "..."
	N can not less than 2
	the number of words to randomly generate should be at least N.
	N must be not greater than the number of words in the file.
	
	#using input>>variable to read a file on word at a time
	#To get random key, include "random.h" and call the global function randomInterger(min, max).
	
My mind map:

	void getCollection( & collection, & gramN ); // get collection
	void writeFile( & collection, & gramN, & wordNum) // to write
	void helper( & collection, & prefix, & wordNum, & count ); // to do recursion for writing 
	
	int gramN;
	map< vector<string>, vector<string> > collection  // to store the relationship between diff words
	
	
	implement:
		
		getCollection:
		
			vector<string> wrappingWord; // to store N words for wrapping
			vector<string> key; // to store key that will be putted in
			
			for loop gramN-1 times: //to store wrappingWord
				wrappingWord.push_back(string);
				key.push_back(string);
			
			while( input>>word ):
				collection[key].push_back( word );
				key.erase(begin);
				key.push_back(word);
			
			while( wrappingWord.size() != 0 ):
				word = wrappingWord.front());
				collection[key].push_back( word );
				key.erase(begin);
				key.push_back(word);
				
		wrtieFile:
		
			random = randomInterger( 0, collection.size() );
			vector<string> start;
			
			start = ( collection.begin()+random )->first;
			
			helper( collection, start, wordNum, 0);
			
		helper:
			
			if( wordNum == count ) return;
			
			vector<string> suffix = collection[prefix]
			
			random = randomInterger( 0, suffix.size());
			word = suffix[random];
			cout<< word <<" ";
			
			prefix.erase(begin);
			prefix.push_back(word);
			
			helper( collection, prefix, wordNum, count++);
				
				
				
