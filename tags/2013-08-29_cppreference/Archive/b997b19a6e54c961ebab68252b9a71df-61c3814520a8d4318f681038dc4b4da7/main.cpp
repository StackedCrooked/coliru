#pragma once
#include "OpenGl.hpp"

namespace ILoveZoidberg {
    template <typename deleter_t>
	class GlId {
		public:
			operator GLuint() const {
				return glHandle;
			}
			
			GlId(deleter_t d) : glHandle(0), deleter(d) {
			}
			GlId(GLuint id, deleter_t d) : glHandle(id), deleter(d) {
			}
			GlId(GlId&& other) {
				glHandle = other.glHandle;
				other.glHandle = 0;
			}
			GlId& operator= (GlId&& other) {
				glHandle = other.glHandle;
				other.glHandle = 0;
				return *this;
			}
			GlId& operator= (GLuint id) {
				glHandle = id;
				return *this;
			}
			
			~GlId() {
				deleter(glHandle);
			}
			
			GlId(GlId const& other) = delete;
			GlId& operator=(GlId const& other) = delete;
						
		private:
			GLuint glHandle;
			deleter_t deleter;
	};
}