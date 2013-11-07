#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <iomanip>

// Inline function to return random values between 0 and 1
inline double probability_gen()
{
    return rand()*1.0 / RAND_MAX;
}

// Graph represented by connectivity matrix format
class graph
{
	const int matrixsize;
	int range; // Edge distance ranges
	double density; //Edge density
	std::vector<std::vector<int>> matrix;

	// Using a struct to record and print the shortest path
	// A record of the fromvertex is required to tracback the path traversed for the shortest distance
	struct vertexnode{
		int fromvertex;
		int vertex;
	};

	// The open set and closed set datatype, represented by vertexnode and distance pair
	typedef std::pair<vertexnode, int> settype;
	std::vector<settype>    openset;
	std::vector<settype>    closedset;
	std::vector<int>		visitedvertices;
	// The comparison function will be used to create a heap (or Priority Queue) data structure
	// to order the openset such that the smallest distance is always returned first.
	std::function<bool(settype &a, settype&b)> cmpfn;

	bool dijkstrapath(int &start, int stop, int &shortestdist)
	{
		if (start >= matrixsize || stop >= matrixsize)
			return false;

		// Mark "start" vertex as visited
		visitedvertices[start] = 1;

		// Have we reached the final destination?
		if (start == stop)
			return true;

		// reference to graph data representing the vertices connected to "start"
		std::vector<int> &row = matrix[start];

		int col = 0, curdistance = 0;
		// flag to check if there is a next vertex
		bool foundnextvertex = false;

		// Following steps populates/updates the openset, with the next reachable vertices and their relative distance from start
		for (auto it = row.cbegin(), endit = row.cend(); it != endit; ++it)
		{
			curdistance = *it;

			// If a value exists, then the vertices are connected
			//  And we don't want to consider vertices visited already - that are in the closed set
			if (curdistance && !visitedvertices[col])
			{
				foundnextvertex = true;
				bool insertvertex = true;
				// Check if the given vertex exists in the openset already
				for (auto openit = openset.begin(), openendit = openset.end(); openit != openendit; ++openit)
				{
					settype &opensetdata = *openit;
					// The openset stores a pair - vertex, distance
					if (opensetdata.first.vertex == col)
					{
						insertvertex = false;
						// If the current distance to that vertex is smaller than that stored in the openset, then update the openset
						if (curdistance + shortestdist < opensetdata.second)
						{
							opensetdata.second = curdistance + shortestdist;
							opensetdata.first.fromvertex = start;
						}
						break;
					}
				}
				if (insertvertex)
				{
					openset.push_back(std::make_pair(vertexnode{ start, col }, curdistance + shortestdist));
				}
			}
			++col;
		}

		// Didn't find any next vertex and openset is empty - nowhere to go
		if (!foundnextvertex && openset.empty())
			return false;

		// Make a heap from the openset data, always returning the lowest distance(which is the second value in the settype data)
		std::make_heap(openset.begin(), openset.end(), cmpfn);

		// Add the vertex with the shorted distance from openset to closed set
		settype &frontval = openset.front();
		shortestdist = frontval.second;

		closedset.push_back(std::make_pair(frontval.first, shortestdist));
		start = frontval.first.vertex;

		//Remove the vertex with the shortest distance from the openset
		std::pop_heap(openset.begin(), openset.end(), cmpfn);
		openset.pop_back();

		// Recursive function till we reach stop or no more destinations
		return dijkstrapath(start, stop, shortestdist);
	}

	// helper function to print the generated matrix
	std::ostream& print_graph(std::ostream &ostr) const
	{
		ostr << " **** Matrix ****\n";
		for (int i = 0; i < matrixsize; ++i)
		{
			for (int j = 0; j < matrixsize; ++j)
			{
				ostr << std::right << std::setw(2) << matrix[i][j];
			}
			ostr << std::endl;
		}
		return ostr;
	}

	// Populate the connectivity matrix
	void generate()
	{
		for (int i = 0; i < matrixsize; ++i)
		{
			for (int j = 0; j < matrixsize; ++j)
			{
				// Omit the diagonal to avoid loops, and when the probability is greater than density
				// connect the vertices, setting the distance to values between 0 and range
				if (i != j && probability_gen() <= density)
				{
					matrix[i][j] = rand() % range;
				}
			}
		}
	}

