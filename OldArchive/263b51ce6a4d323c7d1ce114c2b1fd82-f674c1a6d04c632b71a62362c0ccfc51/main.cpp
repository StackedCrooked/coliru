#pragma once
#include "OpenGl.hpp"
#include <iostream>

namespace Jellyot {
    template <typename deleter_t>
	class GlWrapper {
		protected:
			GLuint glHandle;
		private:
			deleter_t deleter;
			
			template<typename Deleter>
			static auto call_deleter(Deleter& deleter, GLuint* handle) -> decltype(deleter(*handle)) {
				return deleter(*handle);
			}

			template<typename Deleter>
			static auto call_deleter(Deleter& deleter, GLuint* handle) -> decltype(deleter(1, handle)) {
				return deleter(1, handle);
			}
			
		public:
			explicit operator GLuint() const {
				return glHandle;
			}
			GlWrapper(deleter_t d) : glHandle(0), deleter(d) {
			}
			GlWrapper(deleter_t d, GLuint id) : glHandle(id), deleter(d) {
			}
			GlWrapper(GlWrapper&& other) { // Move ctor into this
				deleter = other.deleter;
				glHandle = other.glHandle;
				other.glHandle = 0;
			}
			GlWrapper& operator= (GlWrapper&& other) { // Move into this
				deleter = other.deleter;
				glHandle = other.glHandle;
				other.glHandle = 0;
				return *this;
			}			
			GlWrapper& operator= (GLuint id) {
				glHandle = id;
				return *this;
			}
			virtual ~GlWrapper() {
				call_deleter(deleter, &glHandle);
			}
			GlWrapper(GlWrapper const& other) = delete;
			GlWrapper& operator=(GlWrapper const& other) = delete;
			GLuint* operator&() {
				return &glHandle;
			}
			GLuint& operator*() {
				return glHandle;
			}
	};
}