#include <iostream>
#include <array>

namespace {
    using namespace std;
    const string invalid_option_string = "Invalid option.";
    enum progress {
        ESCAPED,
        FIXED,
        HERDED,
        PROGRESS_SIZE
    };
    const array<const string, PROGRESS_SIZE> report_string_array { 
        { 
            "The goats have escaped because the fence is broken.",
            "The fence is fixed. The goats have escaped.",
            "The goats are herded. You won." 
        }
    };
    enum option {
        FIX_FENCE,
        HERD_GOAT,
        OPTION_SIZE
    };
    const array<const string, OPTION_SIZE> answer_string_array = {
        {
            "Fix the broken fence.",
            "Herd the goats."
        }
    };
    const array<array<progress, OPTION_SIZE>, PROGRESS_SIZE> result_array = {{
        /* ESCAPED */ { { /* FIX_FENCE */ FIXED,  /* HERD_GOAT */ ESCAPED } } ,
        /* FIXED   */ { { /* FIX_FENCE */ FIXED,  /* HERD_GOAT */ HERDED  } } ,
        /* HERDED  */ { { /* FIX_FENCE */ HERDED, /* HERD_GOAT */ HERDED  } }
    }};
    void report(const progress current_progress) {
        std::cout << report_string_array[current_progress] << "\n";
    }
    void ask() {
        using namespace std;
        for(size_t i = 0; i < answer_string_array.size(); ++i) {
            std::cout << i+1 << ") " << answer_string_array[i] << "\n";
        }
    }
    progress get_and_process_answer(const progress current_progress) {
        unsigned int answer;
        std::cout << ">";
        if (std::cin >> answer)
        {
            --answer;
            if (answer < OPTION_SIZE) {
                return result_array[current_progress][answer];
            } else {
                std::cout << invalid_option_string << "\n";
                return current_progress;
            }
        } else
        {
            if (std::cin.eof())
            {
                std::cout << "Okay, okay, you can leave the goats as a sacrifice!\n";
                exit(255);
            }
            std::cin.clear();
            std::cin.ignore(1024, '\n'); // just about enough, right
            std::cout << "I can't understand you.\n";
            return current_progress;
        }
    }
    bool has_won(const progress current_progress) {
        return (current_progress == HERDED);
    }
    void pause() {
        std::cin.get();
    }
}

int main()
{
    progress current_progress = ESCAPED;
    while (!has_won(current_progress)) {
        report(current_progress);
        ask();
        current_progress = get_and_process_answer(current_progress);
    }
    report(current_progress);
    pause(); // this is lame
    // return EXIT_SUCCESS; // and this redundant
}
