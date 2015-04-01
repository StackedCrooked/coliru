// Roulette Wheel Selection
// Return k best individual 
vector< vector<int> > selection(std::vector<int> fitness_vec,vector< vector<int> > P)
{
    vector< vector<int> > tmp_P;
	double x=0;
	int k;
	for (int i=0;i<N;i++)
	{
		//Random number in [0,1]
		x=RND;
		k=0; //index from 0
		// if number > probability but less than next probability then individual has been selected 
		while(k<N-1 && x>cal_cumsum_fitness(k,N,fitness_vec))
		{
			k=k+1;			
		}
		tmp_P.push_back(P[k]);		
	}
	return tmp_P;
}