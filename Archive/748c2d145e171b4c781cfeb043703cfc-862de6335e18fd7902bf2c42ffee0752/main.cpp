template <typename T>
    struct tvec3
	{	
		enum ctor{null};

		typedef T value_type;
		typedef std::size_t size_type;
		typedef tvec3<T> type;
		typedef tvec3<bool> bool_type;

		GLM_FUNC_DECL GLM_CONSTEXPR size_type length() const;

		//////////////////////////////////////
		// Data

#	if(GLM_COMPONENT == GLM_COMPONENT_CXX11)
		union 
		{
#		if(defined(GLM_SWIZZLE))
			_GLM_SWIZZLE3_2_MEMBERS(value_type, glm::detail::tvec2<value_type>, x, y, z)
			_GLM_SWIZZLE3_2_MEMBERS(value_type, glm::detail::tvec2<value_type>, r, g, b)
			_GLM_SWIZZLE3_2_MEMBERS(value_type, glm::detail::tvec2<value_type>, s, t, p)
			_GLM_SWIZZLE3_3_MEMBERS(value_type, glm::detail::tvec3<value_type>, x, y, z)
			_GLM_SWIZZLE3_3_MEMBERS(value_type, glm::detail::tvec3<value_type>, r, g, b)
			_GLM_SWIZZLE3_3_MEMBERS(value_type, glm::detail::tvec3<value_type>, s, t, p)
			_GLM_SWIZZLE3_4_MEMBERS(value_type, glm::detail::tvec4<value_type>, x, y, z)
			_GLM_SWIZZLE3_4_MEMBERS(value_type, glm::detail::tvec4<value_type>, r, g, b)
			_GLM_SWIZZLE3_4_MEMBERS(value_type, glm::detail::tvec4<value_type>, s, t, p)
#		endif//(defined(GLM_SWIZZLE))

			struct{value_type r, g, b;};
			struct{value_type s, t, p;};
			struct{value_type x, y, z;};
		};
#	elif(GLM_COMPONENT == GLM_COMPONENT_CXX98)
		union {value_type x, r, s;};
		union {value_type y, g, t;};
		union {value_type z, b, p;};

#		if(defined(GLM_SWIZZLE))
			// Defines all he swizzle operator as functions
			GLM_SWIZZLE_GEN_REF_FROM_VEC3(T, detail::tvec3, detail::tref2, detail::tref3)
			GLM_SWIZZLE_GEN_VEC_FROM_VEC3(T, detail::tvec3, detail::tvec2, detail::tvec3, detail::tvec4)
#		endif//(defined(GLM_SWIZZLE))
#	else //(GLM_COMPONENT == GLM_COMPONENT_ONLY_XYZW)
		value_type x, y, z;

#		if(defined(GLM_SWIZZLE))
			// Defines all he swizzle operator as functions
			GLM_SWIZZLE_GEN_REF_FROM_VEC3_COMP(T, detail::tvec3, detail::tref2, detail::tref3, x, y, z)
			GLM_SWIZZLE_GEN_VEC_FROM_VEC3_COMP(T, detail::tvec3, detail::tvec2, detail::tvec3, detail::tvec4, x, y, z)
#		endif//(defined(GLM_SWIZZLE))
#	endif//GLM_COMPONENT