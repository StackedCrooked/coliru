int main()
{
  auto invocation = new CompilerInvocation;
  
  invocation->getLangOpts()->CPlusPlus = true;
  
  invocation->getPreprocessorOpts().addRemappedFile(
      "boo.cpp",
      MemoryBuffer::getMemBuffer("/// class X { void bee(); };").release());
  
  invocation->getPreprocessorOpts().addRemappedFile(
      "baa.cpp",
      MemoryBuffer::getMemBuffer("/// class Y { void gee(); };").release());
  
  invocation->getFrontendOpts().Inputs.push_back(FrontendInputFile("baa.cpp", IK_CXX));
  
  invocation->getFrontendOpts().Inputs.push_back(FrontendInputFile("boo.cpp", IK_CXX));
  
  invocation->getFrontendOpts().ProgramAction = frontend::ParseSyntaxOnly;
  invocation->getTargetOpts().Triple = llvm::sys::getDefaultTargetTriple();
  
  CompilerInstance compiler;
  compiler.setInvocation(invocation);
  compiler.createDiagnostics();

  ExampleFrontendAction test_action;
  compiler.ExecuteAction(test_action);
}