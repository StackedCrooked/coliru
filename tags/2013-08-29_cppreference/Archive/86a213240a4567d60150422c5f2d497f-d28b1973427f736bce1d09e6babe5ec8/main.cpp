~/programming/projects/wide/ClangExperiments $ make
clang++ -std=c++11 -stdlib=libc++ -isystem /usr/local/include -isystem  /opt/local/libexec/llvm-3.3/include -I/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include -I.  -I./Stages -I./Stages/Codegen -I./Stages/Lexer -I./Stages/Parser -I./Stages/Semantic -I./Util -I./Util/ConcurrentDetail -I./WideLibrary ./Stages/Codegen/Expression.cpp ./Stages/Codegen/FunctionCodeGen.cpp ./Stages/Codegen/Generator.cpp ./Stages/Codegen/Statement.cpp ./Stages/Parser/Builder.cpp ./Stages/Semantic/Analyzer.cpp ./Stages/Semantic/Bool.cpp ./Stages/Semantic/ClangInclude.cpp ./Stages/Semantic/ClangNamespace.cpp ./Stages/Semantic/ClangOverloadSet.cpp ./Stages/Semantic/ClangTU.cpp ./Stages/Semantic/ClangTemplateClass.cpp ./Stages/Semantic/ClangType.cpp ./Stages/Semantic/ConstructorType.cpp ./Stages/Semantic/DeferredType.cpp ./Stages/Semantic/Function.cpp ./Stages/Semantic/FunctionType.cpp ./Stages/Semantic/IntegralType.cpp ./Stages/Semantic/LvalueType.cpp ./Stages/Semantic/Module.cpp ./Stages/Semantic/OverloadSet.cpp ./Stages/Semantic/PrimitiveType.cpp ./Stages/Semantic/RvalueType.cpp ./Stages/Semantic/StringType.cpp ./Stages/Semantic/Type.cpp ./Stages/Semantic/Util.cpp ./Stages/Semantic/Void.cpp ./Stages/Wide.cpp ./WideLibrary/main_trampoline.cpp ./main.cpp
In file included from ./Stages/Codegen/Expression.cpp:1:
./Stages/Codegen/Expression.h:55:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled_name;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Expression.cpp:1:
./Stages/Codegen/Expression.h:57:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetMangledName() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Expression.cpp:1:
./Stages/Codegen/Expression.h:84:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string value;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Expression.cpp:1:
./Stages/Codegen/Expression.h:86:42: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            StringExpression(std::string expr)
                                         ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Expression.cpp:1:
./Stages/Codegen/Expression.h:92:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetContents() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Expression.cpp:1:
./Stages/Codegen/Expression.h:98:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Expression.cpp:1:
./Stages/Codegen/Expression.h:100:45: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            NamedGlobalVariable(std::string mangledname)
                                            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Expression.cpp:2:
In file included from ./Stages/Codegen/Generator.h:7:
In file included from ./Stages/Codegen/../LLVMOptions.h:8:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Pass.h:366:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/PassSupport.h:26:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/PassRegistry.h:20:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/ADT/StringRef.h:13:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/type_traits.h:20:
/usr/local/include/llvm/Support/DataTypes.h:49:3: error: "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
# error "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
  ^
/usr/local/include/llvm/Support/DataTypes.h:53:3: error: "Must #define __STDC_CONSTANT_MACROS before " "#including Support/DataTypes.h"
# error "Must #define __STDC_CONSTANT_MACROS before " \
  ^
In file included from ./Stages/Codegen/Expression.cpp:8:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:36:32: error: template parameter redefines default argument
template <bool preserveNames = true>
                               ^
./Stages/Codegen/Statement.h:9:36: note: previous default template argument defined here
    template <bool preserveNames = true>
                                   ^
In file included from ./Stages/Codegen/Expression.cpp:8:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:350:31: error: template parameter redefines default argument
template<bool preserveNames = true, typename T = ConstantFolder,
                              ^
./Stages/Codegen/Statement.h:12:35: note: previous default template argument defined here
    template<bool preserveNames = true, typename T = ConstantFolder,
                                  ^
In file included from ./Stages/Codegen/Expression.cpp:8:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:350:50: error: template parameter redefines default argument
template<bool preserveNames = true, typename T = ConstantFolder,
                                                 ^
./Stages/Codegen/Statement.h:12:54: note: previous default template argument defined here
    template<bool preserveNames = true, typename T = ConstantFolder,
                                                     ^
In file included from ./Stages/Codegen/Expression.cpp:8:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:351:30: error: template parameter redefines default argument
         typename Inserter = IRBuilderDefaultInserter<preserveNames> >
                             ^
