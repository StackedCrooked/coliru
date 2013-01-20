#ifdef FURROVINECOMPILE

#ifdef FURROVINEDLL
#define furrovineexport __declspec( dllexport )
#else
#define furrovineexport 
#endif /* FURROVINEDLL */

#else

#ifdef FURROVINEDLL
#define furrovineexport __declspec( dllimport )
#else
#define FURROVINECOMPILE
#define furrovineexport 
#endif /* FURROVINEDLL */

#endif /* FURROVINECOMPILE */

    /* The New Way, shorter compile times, don't have to export the std:: types */

	struct ExportTest {

        std::vector<std::unique_ptr<int>> AllTheExports;

        void furrovineexport DoShit () {
            AllTheExports.emplace_back( std::unique_ptr<int>( new int( 24 ) ) );
        }

    };

	/* The old, shitty way, that increased compile times and didn't work in some special cases, see below:

	// In order to use a std:: type in a dll without a warning, since we were exporting the whole thing, we had to:

#ifdef FURROVINEDLL

	template class furrovineexport std::unique_ptr<int>;
	template class furrovineexport std::vector<std::unique_ptr<int>>;

#endif // FURROVINEDLL

	struct furrovineexport ExportTest {

		std::vector<std::unique_ptr<int>> AllTheExports;

		void DoShit () {
			AllTheExports.emplace_back( std::unique_ptr<int>( new int( 24 ) ) );
		}

	};


    // Now multiply this std:: export for tens - maybe a hundred - different pointer types and such
    // And then do it for every unique_ptr you need from the D3D library, and it takes ass-backwards long
	*/