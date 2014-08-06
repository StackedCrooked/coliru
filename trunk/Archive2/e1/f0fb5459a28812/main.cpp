


// tags
struct compile_button {};
struct share_button {};
struct command_field {};
struct code_field {};


// build the gui
auto coliru = dialog(
    title("Coliru"),
    stretch(vbox(
        tagged(code_field{}, stretch(input("int main(){}"))),
        hbox(
            tagged(command_field{},  stretch(input("g++ main.cpp"))),
            tagged(compile_button{}, button("compile_button, link and run")),
            tagged(share_button{},   button("share_button!")))
    ))
);


// register events
get<compile_button>(coliru) += [] {
    do_compile(
        get<command_field>(dialog),
        get<code_field>(dialog));
};

get<share_button>(coliru) += []{
    do_share(
        get<command_field>(dialog),
        get<code_field>(dialog));
};

