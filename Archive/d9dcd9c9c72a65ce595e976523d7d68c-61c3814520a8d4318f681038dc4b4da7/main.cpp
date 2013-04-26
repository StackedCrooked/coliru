#pragma once
#include "OpenGl.hpp"
#include <iostream>

namespace Jellyot {
    template <typename deleter_t>
	class GlIds {
		public:
			operator GLuint() const {
				return glHandle;
			}
			GlIds(deleter_t d) : glHandle(0), deleter(d) {
			}
			GlIds(GLuint id, deleter_t d) : glHandle(id), deleter(d) {
			}
			GlIds(GlIds&& other) {
				deleter = other.deleter;
				glHandle = other.glHandle;
				other.glHandle = 0;
			}
			GlIds& operator= (GlIds&& other) {
				deleter = other.deleter;
				glHandle = other.glHandle;
				other.glHandle = 0;
				return *this;
			}
			GlIds& operator= (GLuint id) {
				glHandle = id;
				return *this;
			}
			~GlIds() {
				deleter(1, &glHandle);
			}
			GlIds(GlIds const& other) = delete;
			GlIds& operator=(GlIds const& other) = delete;
			GLuint& operator&() {
				return glHandle;
			}
						
		public:
			GLuint glHandle;
			deleter_t deleter;
	};
}