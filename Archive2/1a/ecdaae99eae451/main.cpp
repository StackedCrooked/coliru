    	// Compiles and works properly		
		gr_funcdecl	=	 gr_returntype	// Return type
					  >> gr_identifier	// Function name
					  >>   '('  // After this, no more backtracking
					  >>   (gr_funcargdecl % ',') // Argument list
					  >>   ')'
					  >>   gr_statement;
					  
		// Fails with inpenetrable compiler message culminating in
		// boost_1_54_0\boost\spirit\home\support\container.hpp(117): error C2039: 'value_type' : is not a member of 'avxcclast::identifier'
		gr_funcdecl	=	 gr_returntype	// Return type
					  >> gr_identifier	// Function name
					  >   '('  // After this, no more backtracking
					  >   (gr_funcargdecl % ',') // Argument list
					  >   ')'
					  >   gr_statement;
                      