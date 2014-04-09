

#include <stdexcept>
#include <string>
#include <cstdint>
#include <stack>
using std::begin;
using std::end;

class vm
{
public:
    class error : public std::runtime_error
	{
	public:
		error( std::string what ) : runtime_error{ std::move(what) } {}
	};

	using val = std::intptr_t;
	using function = val;
	using instruction = val;

	enum i : instruction
    {
		i_push = 0,
		i_call = 1,
    };
	enum f : function
    {
		f_and = 0,
		f_or  = 1,
		f_not = 2,
    };
    
    using stack_t = std::stack<val>;
	using native_function = val(stack_t &);

private:
	stack_t stack;

public:
	template<typename InstructionRange>
	void execute( const InstructionRange &bytecode )
	{
		for ( auto bg = begin(bytecode), ed = end(bytecode); bg != ed; )
		{
			switch ( *bg )
			{
			case i_push:
				push( ++bg, ed );
				break;
			case i_call:
				call( ++bg, ed );
				break;
			default:
				throw error("invalid instruction");
			}
			++bg;
		}
	}
	const stack_t &get_stack() const
	{
		return stack;
	}

private:
	template<typename InstructionIter>
	void push( const InstructionIter &bg, const InstructionIter &ed )
	{
		if ( bg == ed )
			throw error("unexpected end of code");
		stack.push( *bg );
	}
	template<typename InstructionIter>
	void call( const InstructionIter &bg, const InstructionIter &ed )
	{
		if ( bg == ed )
			throw error("unexpected end of code");
        const function f = *bg;
		switch ( f )
		{
			case f_and:
                {
    				if ( stack.size() < 2 )
    					throw error("stack undefrlow");
    				const val left = stack.top();
    				stack.pop();
    				stack.top() = left && stack.top();
                }
				return;
			case f_or:
                {
    			    if ( stack.size() < 2 )
					    throw error("stack undefrlow");
    				const val left = stack.top();
    				stack.pop();
    				stack.top() = left || stack.top();
                }
				return;
			case f_not:
				if ( stack.size() < 1 )
					throw error("stack undefrlow");
				stack.top() = !stack.top();
				return;
		}
    	stack.push( reinterpret_cast<native_function *>(f)( stack ) );
	}
};


#include <string>

using Tag = std::size_t;

template<typename Iter>
Tag FindTag( Iter bg, Iter ed ) { return std::hash<std::string>()(std::string(bg,ed)); /*TODO*/ }
template<typename CharRange>
Tag FindTag( const CharRange &str ) { return FindTag(begin(str), end(str)); }


#include <set>
struct FileInfo
{
	template<typename... String>
	explicit FileInfo( String &&... tagNames ) : tags{ FindTag(tagNames)... } {}

	bool IsTagged( Tag t ) const noexcept
	{
		return tags.find(t) != tags.end();
	}

	static vm::val Tagged( vm::stack_t &s )
	{
		if ( s.size() < 2 )
			throw vm::error("stack undefrlow");
		auto file = reinterpret_cast<const FileInfo *>( s.top() );
		s.pop();
		auto tag = static_cast<Tag>( s.top() );
		s.pop();
		return file->IsTagged( tag );
	}

private:
	std::set<Tag> tags;
};


#include <iostream>
using std::cout;
#include <vector>
int main()
{
    const FileInfo file("bananas","a giraffe");
    std::vector<vm::instruction> code =
    {
    	// ассемблерная вставка, ололо!
    	vm::i_push, static_cast<vm::val>( FindTag("bananas") ),
    	vm::i_push, reinterpret_cast<vm::val>( &file ),
    	vm::i_call, reinterpret_cast<vm::function>( &FileInfo::Tagged ),
        
        vm::i_push, static_cast<vm::val>( FindTag("a giraffe") ),
    	vm::i_push, reinterpret_cast<vm::val>( &file ),
    	vm::i_call, reinterpret_cast<vm::function>( &FileInfo::Tagged ),

        vm::i_call, vm::f_and,
    };

    try
    {
        vm machine;
        machine.execute( code );
        const vm::val result = machine.get_stack().top();
        if ( result )
            cout << "can haz bananas and a giraffe!\n";
    }
    catch ( std::exception &e )
    {
        cout << e.what() << '\n';
    }
}
