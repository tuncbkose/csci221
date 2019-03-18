Tree.cc

I don't know what to say about the create_tree program, I have followed the example on one of the lecture slides to assign the variables using the new function.

For destroy_tree function, a recursive implementation seemed like the best choice, given that each node can have two child nodes, so it recursively destroys the child nodes first, then the root node.

For path_to function, I have had some difficulty in the limited time I worked on it to keep the complexity lower, but I ended up calling the same recursive function twice, one for a boolean check, one for assignment.

For the node_at function, I created a helper function named give_pointer, which takes in the tree and and in expected cases 1 letter path information, then returns a pointer to the child of the tree in the requested direction. This function allowed me to both determine what to return when the node_at function has 1 length path, and also how node_at should continue when inputs are longer than one. The else case in the give_pointer function also acts to determine invalid inputs and return nullptr as a result.

Valgrind didn't return any errors, and I was too confused with Catch2 to use it.