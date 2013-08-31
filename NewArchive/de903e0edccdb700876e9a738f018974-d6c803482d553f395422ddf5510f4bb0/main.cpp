#pragma once

#define _SCL_SECURE_NO_WARNINGS

#include <string>
#include <vector>

#pragma warning( push, 0 )
#include "llvm/Support/Host.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Basic/FileManager.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"       
#include "clang/Frontend/LangStandard.h"
#include <clang/Frontend/Utils.h>
#include "clang/Lex/Preprocessor.h"
#include <clang/Frontend/FrontendOptions.h>
#include <clang/Basic/TargetOptions.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Lex/HeaderSearchOptions.h>
#include <clang/Frontend/CompilerInstance.h>
#include "clang/Lex/HeaderSearch.h"
#include "clang/Parse/ParseAST.h"
#include "clang/Sema/Sema.h"
#pragma warning( pop )

namespace Furroflect {
    class Compiler {
    private:
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
    
        Compiler( int argc, const char* const argv[] ) 
        : errorstream( errors ), 
        llvmdiagnosticsoptions( new clang::DiagnosticOptions() ),
    	llvmpreprocessoroptions( new clang::PreprocessorOptions() ),
    	llvmheadersearchoptions( new clang::HeaderSearchOptions() ) {
    		languageoptions.WChar = true;
    		languageoptions.CPlusPlus = true;
    		languageoptions.CPlusPlus11 = true;
    		languageoptions.Bool = true;
    		languageoptions.GNUKeywords = true;
    		languageoptions.Exceptions = true;
    		languageoptions.CXXExceptions = true;
    
    		targetoptions.Triple = llvm::sys::getDefaultTargetTriple( );
    	}
    
    
    	bool Parse( std::string filename ) {
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

		llvm::StringRef llvmfilename( reinterpret_cast<const char*>( filename.data( ) ) );
		
		clang::CompilerInstance ci;
		clang::DiagnosticsEngine diagnosticsengine( diagnosticids, llvmdiagnosticsoptions.getPtr(), new clang::TextDiagnosticPrinter( errorstream, llvmdiagnosticsoptions.getPtr(), false ), true );
		clang::FileManager filemanager( filesystemoptions );
		clang::SourceManager sourcemanager( diagnosticsengine, filemanager );
		clang::TargetInfo* targetinfo = clang::TargetInfo::CreateTargetInfo( diagnosticsengine, &targetoptions );
		targetinfo->setCXXABI( clang::TargetCXXABI::Microsoft );
		clang::HeaderSearchOptions& headersearchoptions = *llvmheadersearchoptions;
		clang::HeaderSearch hs( llvmheadersearchoptions, filemanager, diagnosticsengine, languageoptions, targetinfo );
		clang::PreprocessorOptions& preprocessoroptions = *llvmpreprocessoroptions;
		clang::Preprocessor preprocessor( llvmpreprocessoroptions, diagnosticsengine, languageoptions, targetinfo, sourcemanager, hs, ci );
		clang::InitializePreprocessor( preprocessor, preprocessoroptions, headersearchoptions, frontendoptions );
		preprocessor.getBuiltinInfo( ).InitializeBuiltins( preprocessor.getIdentifierTable( ), languageoptions );
		clang::ASTContext astcontext( languageoptions, sourcemanager, targetinfo, preprocessor.getIdentifierTable( ), preprocessor.getSelectorTable( ), preprocessor.getBuiltinInfo( ), 1024 );
		clang::Sema sema( preprocessor, astcontext, astconsumer, clang::TU_Complete, nullptr );

		const clang::DirectoryLookup* directlookup = nullptr;
		auto entry = hs.LookupFile( llvmfilename, true, nullptr, directlookup, nullptr, nullptr, nullptr, nullptr );
		if ( !entry )
			entry = filemanager.getFile( llvmfilename );
		if ( !entry )
			throw std::runtime_error( "Could not find file " + filename );

		auto fileid = sourcemanager.createFileID( entry, clang::SourceLocation( ), clang::SrcMgr::CharacteristicKind::C_User );
		if ( fileid.isInvalid( ) )
			throw std::runtime_error( "Error translating file " + filename );
		
		sourcemanager.setMainFileID( fileid );
		diagnosticsengine.getClient( )->BeginSourceFile( languageoptions, &preprocessor );
		clang::ParseAST( sema );
		diagnosticsengine.getClient( )->EndSourceFile( );

		return diagnosticsengine.getClient( )->getNumErrors() == 0;
    	}
    };
}

