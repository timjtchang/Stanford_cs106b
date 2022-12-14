Huffman

{ char:frequency }

priority queue built by binary tree
count as priority

Priority Queue< Binary Tree >

Using hash map to record the charactor and the count
put each element into priority queue

while( nubmer of Q elements != 1 ){

	remove first two elements
	create a new node as the sum of these two elements
	add these two elements as the children of the node
	add the node into the Q

}

record huffman code into the hash map by loop over the tree.