./Stages/Codegen/Statement.h:13:29: note: previous default template argument defined here
        typename Inserter = IRBuilderDefaultInserter<preserveNames> >
                            ^
13 errors generated.
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:3:
./Stages/Codegen/Function.h:23:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string name;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:5:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:55:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled_name;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:5:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:57:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetMangledName() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:5:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:84:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string value;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:5:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:86:42: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            StringExpression(std::string expr)
                                         ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:5:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:92:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetContents() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:5:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:98:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:5:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:100:45: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            NamedGlobalVariable(std::string mangledname)
                                            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:5:
In file included from ./Stages/Codegen/Generator.h:7:
In file included from ./Stages/Codegen/../LLVMOptions.h:8:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Pass.h:366:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/PassSupport.h:26:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/PassRegistry.h:20:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/ADT/StringRef.h:13:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/type_traits.h:20:
/usr/local/include/llvm/Support/DataTypes.h:49:3: error: "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
# error "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
  ^
/usr/local/include/llvm/Support/DataTypes.h:53:3: error: "Must #define __STDC_CONSTANT_MACROS before " "#including Support/DataTypes.h"
# error "Must #define __STDC_CONSTANT_MACROS before " \
  ^
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:13:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:36:32: error: template parameter redefines default argument
template <bool preserveNames = true>
                               ^
./Stages/Codegen/Statement.h:9:36: note: previous default template argument defined here
    template <bool preserveNames = true>
                                   ^
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:13:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:350:31: error: template parameter redefines default argument
template<bool preserveNames = true, typename T = ConstantFolder,
                              ^
./Stages/Codegen/Statement.h:12:35: note: previous default template argument defined here
    template<bool preserveNames = true, typename T = ConstantFolder,
                                  ^
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:13:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:350:50: error: template parameter redefines default argument
template<bool preserveNames = true, typename T = ConstantFolder,
                                                 ^
./Stages/Codegen/Statement.h:12:54: note: previous default template argument defined here
    template<bool preserveNames = true, typename T = ConstantFolder,
                                                     ^
In file included from ./Stages/Codegen/FunctionCodeGen.cpp:13:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:351:30: error: template parameter redefines default argument
         typename Inserter = IRBuilderDefaultInserter<preserveNames> >
                             ^
./Stages/Codegen/Statement.h:13:29: note: previous default template argument defined here
        typename Inserter = IRBuilderDefaultInserter<preserveNames> >
                            ^
14 errors generated.
In file included from ./Stages/Codegen/Generator.cpp:1:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:55:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled_name;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Generator.cpp:1:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:57:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetMangledName() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Generator.cpp:1:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:84:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string value;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Generator.cpp:1:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:86:42: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            StringExpression(std::string expr)
                                         ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Generator.cpp:1:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:92:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetContents() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Generator.cpp:1:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:98:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Generator.cpp:1:
In file included from ./Stages/Codegen/Generator.h:6:
./Stages/Codegen/Expression.h:100:45: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            NamedGlobalVariable(std::string mangledname)
                                            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Generator.cpp:1:
In file included from ./Stages/Codegen/Generator.h:7:
In file included from ./Stages/Codegen/../LLVMOptions.h:8:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Pass.h:366:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/PassSupport.h:26:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/PassRegistry.h:20:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/ADT/StringRef.h:13:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/type_traits.h:20:
/usr/local/include/llvm/Support/DataTypes.h:49:3: error: "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
# error "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
  ^
/usr/local/include/llvm/Support/DataTypes.h:53:3: error: "Must #define __STDC_CONSTANT_MACROS before " "#including Support/DataTypes.h"
# error "Must #define __STDC_CONSTANT_MACROS before " \
  ^
In file included from ./Stages/Codegen/Generator.cpp:14:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:36:32: error: template parameter redefines default argument
template <bool preserveNames = true>
                               ^
./Stages/Codegen/Statement.h:9:36: note: previous default template argument defined here
    template <bool preserveNames = true>
                                   ^
In file included from ./Stages/Codegen/Generator.cpp:14:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:350:31: error: template parameter redefines default argument
template<bool preserveNames = true, typename T = ConstantFolder,
                              ^
./Stages/Codegen/Statement.h:12:35: note: previous default template argument defined here
    template<bool preserveNames = true, typename T = ConstantFolder,
                                  ^
In file included from ./Stages/Codegen/Generator.cpp:14:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:350:50: error: template parameter redefines default argument
template<bool preserveNames = true, typename T = ConstantFolder,
                                                 ^
./Stages/Codegen/Statement.h:12:54: note: previous default template argument defined here
    template<bool preserveNames = true, typename T = ConstantFolder,
                                                     ^
In file included from ./Stages/Codegen/Generator.cpp:14:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:351:30: error: template parameter redefines default argument
         typename Inserter = IRBuilderDefaultInserter<preserveNames> >
                             ^
