void pretty_print(const type_declaration_class klass)
    {
        // Get the info struct
        class_declaration info = klass.type;
        // Print final, if we are
        if(info.is_final)
        {
            std::cout << "final ";
        }
        // Print abstract, if we are
        if(info.is_abstract)
        {
            std::cout << "abstract ";
        }
        // Print the 'class' keyword, the class name, and the class we extend
        // (in non inheriting classes this will be java.lang.Object).
        std::cout << "class " << info.name.identifier_string << " extends " << name_to_string(info.extends);
        // If we're implementing anything
        if(info.implements.empty() == false)
        {
            // Then write out the 'implements' keyword, and a comma seperated
            // list of implements 
            std::cout << " implements ";
            std::cout << concat(info.implements, name_to_string, ", ");
        }
        // Newline because we like allman style
        std::cout << std::endl;
        // Start brace, and newline
        std::cout << "{" << std::endl;
        // Print all members
        unpack_list(info.members, pretty_print);
        // End brace, and newline
        std::cout << "}" << std::endl;
    }