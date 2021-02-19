# B+ Tree
Created B+ Tree from scratch
## Implementation:
1. Assumed the `order of B+ Tree to be 3` but can be done for other values too.
2. Created a `Node` structure which consists of a vector `key` which is a vector of pair of int,int maintaining the key value and its count, and an `Address` vector maintaining the child pointers of the node.
3. The insert function handles two cases using two seperate functions for insertion at leaf node and insertion at non-leaf node.
4. In insertion we need to check if there is an overflow condition or not. In case there is no overflow we directly insert the node at the leaf.
5. Else in case of overflow we need to check if parent exists or not. For maintaining the record of parents, I have maintained a `stack named Parents` which keeps the record of the parent node of node.
6. If parent doesn't exists, i.e. `parents stack is empty`, so we need to create a new node else we need to insert in the non-leaf node using the function `insert_nonleaf`. 

## Steps to Run:
1. g++ B+Tree.cpp
2. ./a.out `input_filename.txt`.
3. The output will be displayed on the terminal.