./Stages/Codegen/Statement.h:13:29: note: previous default template argument defined here
        typename Inserter = IRBuilderDefaultInserter<preserveNames> >
                            ^
13 errors generated.
In file included from ./Stages/Codegen/Statement.cpp:2:
./Stages/Codegen/Expression.h:55:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled_name;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Statement.cpp:2:
./Stages/Codegen/Expression.h:57:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetMangledName() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Statement.cpp:2:
./Stages/Codegen/Expression.h:84:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string value;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Statement.cpp:2:
./Stages/Codegen/Expression.h:86:42: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            StringExpression(std::string expr)
                                         ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Statement.cpp:2:
./Stages/Codegen/Expression.h:92:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetContents() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Statement.cpp:2:
./Stages/Codegen/Expression.h:98:25: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Statement.cpp:2:
./Stages/Codegen/Expression.h:100:45: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            NamedGlobalVariable(std::string mangledname)
                                            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Codegen/Statement.cpp:9:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:18:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/ADT/ArrayRef.h:13:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/ADT/SmallVector.h:19:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/MathExtras.h:17:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/SwapByteOrder.h:18:
/usr/local/include/llvm/Support/DataTypes.h:49:3: error: "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
# error "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
  ^
/usr/local/include/llvm/Support/DataTypes.h:53:3: error: "Must #define __STDC_CONSTANT_MACROS before " "#including Support/DataTypes.h"
# error "Must #define __STDC_CONSTANT_MACROS before " \
  ^
In file included from ./Stages/Codegen/Statement.cpp:9:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:36:32: error: template parameter redefines default argument
template <bool preserveNames = true>
                               ^
./Stages/Codegen/Statement.h:9:36: note: previous default template argument defined here
    template <bool preserveNames = true>
                                   ^
In file included from ./Stages/Codegen/Statement.cpp:9:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:350:31: error: template parameter redefines default argument
template<bool preserveNames = true, typename T = ConstantFolder,
                              ^
./Stages/Codegen/Statement.h:12:35: note: previous default template argument defined here
    template<bool preserveNames = true, typename T = ConstantFolder,
                                  ^
In file included from ./Stages/Codegen/Statement.cpp:9:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:350:50: error: template parameter redefines default argument
template<bool preserveNames = true, typename T = ConstantFolder,
                                                 ^
./Stages/Codegen/Statement.h:12:54: note: previous default template argument defined here
    template<bool preserveNames = true, typename T = ConstantFolder,
                                                     ^
In file included from ./Stages/Codegen/Statement.cpp:9:
/Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/IRBuilder.h:351:30: error: template parameter redefines default argument
         typename Inserter = IRBuilderDefaultInserter<preserveNames> >
                             ^
./Stages/Codegen/Statement.h:13:29: note: previous default template argument defined here
        typename Inserter = IRBuilderDefaultInserter<preserveNames> >
                            ^
