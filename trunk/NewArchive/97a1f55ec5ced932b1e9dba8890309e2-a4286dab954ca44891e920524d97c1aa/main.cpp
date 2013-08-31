#define UNIFORM_TYPECHECK_FULL(assign_type, uniform_type) \
    if(type != uniform_type) { \
		std::stringstream error_s; \
		error_s << "Error assigning " #assign_type " to uniform " << name << " of type " << type; \
		throw std::invalid_argument(error_s.str()); \
	}
#ifdef DEBUG
	#define UNIFORM_TYPECHECK(assign_type, uniform_type) UNIFORM_TYPECHECK_FULL(assign_type, uniform_type)
#else
	#define UNIFORM_TYPECHECK(assign_type, uniform_type) ;
#endif