int main(int argc, char** argv) {
	Furroflect::Compiler c(argc, argv);
	c.Parse("main.cpp");
}


#pragma comment( lib, "clangAnalysis.lib" )
#pragma comment( lib, "clangARCMigrate.lib" )
#pragma comment( lib, "clangAST.lib" )
#pragma comment( lib, "clangASTMatchers.lib" )
#pragma comment( lib, "clangBasic.lib" )
#pragma comment( lib, "clangCodeGen.lib" )
#pragma comment( lib, "clangDriver.lib" )
//#pragma comment( lib, "clangDynamicASTMatchers.lib" )
#pragma comment( lib, "clangEdit.lib" )
#pragma comment( lib, "clangFormat.lib" )
#pragma comment( lib, "clangFrontend.lib" )
#pragma comment( lib, "clangFrontendTool.lib" )
#pragma comment( lib, "clangLex.lib" )
#pragma comment( lib, "clangParse.lib" )
#pragma comment( lib, "clangRewriteCore.lib" )
#pragma comment( lib, "clangRewriteFrontend.lib" )
#pragma comment( lib, "clangSema.lib" )
#pragma comment( lib, "clangSerialization.lib" )
#pragma comment( lib, "clangStaticAnalyzerCheckers.lib" )
#pragma comment( lib, "clangStaticAnalyzerCore.lib" )
#pragma comment( lib, "clangStaticAnalyzerFrontend.lib" )
#pragma comment( lib, "clangTooling.lib" )
#pragma comment( lib, "LLVMAArch64AsmParser.lib" )
#pragma comment( lib, "LLVMAArch64AsmPrinter.lib" )
#pragma comment( lib, "LLVMAArch64CodeGen.lib" )
#pragma comment( lib, "LLVMAArch64Desc.lib" )
#pragma comment( lib, "LLVMAArch64Disassembler.lib" )
#pragma comment( lib, "LLVMAArch64Info.lib" )
#pragma comment( lib, "LLVMAArch64Utils.lib" )
#pragma comment( lib, "LLVMAnalysis.lib" )
#pragma comment( lib, "LLVMARMAsmParser.lib" )
#pragma comment( lib, "LLVMARMAsmPrinter.lib" )
#pragma comment( lib, "LLVMARMCodeGen.lib" )
#pragma comment( lib, "LLVMARMDesc.lib" )
#pragma comment( lib, "LLVMARMDisassembler.lib" )
#pragma comment( lib, "LLVMARMInfo.lib" )
#pragma comment( lib, "LLVMAsmParser.lib" )
#pragma comment( lib, "LLVMAsmPrinter.lib" )
#pragma comment( lib, "LLVMBitReader.lib" )
#pragma comment( lib, "LLVMBitWriter.lib" )
#pragma comment( lib, "LLVMCodeGen.lib" )
#pragma comment( lib, "LLVMCore.lib" )
#pragma comment( lib, "LLVMCppBackendCodeGen.lib" )
#pragma comment( lib, "LLVMCppBackendInfo.lib" )
#pragma comment( lib, "LLVMDebugInfo.lib" )
#pragma comment( lib, "LLVMExecutionEngine.lib" )
#pragma comment( lib, "LLVMHexagonAsmPrinter.lib" )
#pragma comment( lib, "LLVMHexagonCodeGen.lib" )
#pragma comment( lib, "LLVMHexagonDesc.lib" )
#pragma comment( lib, "LLVMHexagonInfo.lib" )
#pragma comment( lib, "LLVMInstCombine.lib" )
#pragma comment( lib, "LLVMInstrumentation.lib" )
#pragma comment( lib, "LLVMInterpreter.lib" )
#pragma comment( lib, "LLVMipa.lib" )
#pragma comment( lib, "LLVMipo.lib" )
#pragma comment( lib, "LLVMIRReader.lib" )
#pragma comment( lib, "LLVMJIT.lib" )
#pragma comment( lib, "LLVMLinker.lib" )
#pragma comment( lib, "LLVMMBlazeAsmParser.lib" )
#pragma comment( lib, "LLVMMBlazeAsmPrinter.lib" )
#pragma comment( lib, "LLVMMBlazeCodeGen.lib" )
#pragma comment( lib, "LLVMMBlazeDesc.lib" )
#pragma comment( lib, "LLVMMBlazeDisassembler.lib" )
#pragma comment( lib, "LLVMMBlazeInfo.lib" )
#pragma comment( lib, "LLVMMC.lib" )
#pragma comment( lib, "LLVMMCDisassembler.lib" )
#pragma comment( lib, "LLVMMCJIT.lib" )
#pragma comment( lib, "LLVMMCParser.lib" )
#pragma comment( lib, "LLVMMipsAsmParser.lib" )
#pragma comment( lib, "LLVMMipsAsmPrinter.lib" )
#pragma comment( lib, "LLVMMipsCodeGen.lib" )
#pragma comment( lib, "LLVMMipsDesc.lib" )
#pragma comment( lib, "LLVMMipsDisassembler.lib" )
#pragma comment( lib, "LLVMMipsInfo.lib" )
#pragma comment( lib, "LLVMMSP430AsmPrinter.lib" )
#pragma comment( lib, "LLVMMSP430CodeGen.lib" )
#pragma comment( lib, "LLVMMSP430Desc.lib" )
#pragma comment( lib, "LLVMMSP430Info.lib" )
#pragma comment( lib, "LLVMNVPTXAsmPrinter.lib" )
#pragma comment( lib, "LLVMNVPTXCodeGen.lib" )
#pragma comment( lib, "LLVMNVPTXDesc.lib" )
#pragma comment( lib, "LLVMNVPTXInfo.lib" )
#pragma comment( lib, "LLVMObjCARCOpts.lib" )
#pragma comment( lib, "LLVMObject.lib" )
#pragma comment( lib, "LLVMOption.lib" )
#pragma comment( lib, "LLVMPowerPCAsmParser.lib" )
#pragma comment( lib, "LLVMPowerPCAsmPrinter.lib" )
#pragma comment( lib, "LLVMPowerPCCodeGen.lib" )
#pragma comment( lib, "LLVMPowerPCDesc.lib" )
#pragma comment( lib, "LLVMPowerPCInfo.lib" )
#pragma comment( lib, "LLVMR600AsmPrinter.lib" )
#pragma comment( lib, "LLVMR600CodeGen.lib" )
#pragma comment( lib, "LLVMR600Desc.lib" )
#pragma comment( lib, "LLVMR600Info.lib" )
#pragma comment( lib, "LLVMRuntimeDyld.lib" )
#pragma comment( lib, "LLVMScalarOpts.lib" )
#pragma comment( lib, "LLVMSelectionDAG.lib" )
#pragma comment( lib, "LLVMSparcCodeGen.lib" )
#pragma comment( lib, "LLVMSparcDesc.lib" )
#pragma comment( lib, "LLVMSparcInfo.lib" )
#pragma comment( lib, "LLVMSupport.lib" )
#pragma comment( lib, "LLVMSystemZAsmParser.lib" )
#pragma comment( lib, "LLVMSystemZAsmPrinter.lib" )
#pragma comment( lib, "LLVMSystemZCodeGen.lib" )
#pragma comment( lib, "LLVMSystemZDesc.lib" )
#pragma comment( lib, "LLVMSystemZDisassembler.lib" )
#pragma comment( lib, "LLVMSystemZInfo.lib" )
#pragma comment( lib, "LLVMTableGen.lib" )
#pragma comment( lib, "LLVMTarget.lib" )
#pragma comment( lib, "LLVMTransformUtils.lib" )
#pragma comment( lib, "LLVMVectorize.lib" )
#pragma comment( lib, "LLVMX86AsmParser.lib" )
#pragma comment( lib, "LLVMX86AsmPrinter.lib" )
#pragma comment( lib, "LLVMX86CodeGen.lib" )
#pragma comment( lib, "LLVMX86Desc.lib" )
#pragma comment( lib, "LLVMX86Disassembler.lib" )
#pragma comment( lib, "LLVMX86Info.lib" )
#pragma comment( lib, "LLVMX86Utils.lib" )
#pragma comment( lib, "LLVMXCoreAsmPrinter.lib" )
#pragma comment( lib, "LLVMXCoreCodeGen.lib" )
#pragma comment( lib, "LLVMXCoreDesc.lib" )
#pragma comment( lib, "LLVMXCoreDisassembler.lib" )
#pragma comment( lib, "LLVMXCoreInfo.lib" )