13 errors generated.
In file included from ./Stages/Parser/Builder.cpp:1:
In file included from ./Stages/Parser/Builder.h:3:
In file included from ./Stages/Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:18:13: error: no template named 'iterator'; did you mean 'std::iterator'?
            iterator find(K k) {
            ^~~~~~~~
            std::iterator
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iterator:416:25: note: 'std::iterator' declared here
struct _LIBCPP_TYPE_VIS iterator
                        ^
In file included from ./Stages/Parser/Builder.cpp:1:
In file included from ./Stages/Parser/Builder.h:3:
In file included from ./Stages/Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:18:13: error: use of class template 'iterator' requires template arguments
            iterator find(K k) {
            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iterator:416:25: note: template is declared here
struct _LIBCPP_TYPE_VIS iterator
                        ^
In file included from ./Stages/Parser/Builder.cpp:1:
In file included from ./Stages/Parser/Builder.h:3:
In file included from ./Stages/Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:21:13: error: no template named 'iterator'; did you mean 'std::iterator'?
            iterator end() {
            ^~~~~~~~
            std::iterator
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iterator:416:25: note: 'std::iterator' declared here
struct _LIBCPP_TYPE_VIS iterator
                        ^
In file included from ./Stages/Parser/Builder.cpp:1:
In file included from ./Stages/Parser/Builder.h:3:
In file included from ./Stages/Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:21:13: error: use of class template 'iterator' requires template arguments
            iterator end() {
            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iterator:416:25: note: template is declared here
struct _LIBCPP_TYPE_VIS iterator
                        ^
In file included from ./Stages/Parser/Builder.cpp:1:
In file included from ./Stages/Parser/Builder.h:3:
In file included from ./Stages/Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:28:6: error: expected ';' after class
    }
     ^
     ;
In file included from ./Stages/Parser/Builder.cpp:1:
In file included from ./Stages/Parser/Builder.h:3:
In file included from ./Stages/Parser/AST.h:9:
In file included from ./Stages/Parser/../../Util/ConcurrentVector.h:10:
./Util/ConcurrentDetail/stdvector.h:7:15: error: redefinition of 'Concurrency' as different kind of symbol
    namespace Concurrency {
              ^
./Util/ConcurrentDetail/stdumap.h:7:11: note: previous definition is here
    class Concurrency {
          ^
In file included from ./Stages/Parser/Builder.cpp:1:
In file included from ./Stages/Parser/Builder.h:3:
./Stages/Parser/AST.h:90:26: error: 'UnorderedMap' is a private member of 'Wide::Concurrency'
            Concurrency::UnorderedMap<std::string, ModuleLevelDeclaration*> decls;
                         ^
./Util/ConcurrentDetail/stdumap.h:8:106: note: implicitly declared private here
        template<typename K, typename V, typename H = std::hash<K>, typename E = std::equal_to<K>> class UnorderedMap {
                                                                                                         ^
In file included from ./Stages/Parser/Builder.cpp:1:
In file included from ./Stages/Parser/Builder.h:3:
./Stages/Parser/AST.h:97:26: error: no type named 'Vector' in 'Wide::Concurrency'
            Concurrency::Vector<Function*> functions;
            ~~~~~~~~~~~~~^
./Stages/Parser/AST.h:97:32: error: expected member name or ';' after declaration specifiers
            Concurrency::Vector<Function*> functions;
            ~~~~~~~~~~~~~~~~~~~^
In file included from ./Stages/Parser/Builder.cpp:1:
In file included from ./Stages/Parser/Builder.h:6:
In file included from ./Stages/Parser/../../Util/ConcurrentQueue.h:9:
./Util/ConcurrentDetail/stdqueue.h:13:35: error: static_assert failed "Concurrent queue cannot be guaranteed to be movable or copyable."
            Queue(const Queue&) { static_assert(false, "Concurrent queue cannot be guaranteed to be movable or copyable."); }
                                  ^             ~~~~~
./Util/ConcurrentDetail/stdqueue.h:14:30: error: static_assert failed "Concurrent queue cannot be guaranteed to be movable or copyable."
            Queue(Queue&&) { static_assert(false, "Concurrent queue cannot be guaranteed to be movable or copyable."); }
                             ^             ~~~~~
In file included from ./Stages/Parser/Builder.cpp:1:
./Stages/Parser/Builder.h:11:26: error: no type named 'Queue' in 'Wide::Concurrency'
            Concurrency::Queue<Wide::Memory::Arena> arenas;
            ~~~~~~~~~~~~~^
./Stages/Parser/Builder.h:11:31: error: expected member name or ';' after declaration specifiers
            Concurrency::Queue<Wide::Memory::Arena> arenas;
            ~~~~~~~~~~~~~~~~~~^
./Stages/Parser/Builder.cpp:28:24: error: use of undeclared identifier 'arenas'
    ConcurrentUseArena(arenas, [&](Wide::Memory::Arena& arena) {
                       ^
./Stages/Parser/Builder.cpp:34:31: error: use of undeclared identifier 'arenas'
    return ConcurrentUseArena(arenas, [&](Wide::Memory::Arena& arena) {
                              ^
./Stages/Parser/Builder.cpp:40:31: error: use of undeclared identifier 'arenas'
    return ConcurrentUseArena(arenas, [&](Wide::Memory::Arena& arena) {
                              ^
./Stages/Parser/Builder.cpp:46:31: error: use of undeclared identifier 'arenas'
    return ConcurrentUseArena(arenas, [&](Wide::Memory::Arena& arena) {
                              ^
./Stages/Parser/Builder.cpp:52:31: error: use of undeclared identifier 'arenas'
    return ConcurrentUseArena(arenas, [&](Wide::Memory::Arena& arena) {
                              ^
./Stages/Parser/Builder.cpp:58:31: error: use of undeclared identifier 'arenas'
    return ConcurrentUseArena(arenas, [&](Wide::Memory::Arena& arena) {
                              ^
fatal error: too many errors emitted, stopping now [-ferror-limit=]
20 errors generated.
In file included from ./Stages/Semantic/Analyzer.cpp:1:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
1 error generated.
In file included from ./Stages/Semantic/Bool.cpp:1:
In file included from ./Stages/Semantic/Bool.h:3:
In file included from ./Stages/Semantic/PrimitiveType.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/Bool.cpp:2:
In file included from ./Stages/Semantic/ClangTU.h:9:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
2 errors generated.
In file included from ./Stages/Semantic/ClangInclude.cpp:1:
In file included from ./Stages/Semantic/ClangInclude.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/ClangInclude.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:55:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled_name;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/ClangInclude.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:57:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetMangledName() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/ClangInclude.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:84:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string value;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/ClangInclude.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:86:42: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            StringExpression(std::string expr)
                                         ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/ClangInclude.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:92:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetContents() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/ClangInclude.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:98:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/ClangInclude.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:100:45: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>
      >'
            NamedGlobalVariable(std::string mangledname)
                                            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/ClangInclude.cpp:3:
In file included from ./Stages/Semantic/../Codegen/Generator.h:7:
In file included from ./Stages/Codegen/../LLVMOptions.h:8:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Pass.h:366:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/PassSupport.h:26:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/PassRegistry.h:20:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/ADT/StringRef.h:13:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/type_traits.h:20:
/usr/local/include/llvm/Support/DataTypes.h:49:3: error: "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
# error "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
  ^
/usr/local/include/llvm/Support/DataTypes.h:53:3: error: "Must #define __STDC_CONSTANT_MACROS before " "#including Support/DataTypes.h"
# error "Must #define __STDC_CONSTANT_MACROS before " \
  ^
In file included from ./Stages/Semantic/ClangInclude.cpp:4:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^

11 errors generated.
In file included from ./Stages/Semantic/ClangNamespace.cpp:1:
In file included from ./Stages/Semantic/ClangNamespace.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/ClangNamespace.cpp:2:
In file included from ./Stages/Semantic/ClangTU.h:9:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
2 errors generated.
In file included from ./Stages/Semantic/ClangOverloadSet.cpp:1:
In file included from ./Stages/Semantic/ClangOverloadSet.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/ClangOverloadSet.cpp:1:
In file included from ./Stages/Semantic/ClangOverloadSet.h:7:
In file included from /opt/local/libexec/llvm-3.3/include/clang/Sema/Overload.h:18:
In file included from /opt/local/libexec/llvm-3.3/include/clang/AST/Decl.h:17:
In file included from /opt/local/libexec/llvm-3.3/include/clang/AST/APValue.h:17:
In file included from /opt/local/libexec/llvm-3.3/include/clang/Basic/LLVM.h:22:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/Casting.h:18:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/type_traits.h:20:
/usr/local/include/llvm/Support/DataTypes.h:49:3: error: "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
# error "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
  ^
/usr/local/include/llvm/Support/DataTypes.h:53:3: error: "Must #define __STDC_CONSTANT_MACROS before " "#including Support/DataTypes.h"
# error "Must #define __STDC_CONSTANT_MACROS before " \
  ^
In file included from ./Stages/Semantic/ClangOverloadSet.cpp:5:
In file included from ./Stages/Semantic/ClangTU.h:9:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
4 errors generated.
In file included from ./Stages/Semantic/ClangTU.cpp:1:
In file included from ./Stages/Semantic/ClangTU.h:9:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
1 error generated.
In file included from ./Stages/Semantic/ClangTemplateClass.cpp:1:
In file included from ./Stages/Semantic/ClangTemplateClass.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/ClangTemplateClass.cpp:3:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
2 errors generated.
In file included from ./Stages/Semantic/ClangType.cpp:1:
In file included from ./Stages/Semantic/ClangType.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/ClangType.cpp:1:
In file included from ./Stages/Semantic/ClangType.h:7:
In file included from /opt/local/libexec/llvm-3.3/include/clang/AST/Type.h:17:
In file included from /opt/local/libexec/llvm-3.3/include/clang/AST/NestedNameSpecifier.h:17:
In file included from /opt/local/libexec/llvm-3.3/include/clang/Basic/Diagnostic.h:18:
In file included from /opt/local/libexec/llvm-3.3/include/clang/Basic/DiagnosticIDs.h:18:
In file included from /opt/local/libexec/llvm-3.3/include/clang/Basic/LLVM.h:22:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/Casting.h:18:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/type_traits.h:20:
/usr/local/include/llvm/Support/DataTypes.h:49:3: error: "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
# error "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
  ^
/usr/local/include/llvm/Support/DataTypes.h:53:3: error: "Must #define __STDC_CONSTANT_MACROS before " "#including Support/DataTypes.h"
# error "Must #define __STDC_CONSTANT_MACROS before " \
  ^
In file included from ./Stages/Semantic/ClangType.cpp:2:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
4 errors generated.
In file included from ./Stages/Semantic/ConstructorType.cpp:1:
In file included from ./Stages/Semantic/ConstructorType.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
./Stages/Semantic/ConstructorType.cpp:9:66: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
Expression ConstructorType::AccessMember(Expression, std::string name, Analyzer& a) {
                                                                 ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
2 errors generated.
In file included from ./Stages/Semantic/Function.cpp:1:
In file included from ./Stages/Semantic/Function.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/Function.cpp:1:
In file included from ./Stages/Semantic/Function.h:4:
./Stages/Semantic/../Codegen/Expression.h:55:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled_name;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/Function.cpp:1:
In file included from ./Stages/Semantic/Function.h:4:
./Stages/Semantic/../Codegen/Expression.h:57:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetMangledName() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/Function.cpp:1:
In file included from ./Stages/Semantic/Function.h:4:
./Stages/Semantic/../Codegen/Expression.h:84:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string value;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/Function.cpp:1:
In file included from ./Stages/Semantic/Function.h:4:
./Stages/Semantic/../Codegen/Expression.h:86:42: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            StringExpression(std::string expr)
                                         ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/Function.cpp:1:
In file included from ./Stages/Semantic/Function.h:4:
./Stages/Semantic/../Codegen/Expression.h:92:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetContents() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/Function.cpp:1:
In file included from ./Stages/Semantic/Function.h:4:
./Stages/Semantic/../Codegen/Expression.h:98:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/Function.cpp:1:
In file included from ./Stages/Semantic/Function.h:4:
./Stages/Semantic/../Codegen/Expression.h:100:45: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>
      >'
            NamedGlobalVariable(std::string mangledname)
                                            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/Function.cpp:1:
In file included from ./Stages/Semantic/Function.h:13:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/DerivedTypes.h:21:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/IR/Type.h:18:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/ADT/APFloat.h:104:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/ADT/APInt.h:18:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/ADT/ArrayRef.h:13:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/ADT/SmallVector.h:19:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/MathExtras.h:17:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/SwapByteOrder.h:18:
/usr/local/include/llvm/Support/DataTypes.h:49:3: error: "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
# error "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
  ^
/usr/local/include/llvm/Support/DataTypes.h:53:3: error: "Must #define __STDC_CONSTANT_MACROS before " "#including Support/DataTypes.h"
# error "Must #define __STDC_CONSTANT_MACROS before " \
  ^
In file included from ./Stages/Semantic/Function.cpp:2:
In file included from ./Stages/Semantic/../Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:18:13: error: no template named 'iterator'; did you mean 'std::iterator'?
            iterator find(K k) {
            ^~~~~~~~
            std::iterator
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iterator:416:25: note: 'std::iterator' declared here
struct _LIBCPP_TYPE_VIS iterator
                        ^
In file included from ./Stages/Semantic/Function.cpp:2:
In file included from ./Stages/Semantic/../Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:18:13: error: use of class template 'iterator' requires template arguments
            iterator find(K k) {
            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iterator:416:25: note: template is declared here
struct _LIBCPP_TYPE_VIS iterator
                        ^
In file included from ./Stages/Semantic/Function.cpp:2:
In file included from ./Stages/Semantic/../Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:21:13: error: no template named 'iterator'; did you mean 'std::iterator'?
            iterator end() {
            ^~~~~~~~
            std::iterator
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iterator:416:25: note: 'std::iterator' declared here
struct _LIBCPP_TYPE_VIS iterator
                        ^
In file included from ./Stages/Semantic/Function.cpp:2:
In file included from ./Stages/Semantic/../Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:21:13: error: use of class template 'iterator' requires template arguments
            iterator end() {
            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iterator:416:25: note: template is declared here
struct _LIBCPP_TYPE_VIS iterator
                        ^
In file included from ./Stages/Semantic/Function.cpp:2:
In file included from ./Stages/Semantic/../Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:28:6: error: expected ';' after class
    }
     ^
     ;
In file included from ./Stages/Semantic/Function.cpp:2:
In file included from ./Stages/Semantic/../Parser/AST.h:9:
In file included from ./Stages/Parser/../../Util/ConcurrentVector.h:10:
./Util/ConcurrentDetail/stdvector.h:7:15: error: redefinition of 'Concurrency' as different kind of symbol
    namespace Concurrency {
              ^
./Util/ConcurrentDetail/stdumap.h:7:11: note: previous definition is here
    class Concurrency {
          ^
In file included from ./Stages/Semantic/Function.cpp:2:
./Stages/Semantic/../Parser/AST.h:90:26: error: 'UnorderedMap' is a private member of 'Wide::Concurrency'
            Concurrency::UnorderedMap<std::string, ModuleLevelDeclaration*> decls;
                         ^
./Util/ConcurrentDetail/stdumap.h:8:106: note: implicitly declared private here
        template<typename K, typename V, typename H = std::hash<K>, typename E = std::equal_to<K>> class UnorderedMap {
                                                                                                         ^
In file included from ./Stages/Semantic/Function.cpp:2:
./Stages/Semantic/../Parser/AST.h:97:26: error: no type named 'Vector' in 'Wide::Concurrency'
            Concurrency::Vector<Function*> functions;
            ~~~~~~~~~~~~~^
./Stages/Semantic/../Parser/AST.h:97:32: error: expected member name or ';' after declaration specifiers
            Concurrency::Vector<Function*> functions;
            ~~~~~~~~~~~~~~~~~~~^
In file included from ./Stages/Semantic/Function.cpp:4:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
20 errors generated.
In file included from ./Stages/Semantic/FunctionType.cpp:1:
In file included from ./Stages/Semantic/FunctionType.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/FunctionType.cpp:2:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
2 errors generated.
In file included from ./Stages/Semantic/IntegralType.cpp:1:
In file included from ./Stages/Semantic/IntegralType.h:1:
In file included from ./Stages/Semantic/PrimitiveType.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/IntegralType.cpp:2:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
^[[3~2 errors generated.
In file included from ./Stages/Semantic/LvalueType.cpp:1:
In file included from ./Stages/Semantic/LvalueType.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/LvalueType.cpp:1:
./Stages/Semantic/LvalueType.h:21:65: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            Expression AccessMember(Expression val, std::string name, Analyzer& a) {
                                                                ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/LvalueType.cpp:2:
In file included from ./Stages/Semantic/ClangTU.h:9:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
3 errors generated.
In file included from ./Stages/Semantic/Module.cpp:1:
In file included from ./Stages/Semantic/Module.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/Module.cpp:2:
In file included from ./Stages/Semantic/../Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:18:13: error: no template named 'iterator'; did you mean 'std::iterator'?
            iterator find(K k) {
            ^~~~~~~~
            std::iterator
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iterator:416:25: note: 'std::iterator' declared here
struct _LIBCPP_TYPE_VIS iterator
                        ^
In file included from ./Stages/Semantic/Module.cpp:2:
In file included from ./Stages/Semantic/../Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:18:13: error: use of class template 'iterator' requires template arguments
            iterator find(K k) {
            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iterator:416:25: note: template is declared here
struct _LIBCPP_TYPE_VIS iterator
                        ^
In file included from ./Stages/Semantic/Module.cpp:2:
In file included from ./Stages/Semantic/../Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:21:13: error: no template named 'iterator'; did you mean 'std::iterator'?
            iterator end() {
            ^~~~~~~~
            std::iterator
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iterator:416:25: note: 'std::iterator' declared here
struct _LIBCPP_TYPE_VIS iterator
                        ^
In file included from ./Stages/Semantic/Module.cpp:2:
In file included from ./Stages/Semantic/../Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:21:13: error: use of class template 'iterator' requires template arguments
            iterator end() {
            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iterator:416:25: note: template is declared here
struct _LIBCPP_TYPE_VIS iterator
                        ^
In file included from ./Stages/Semantic/Module.cpp:2:
In file included from ./Stages/Semantic/../Parser/AST.h:8:
In file included from ./Stages/Parser/../../Util/ConcurrentUnorderedMap.h:12:
./Util/ConcurrentDetail/stdumap.h:28:6: error: expected ';' after class
    }
     ^
     ;
In file included from ./Stages/Semantic/Module.cpp:2:
In file included from ./Stages/Semantic/../Parser/AST.h:9:
In file included from ./Stages/Parser/../../Util/ConcurrentVector.h:10:
./Util/ConcurrentDetail/stdvector.h:7:15: error: redefinition of 'Concurrency' as different kind of symbol
    namespace Concurrency {
              ^
./Util/ConcurrentDetail/stdumap.h:7:11: note: previous definition is here
    class Concurrency {
          ^
In file included from ./Stages/Semantic/Module.cpp:2:
./Stages/Semantic/../Parser/AST.h:90:26: error: 'UnorderedMap' is a private member of 'Wide::Concurrency'
            Concurrency::UnorderedMap<std::string, ModuleLevelDeclaration*> decls;
                         ^
./Util/ConcurrentDetail/stdumap.h:8:106: note: implicitly declared private here
        template<typename K, typename V, typename H = std::hash<K>, typename E = std::equal_to<K>> class UnorderedMap {
                                                                                                         ^
In file included from ./Stages/Semantic/Module.cpp:2:
./Stages/Semantic/../Parser/AST.h:97:26: error: no type named 'Vector' in 'Wide::Concurrency'
            Concurrency::Vector<Function*> functions;
            ~~~~~~~~~~~~~^
./Stages/Semantic/../Parser/AST.h:97:32: error: expected member name or ';' after declaration specifiers
            Concurrency::Vector<Function*> functions;
            ~~~~~~~~~~~~~~~~~~~^
In file included from ./Stages/Semantic/Module.cpp:3:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
11 errors generated.
In file included from ./Stages/Semantic/OverloadSet.cpp:1:
In file included from ./Stages/Semantic/OverloadSet.h:3:
In file included from ./Stages/Semantic/PrimitiveType.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/OverloadSet.cpp:2:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
2 errors generated.
In file included from ./Stages/Semantic/PrimitiveType.cpp:1:
In file included from ./Stages/Semantic/PrimitiveType.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/PrimitiveType.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:55:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled_name;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/PrimitiveType.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:57:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetMangledName() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/PrimitiveType.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:84:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string value;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/PrimitiveType.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:86:42: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            StringExpression(std::string expr)
                                         ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/PrimitiveType.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:92:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string GetContents() {
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/PrimitiveType.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:98:25: error: implicit instantiation of undefined template
      'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            std::string mangled;
                        ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/PrimitiveType.cpp:2:
./Stages/Semantic/../Codegen/Expression.h:100:45: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>
      >'
            NamedGlobalVariable(std::string mangledname)
                                            ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/PrimitiveType.cpp:3:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
9 errors generated.
In file included from ./Stages/Semantic/RvalueType.cpp:1:
In file included from ./Stages/Semantic/RvalueType.h:1:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/RvalueType.cpp:2:
In file included from ./Stages/Semantic/ClangTU.h:9:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
2 errors generated.
In file included from ./Stages/Semantic/StringType.cpp:1:
In file included from ./Stages/Semantic/StringType.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/StringType.cpp:2:
In file included from ./Stages/Semantic/ClangTU.h:9:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
2 errors generated.
In file included from ./Stages/Semantic/Type.cpp:1:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/Type.cpp:2:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
2 errors generated.
./Stages/Semantic/Util.cpp:9:10: fatal error: 'CodeGen/CodeGenModule.h' file not found
#include <CodeGen/CodeGenModule.h>
         ^
1 error generated.
In file included from ./Stages/Semantic/Void.cpp:1:
In file included from ./Stages/Semantic/Void.h:3:
./Stages/Semantic/Type.h:72:69: error: implicit instantiation of undefined template 'std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >'
            virtual Expression AccessMember(Expression, std::string name, Analyzer& a) {
                                                                    ^
/opt/local/libexec/llvm-3.3/bin/../lib/c++/v1/iosfwd:188:28: note: template is declared here
    class _LIBCPP_TYPE_VIS basic_string;
                           ^
In file included from ./Stages/Semantic/Void.cpp:2:
In file included from ./Stages/Semantic/ClangTU.h:9:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
2 errors generated.
In file included from ./Stages/Wide.cpp:1:
In file included from ./Stages/Wide.h:1:
In file included from ./Stages/ClangOptions.h:13:
In file included from /opt/local/libexec/llvm-3.3/include/clang/Basic/DiagnosticIDs.h:18:
In file included from /opt/local/libexec/llvm-3.3/include/clang/Basic/LLVM.h:22:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/Casting.h:18:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/type_traits.h:20:
/usr/local/include/llvm/Support/DataTypes.h:49:3: error: "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
# error "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
  ^
/usr/local/include/llvm/Support/DataTypes.h:53:3: error: "Must #define __STDC_CONSTANT_MACROS before " "#including Support/DataTypes.h"
# error "Must #define __STDC_CONSTANT_MACROS before " \
  ^
In file included from ./Stages/Wide.cpp:2:
./Stages/Semantic/Analyzer.h:5:10: fatal error: '../../Util\MemoryArena.h' file not found
#include "../../Util\MemoryArena.h"
         ^
3 errors generated.
In file included from ./main.cpp:3:
In file included from ./Stages/Wide.h:1:
In file included from ./Stages/ClangOptions.h:13:
In file included from /opt/local/libexec/llvm-3.3/include/clang/Basic/DiagnosticIDs.h:18:
In file included from /opt/local/libexec/llvm-3.3/include/clang/Basic/LLVM.h:22:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/Casting.h:18:
In file included from /Users/francis/Development/programming/projects/stacked-crooked/Clang/llvm/include/llvm/Support/type_traits.h:20:
/usr/local/include/llvm/Support/DataTypes.h:49:3: error: "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
# error "Must #define __STDC_LIMIT_MACROS before #including Support/DataTypes.h"
  ^
/usr/local/include/llvm/Support/DataTypes.h:53:3: error: "Must #define __STDC_CONSTANT_MACROS before " "#including Support/DataTypes.h"
# error "Must #define __STDC_CONSTANT_MACROS before " \
  ^
2 errors generated.
make: *** [all] Error 1
~/programming/projects/wide/ClangExperiments $ 
~/programming/projects/wide/ClangExperiments $ 
