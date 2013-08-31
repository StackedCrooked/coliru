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
    private:
		Vendor vendor;
    	CommandArguments compilerargs;
		clang::LangOptions langopts;
		llvm::IntrusiveRefCntPtr<clang::PreprocessorOptions> llvmpreprocessoroptions;
		clang::LangOptions languageoptions;
		llvm::IntrusiveRefCntPtr<clang::DiagnosticIDs> diagnosticids;
		llvm::IntrusiveRefCntPtr<clang::DiagnosticOptions> llvmdiagnosticsoptions;
		llvm::IntrusiveRefCntPtr<clang::HeaderSearchOptions> llvmheadersearchoptions;
		clang::FrontendOptions frontendoptions;
		clang::TargetOptions targetoptions;
		clang::FileSystemOptions filesystemoptions;
		
		std::string errors;
		llvm::raw_string_ostream errorstream;

		std::vector<clang::Decl*> declarations;
	public:
    
        Compiler( int argc, const char* const argv[], Vendor vend ) 
        : vendor( vend ), compilerargs( argc, argv ), errorstream( errors ), llvmpreprocessoroptions( new clang::PreprocessorOptions() ) {
    		languageoptions.WChar = true;
    		languageoptions.CPlusPlus = true;
    		languageoptions.CPlusPlus11 = true;
    		languageoptions.Bool = true;
    		languageoptions.GNUKeywords = true;
    		languageoptions.Exceptions = true;
    		languageoptions.CXXExceptions = true;
    
    		targetoptions.Triple = llvm::sys::getDefaultTargetTriple( );
    		if ( vendor == Vendor::MSVC ) {
    			targetoptions.CXXABI = "microsoft";
    		}
    		else {
    			targetoptions.CXXABI = "itanium";
    		}
    	}
    
    
    	bool Parse( Furrovine::String filename ) {
    		class ASTDeclConsumer : public clang::ASTConsumer {
    	public:
			ASTDeclConsumer( std::vector<clang::Decl*>& arg )
				: vec( arg ) {}
			std::vector<clang::Decl*>& vec;
			bool HandleTopLevelDecl( clang::DeclGroupRef arg ) {
				for ( auto && x : arg ) {
					vec.push_back( x );
				}
				return true;
			}
		};

		ASTDeclConsumer astconsumer( declarations );

		llvm::StringRef llvmfilename( reinterpret_cast<char*>( filename.data( ) ) );
		
		clang::CompilerInstance ci;
		clang::DiagnosticsEngine diagnosticsengine( diagnosticids, llvmdiagnosticsoptions.getPtr(), new clang::TextDiagnosticPrinter( errorstream, llvmdiagnosticsoptions.getPtr(), false ), true );
		clang::FileManager filemanager( filesystemoptions );
		clang::SourceManager sourcemanager( diagnosticsengine, filemanager );
		std::unique_ptr<clang::TargetInfo> targetinfo( clang::TargetInfo::CreateTargetInfo( diagnosticsengine, &targetoptions ) );
		targetinfo->setCXXABI( vendor == Vendor::MSVC ? clang::TargetCXXABI::Microsoft : clang::TargetCXXABI::GenericItanium );
		clang::HeaderSearchOptions& headersearchoptions = *llvmheadersearchoptions;
		clang::HeaderSearch hs( llvmheadersearchoptions, filemanager, diagnosticsengine, languageoptions, targetinfo.get( ) );
		clang::PreprocessorOptions& preprocessoroptions = *llvmpreprocessoroptions;
		clang::Preprocessor preprocessor( llvmpreprocessoroptions, diagnosticsengine, languageoptions, targetinfo.get( ), sourcemanager, hs, ci );
		clang::InitializePreprocessor( preprocessor, preprocessoroptions, headersearchoptions, frontendoptions );
		preprocessor.getBuiltinInfo( ).InitializeBuiltins( preprocessor.getIdentifierTable( ), languageoptions );
		clang::ASTContext astcontext( languageoptions, sourcemanager, targetinfo.get( ), preprocessor.getIdentifierTable( ), preprocessor.getSelectorTable( ), preprocessor.getBuiltinInfo( ), 1024 );
		clang::Sema sema( preprocessor, astcontext, astconsumer, clang::TU_Complete, null );

		const clang::DirectoryLookup* directlookup = nullptr;
		auto entry = hs.LookupFile( llvmfilename, true, nullptr, directlookup, nullptr, nullptr, nullptr, nullptr );
		if ( !entry )
			entry = filemanager.getFile( llvmfilename );
		if ( !entry )
			throw Furrovine::TException<std::exception>( "Could not find file " + filename );

		auto fileid = sourcemanager.createFileID( entry, clang::SourceLocation( ), clang::SrcMgr::CharacteristicKind::C_User );
		if ( fileid.isInvalid( ) )
			throw Furrovine::TException<std::exception>( "Error translating file " + filename );
		
		sourcemanager.setMainFileID( fileid );
		diagnosticsengine.getClient( )->BeginSourceFile( languageoptions, &preprocessor );
		clang::ParseAST( sema );
		diagnosticsengine.getClient( )->EndSourceFile( );

		return diagnosticsengine.getClient( )->getNumErrors() == 0;
    	}
    };
}