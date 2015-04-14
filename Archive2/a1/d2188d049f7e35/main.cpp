int main()
{
    auto compilations = FixedCompilationDatabase{Twine("."), ArrayRef<std::string>{}};

    auto tool = ClangTool{compilations, std::vector<std::string>{"test.cpp"}};

    tool.mapVirtualFile("test.cpp", "/// [[Remoted]]\nclass X { void foo(); };");

    auto action = newFrontendActionFactory<ExampleFrontendAction>();

    tool.run(action.get());
}