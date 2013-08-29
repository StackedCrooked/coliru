#pragma once

#pragma warning( push, 0 )
#include "llvm/Support/Host.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Basic/FileManager.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"       
#include "clang/Frontend/LangStandard.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/HeaderSearch.h"
#include "clang/Parse/ParseAST.h"
#include "clang/Sema/Sema.h"
#pragma warning( pop )

namespace Furroflect {

    class Compiler {
    public:
		Compiler( int argc, const char* const argv[], Vendor vendor );

		bool Parse( Furrovine::String filename );

	private:
		Vendor vendor;
		CommandArguments compilerargs;
		clang::CompilerInstance compilerinstance;
		clang::DiagnosticOptions diagnosticoptions;
		clang::TargetOptions targetoptions;
		llvm::OwningPtr<clang::CompilerInvocation> compilerinvocation;
	};

    namespace detail {
		// Empty consumer that gets called during parsing of the AST.
		// We don't get the AST mid-parsing because we need full post-parse
		// typing information, which can only be gotten after the entire TU
		// has been parsed and we then iterate over the TU_Decl's afterwards
		struct EmptyASTConsumer : public clang::ASTConsumer {
			virtual ~EmptyASTConsumer() { }
			virtual bool HandleTopLevelDecl(clang::DeclGroupRef) { return true; }
		};
	}

	Compiler::Compiler( int argc, const char* const argv[], Vendor vend ) : vendor( vend ), compilerargs( argc, argv ) {
		if ( vendor == Vendor::MSVC ) {
			diagnosticoptions.setFormat( diagnosticoptions.Msvc );
		}
		else {
			diagnosticoptions.setFormat( diagnosticoptions.Clang );
		}
		compilerinstance.createDiagnostics( new clang::TextDiagnosticPrinter( llvm::outs( ), &diagnosticoptions ), true );
		//compilerinstance.getDiagnostics( ).setSuppressSystemWarnings( true );
		
		compilerinvocation.reset( new clang::CompilerInvocation( ) );
		clang::CompilerInvocation::CreateFromArgs( *compilerinvocation, argv + 1, argv + argc, compilerinstance.getDiagnostics( ) );
		compilerinstance.setInvocation( compilerinvocation.get() );

		// Setup the language parsing options for C++
		clang::LangOptions& languageoptions = *compilerinvocation->getLangOpts( );
		clang::CompilerInvocation::setLangDefaults( languageoptions,
			clang::IK_CXX, vendor == Vendor::GCC ? clang::LangStandard::lang_gnucxx0x : clang::LangStandard::lang_cxx0x );
		languageoptions.WChar = true;
		languageoptions.CPlusPlus = true;
		languageoptions.CPlusPlus11 = true;
		languageoptions.Bool = true;
		languageoptions.GNUKeywords = true;
		languageoptions.Exceptions = true;
		languageoptions.CXXExceptions = true;
		//languageoptions.CPlusPlus = 1;
		//languageoptions.Bool = 1;
		//languageoptions.RTTI = 1;
		//languageoptions.CXXExceptions = 1;
		if ( vendor == Vendor::MSVC ) {
			//languageoptions.MicrosoftExt = 1;
			///languageoptions.MicrosoftMode = 1;
			//languageoptions.MSBitfields = 1;
			//languageoptions.DelayedTemplateParsing = 1;
		}
		else if ( vendor == Vendor::GCC ) {
			//languageoptions.GNUMode = 1;
		}
		
		targetoptions.Triple = llvm::sys::getDefaultTargetTriple( );
		/*if ( vendor == Vendor::MSVC ) {
			targetoptions.CXXABI = "microsoft";
		}
		else {
			targetoptions.CXXABI = "itanium";
		}*/
		compilerinstance.setTarget( clang::TargetInfo::CreateTargetInfo( 
			compilerinstance.getDiagnostics( ),
			&targetoptions 
		) );
		
		// Create the file manager
		compilerinstance.createFileManager( );
		compilerinstance.createSourceManager( compilerinstance.getFileManager( ) );
	
		// Gather C++ header searches from the command-line
		// ( Unnecessary due to compiler invocation taking args from command line now ? )
		clang::HeaderSearchOptions& headersearchoptions = compilerinstance.getHeaderSearchOpts( );
		for ( Furrovine::ulword i = 0;; i++ ) {
			Furrovine::String include = compilerargs.After( "-i", i );
			if ( include.IsEmpty( ) )
			break;
			llvm::StringRef llvminclude = (char*)include.data( );
			headersearchoptions.AddPath( llvminclude, clang::frontend::Angled, false, false );
		}
		for ( Furrovine::ulword i = 0;; i++ ) {
			Furrovine::String include = compilerargs.After( "-isystem", i );
			llvm::StringRef llvminclude = (char*)include.data( );
			if ( include == "" )
				break;
			headersearchoptions.AddPath( llvminclude, clang::frontend::System, false, false );
		}
	}


	bool Compiler::Parse( Furrovine::String filename ) {
		// Recreate preprocessor 
		compilerinstance.createPreprocessor();
		compilerinstance.getPreprocessorOpts( ).UsePredefines = false;
	
		// Prepare the AST
		compilerinstance.createASTContext( );
		
		// Parse the AST
		llvm::StringRef llvmfilename = (char*)filename.data( );
		const clang::FileEntry* file = compilerinstance.getFileManager( ).getFile( llvmfilename );
		
		compilerinstance.getSourceManager( ).createMainFileID( file );
		compilerinstance.getDiagnosticClient( ).BeginSourceFile(
			compilerinstance.getLangOpts( ),
			&compilerinstance.getPreprocessor( ) );
		
		// Create and use AST
		detail::EmptyASTConsumer emptyastconsumer;
		// KerBOOM
		clang::ParseAST( compilerinstance.getPreprocessor( ),
			&emptyastconsumer, 
			compilerinstance.getASTContext( ) );
		
		compilerinstance.getDiagnosticClient( ).EndSourceFile( );

		// States
		compilerinstance.getASTContext( ).Idents.PrintStats( );

		return compilerinstance.getDiagnosticClient().getNumErrors() == 0;
	}

}