    std::pair<std::array<Vector3i,4>::iterator,std::array<Vector3i,4>::iterator> minMaxL
    = std::minmax_element(myArray.myArray.begin(), myArray.myArray.end(), [](Vector3i &vv, Vector3i &ww){ return vv.y < ww.y ; });
    std::pair<std::array<Vector3i,4>::reverse_iterator,std::array<Vector3i,4>::reverse_iterator> minMaxR
	= std::minmax_element(myArray.myArray.rend(), myArray.myArray.rbegin(), [](Vector3i &vv, Vector3i &ww){ return vv.y < ww.y ; });
    
    
    int top_left_index = minMaxL.second - myArray.myArray.begin() ;
    int down_left_index = minMaxL.first - myArray.myArray.begin() ;

    int top_right_index = minMaxR.second - myArray.myArray.rend() ;
    int down_right_index = minMaxR.first - myArray.myArray.rend() ;