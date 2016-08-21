# Partitioning-using-Simulated-Annealing
###Simulated Annealing:
Partitioning is a combinatorial problem. For combinatorial problems finding the solution is NP-Complete. To deal with such problem simulated annealing is used. It is a probabilistic function for estimating the global optimum. It mainly emphasis on accepting the inferior moves to come out of the local optimum points and to reach the global optimum.
###Flow of the Simulated Annealing Algorithm:
The objective of the partitioning is to partition the nodes into two equal number of subsets such that the total number of connections between the two sets of nodes is minimum.
As shown in the flowchart the initial partition is randomly chosen using SRAND function in the C++ STD library. Seed for the SRAND function is the system time that is derived using time (0) function. SRAND function generates random values based on the seed value provided as an input. With different seeds it produces different numbers. Time (0) function produces the system time that keeps on changing. So, I find it as a best seed to produce the random numbers.
Initial temperature and maximum number of moves are specified to iteratively check for the local optimum point so as to reach the global optimum.
Calculating gain or the cost is the heart of the algorithm. We need to optimize it as much as possible. The time complexity of cost function that I have implemented is O (n) in the worst case. For calculating the gain heuristic from the KL algorithm is used. N is the number of nodes.
Moves are accepted based on the two gain and probability function. Move with positive gain is always accepted and if the gain is negative then a random number is generated between 0 and 1. And, if the random number is less than the Boltzmann function then move is accepted else move is not accepted.
Random number between 0 and 1 < Exponential (Gain/ K* Initial temperature)
It can be observed that the function accepts the inferior moves. The function seems to be random but it is not completely random. It can be observed from the function that at higher temperatures the exponential value will be close to 1 and as temperature decreases it moves close to 0. So the function accepts more number of inferior moves at the higher temperatures and as the temperature decreases probability of accepting inferior moves decreases. The value of K should be tuned such that exponential value stays within 0 to 1.
If the move is accepted, then the two nodes are swapped.
This process repeats iteratively till specified moves are completed.
