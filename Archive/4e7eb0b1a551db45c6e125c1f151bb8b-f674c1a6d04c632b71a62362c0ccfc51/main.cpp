void pretty_print(const import_declaration_on_demand import)
    {
        const name* import_name = import.import;
        std::cout << "import " << name_to_string(import_name) << ";" << std::endl;
    }

    void pretty_print(const import_declaration_single import)
    {
        const name* import_name = import.import;
        std::cout << "import " << name_to_string(import_name) << "." << import.class_name.identifier_string << ";" << std::endl;
    }

    void pretty_print(const import_declaration* import)
    {
        Match(import)
        {
            Case(const import_declaration_on_demand import)
            {
                pretty_print(import);
            }
            Case(const import_declaration_single import)
            {
                pretty_print(import);
            }
        }
        EndMatch
    }

    void pretty_print(package_declaration package)
    {
        std::cout << "package " << name_to_string(&package) << ";" << std::endl;
    }

    void pretty_print(source_file sf)
    {
        // Start marker
        std::cout << ">>>> File: " << sf.name << " Start <<<<" << std::endl;

        // Print package declaration if any
        call_if(sf.package, pretty_print);
        //pretty_print(sf.package);
        // Print imports
        unpack_list(sf.imports, pretty_print);
        // Print the type, inside the file
        pretty_print(sf.type);
        
        // End Marker
        std::cout << ">>>> File: " << sf.name << " End <<<<" << std::endl;
    }

    void pretty_print(program prog)
    {
        std::cout << " *** " << "pretty printing Ast::program" << " *** " << std::endl;
        // Pretty print each source file in program
        unpack_list(prog, pretty_print);
    }