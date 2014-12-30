void OpenCLProcess::debug()
{
    for(auto const& ps : programSources) {
		std::cout << ps.first <<":\n"<< ps.second <<"\n"<< std::endl;
	}
	std::cout <<"And once more: "<< programSources["program.cl"] << std::endl;
}

/* Above functions prints:

program.cl:
__kernel void matvec_mult(__global float4* matrix,
    					  __global float4* vector,
						  __global float* result)
{
	int i = get_global_id(0);
	result[i] = dot(matrix[i], vector[0]);
}

And once more:
*/
