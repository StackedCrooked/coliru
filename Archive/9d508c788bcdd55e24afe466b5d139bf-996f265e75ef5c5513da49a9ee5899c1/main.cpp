#pragma once

namespace lua {

template<typename State>
class ref {
    State &state_;

public:
	/* Constructs a new reference to the element at the given index.
	 * This create a strong reference, thus preventing collection
	 * of the object. This does not alter the stack's state.
	 */
	ref(State &state, int index) 
	 : state_(state) {
		lua_pushlightuserdata(state_, this);
		lua_pushvalue(state_, index);
		lua_rawset(state_, LUA_REGISTRYINDEX);
	}

	/* Copies a reference. Similar to shared_ptr, this will increment
	 * the reference count, requiring both copies to be destroyed for the
	 * referenced object to be collectable.
	 */
	ref(ref const &other) 
	 : state_(other.state_) {
		lua_pushlightuserdata(state_, this);
		other.push();
		lua_rawset(state_, LUA_REGISTRYINDEX);
	}

	/* Assigns a reference. This will decrease the refcount of the current 
	 * object and increase these of the assigned object.
	 */
	ref &operator=(ref const &other) {
		if(state_ != other.state_)
			{} // throw, or destroy + construct

		lua_pushlightuserdata(state_, this);
		other.push();
		lua_rawset(state_, LUA_REGISTRYINDEX);
	}

    /* Destroys the reference to the object. This may destroy a link
     * in such a way that the object will be collected.
     */
	~ref() {
		lua_pushlightuserdata(state_, this);
		lua_pushnil(state_);
		lua_rawset(state_, LUA_REGISTRYINDEX);
	}

	int push() {
		lua_pushlightuserdata(state_, this);
		lua_rawget(state_, LUA_REGISTRYINDEX);
		return lua_absindex(state_, -1);
	}

	lua_State *state() {
		return state_;
	}
};

template<typename Table>
class table_proxy {
	Table &table_;
	variant key_;

public:
	table_proxy(Table &table, variant key)
	 : table_(table)
	 , key_(key) {}

	operator variant() {
		return table_.get(key_);
	}

	variant &operator=(variant const& val) {
		table_.set(key_, val);
		return val;
	}
};

class table {
	ref ref_;

public:
	typedef table_proxy<table> proxy;

	table(ref const &ref) 
	 : ref_(ref) {}
	
	proxy operator[](variant const &key) {
		return proxy(*this, key);
	}

	void set(variant const &key, variant const &value) {
		int table_idx = ref_.push();
		key.push();
		value.push();
		lua_settable(ref.state(), table_idx);
		lua_pop(ref.state());
	}

	variant get(variant const &key) {
		int table_idx = ref_.push();
		key.push();
		lua_gettable(ref.state(), hnd);
		variant value = state.pop();
		lua_pop(ref.state());
		return value;
	}
};

}
