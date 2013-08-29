struct ExportTest {

        std::vector<std::unique_ptr<int>> AllTheExports;

        void furrovineexport DoShit () {
            AllTheExports.emplace_back( std::unique_ptr<int>( new int( 24 ) ) );
        }

    };