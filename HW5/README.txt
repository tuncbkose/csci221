README document for Tunc Kose's gridpi function as a part of HW5.

The result of gridpi for 10 input is 3.52.
The result of gridpi for 100 input is 3.1812.
The result of gridpi for 1000 input is 3.14554.
The result of gridpi for 10000 input is 3.14199.

I think the complexity of my gridpi function is n^2 because it has a for loop inside another for loop, both go from 0 to n.

Time measurements:

Input	Time taken
10	  0m0.005s	
100	  0m0.006s
1000	0m0.063s
10000	0m2.796s

Function with constexpr:
Input	Estimate	Time taken
10	  3.52		  0m0.005s
100	  3.1812		0m0.005s
1000	3.14554		0m0.042s-66s -> multiple trials

The estimates of the functions are the same, which is normal since the addition of constexpr doesn't affect the logic of the function. However, the time it took to compile and execute these changed. 
Without the constexpr expression, the code was compiled at relatively the same time, however took longer to execute as the input grew bigger. This is because the compilation process only included the logic of the function, which was independent of the input. 
Since constexpr makes the output compiled as well, it took longer to compile as the input increased. 
In addition, I have noticed that in my VM, when constexpr was added, inputs 10 and 100 had the same run time, but 1000 had a significantly longer run time which changed slightly when I executed it repeatedly.