	// Are vertices connected?
	bool is_connected(int vertexa, int vertexb)
	{
		return (0 != matrix[vertexa][vertexb]);
	}

	void print_traversedpath(int startpos, int stop)
	{
		if (closedset.empty())
			return;

		int fromindex = stop, lastvisited = stop;

		auto revit = closedset.rbegin();
		lastvisited = (*revit).first.vertex;
		fromindex = (*revit).first.fromvertex;

		std::cout << "Traversed path(in reverse): " << std::right << std::setw(2) << lastvisited << " <-- ";
		++revit;

		// The closed set has shortest distances to different vertices.
		// But to get the shortest path, the fromvertex is required to trace the path back to start
		for (auto revitend = closedset.rend(); revit != revitend; ++revit)
		{
			if (fromindex == (*revit).first.vertex)
			{
				fromindex = (*revit).first.fromvertex;
				lastvisited = (*revit).first.vertex;
				std::cout << std::right << std::setw(2) << lastvisited << " <--  ";
			}
		}
		std::cout << std::endl;
	}

public:
	graph(int sz = 50, double d = 0.1, int r = 10) :matrixsize(sz), range(r), density(d)
	{
		// Set the 2D matix vector size - Ref: http://www.cplusplus.com/forum/beginner/12409/
		matrix.resize(matrixsize, std::vector<int>(matrixsize, 0));
		visitedvertices.resize(matrixsize);
		this->generate();
	}



	int getdijikstrapath(int start, int stop)
	{
		// The start and stop vertices should be valid and within the matrix size.
		if (start >= matrixsize || stop >= matrixsize)
			return false;

		// clear the data to be reused
		closedset.clear();
		openset.clear();
		visitedvertices.assign(matrixsize, 0);

		// lambda function to use the second value(distance) of the settype data for comparison 
		cmpfn = [](settype &a, settype&b)->bool{ return a.second > b.second; };

		int shortestpath = 0;
		int startpos = start;

		// Initialising closedset with the startnode
		closedset.push_back(std::make_pair(vertexnode{ start, start }, 0));

		if (dijkstrapath(startpos, stop, shortestpath))
		{
			print_traversedpath(start, stop);
			return shortestpath;
		}
		else
			return 0;
	}

	friend std::ostream& operator<<(std::ostream& out, const graph& gr)
	{
		return gr.print_graph(out);
	}

};


int main()
{
	// Random Seed initialiser
	srand(static_cast<unsigned int>(time(0)));

	{
		const unsigned graphsize = 50;

		graph graph_10pdensity(graphsize, 0.10, 10);
		std::cout << graph_10pdensity;

		int shortest_path, total_shortestpath = 0, pathcounts = 0;
		double avg_shortestpath = 0;
		for (unsigned i = 1; i < graphsize; ++i)
		{
			shortest_path = graph_10pdensity.getdijikstrapath(0, i);
			if (shortest_path > 0)
			{
				std::cout << "shortest path between 0 and " << i << " is " << shortest_path << std::endl;
				pathcounts += 1;
				total_shortestpath += shortest_path;
			}
		}
		if (pathcounts)
		{
			avg_shortestpath = total_shortestpath*1.0 / pathcounts;
			std::cout << "Average shorted path with 10 % density is " << avg_shortestpath << std::endl;
		}
		else
			std::cout << "No paths found" << std::endl;


		graph graph_20pdensity(graphsize, 0.2, 10);
		std::cout << graph_20pdensity;
		total_shortestpath = 0;
		pathcounts = 0;
		avg_shortestpath = 0;
		for (unsigned i = 1; i < graphsize; ++i)
		{
			shortest_path = graph_20pdensity.getdijikstrapath(0, i);
			if (shortest_path > 0)
			{
				std::cout << "shortest path between 0 and " << i << " is " << shortest_path << std::endl;
				pathcounts += 1;
				total_shortestpath += shortest_path;
			}
		}
		if (pathcounts)
		{
			avg_shortestpath = total_shortestpath*1.0 / pathcounts;
			std::cout << "Average shorted path with 20 % density is " << avg_shortestpath << std::endl;
		}
		else
			std::cout << "No paths found" << std::endl;


		getchar();
		exit(0);
	}
}