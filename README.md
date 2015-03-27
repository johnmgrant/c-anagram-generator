# AnagramGenerator
An anagram generator that obtains all of the permutations of a word. 
To improve the memory issue, I plan on exporting the permutation list to a file and only store one word at a time in memory. This will decrease the amount of dynamic memory that I need to allocate.
To increase performance, I plan on running 2-4 threads at a time depending on the amount of permutations.
