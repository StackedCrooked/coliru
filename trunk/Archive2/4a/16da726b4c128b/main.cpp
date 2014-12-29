#include <iostream>
#include <string>
#include <vector>
#include <boost/range/numeric.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/optional.hpp>

struct StudentRecord {
    std::string strName, strID;

    StudentRecord(std::string const& name, std::string id) 
        : strName(name), strID(id)
    {
    }

    struct Scores {
        double fQuiz[3]    = { 0 };
        double fMacProb[2] = { 0 };
        double fFinalExam  = 0;

        friend std::ostream& operator<<(std::ostream& os, Scores const& score) {
            return os << "Scores[\n"
                   "\tQuiz:            { " << score.fQuiz[0]                << ", " << score.fQuiz[1]    << ", "  << score.fQuiz[2] << " }\n"
                   "\tMachine Problem: { " << score.fMacProb[0]             << ", " << score.fMacProb[1] << "}\n"
                   "\tFinal Exam:        " << score.fFinalExam              << "\n"
                   "\tRaw Score:         " << score.rawScore()              << "\n"
                   "\tFinal Grade:       " << score.finaleGrade()           << "\n"
                   "\tAvg. Quiz score:   " << score.averageQuiz()           << "\n"
                   "\tAvg. Mach.Problem: " << score.averageMachineProblem() << "\n"
                "]";
        }

        double averageQuiz() const            { return boost::accumulate(fQuiz,0.0f)/boost::size(fQuiz); }
        double averageMachineProblem() const  { return boost::accumulate(fMacProb,0.0f)/boost::size(fMacProb); }
        double rawScore() const               { return averageQuiz() + averageMachineProblem() + fFinalExam; } // FIXME MISSING FROM OP CODE
        double finaleGrade() const            { return (rawScore() >= 94)? 1 : 0; }
    } mutable score;

    friend std::ostream& operator<<(std::ostream& os, StudentRecord const& sr) {
        return os << "StudentRecord[Name:'" << sr.strName << "', ID:'" << sr.strID << "']";
    }
};

namespace bmi = boost::multi_index;
using Students = boost::multi_index_container<StudentRecord,
    bmi::indexed_by<
        bmi::random_access<>,
        bmi::ordered_unique<
            bmi::tag<struct byName>,
            bmi::member<StudentRecord, std::string, &StudentRecord::strName>
        >,
        bmi::ordered_unique<
            bmi::tag<struct byId>,
            bmi::member<StudentRecord, std::string, &StudentRecord::strID>
        >
    >
>;

enum class Field { NONE, NAME, ID, QUIZ1, QUIZ2, QUIZ3, MP1, MP2, FE, QUIT };

void displayOption() {
    std::cout << "\n**************************************";
    std::cout << "\n [1] Add Record";
    std::cout << "\n [2] View Student Record";
    std::cout << "\n [3] Modify Student Record";
    std::cout << "\n [4] View Class Record";
    std::cout << "\n [5] EXIT";
    std::cout << "\n**************************************";
}

template <typename Idx>
static inline boost::optional<StudentRecord const&> searchRecord(Idx& idx, std::string const& key) {
    auto it = idx.find(key);
    if (it != idx.end())
        return *it;
    else 
        return boost::none;
}

boost::optional<StudentRecord const&> searchRecord(Students& table, std::string const& key, Field nMode) {
    switch(nMode) {
        case Field::NAME: return searchRecord(table.get<byName>(), key);
        case Field::ID:   return searchRecord(table.get<byId>(), key);
        default:          std::cerr << "Illegal index\n";
    }
    return boost::none;
}

void viewStudentRecord(StudentRecord const& sr) {
    std::cout << sr << "\n";
    std::cout << sr.score << "\n";
}

void addRecord(Students& table) {
    std::cout << "*****ADD RECORD*****\n";

    std::string name, id;
    std::cout << "STUDENT NAME: ";
    std::cin >> name;
    std::cout << "STUDENT ID: ";
    if (std::cin >> id) {
        auto insertion = table.emplace_back(name, id);
        if (!insertion.second) {
            std::cerr << "Name or ID not unique, existing item: " << *insertion.first << "\n";
        }
    } else
    {
        std::cerr << "Add aborted\n";
    }
}

void displayOptionInput() {
    std::cout << "\n**************************************";
    std::cout << "\n  [" << static_cast<int>(Field::NAME)  << "] Enter New Student Name ";
    std::cout << "\n  [" << static_cast<int>(Field::ID)    << "] Enter New Student ID ";
    std::cout << "\n  [" << static_cast<int>(Field::QUIZ1) << "] Enter Quiz#1 ";
    std::cout << "\n  [" << static_cast<int>(Field::QUIZ2) << "] Enter Quiz#2 ";
    std::cout << "\n  [" << static_cast<int>(Field::QUIZ2) << "] Enter Quiz#3 ";
    std::cout << "\n  [" << static_cast<int>(Field::MP1)   << "] Enter Machine Problem#1 ";
    std::cout << "\n  [" << static_cast<int>(Field::MP2)   << "] Enter Machine Problem#2 ";
    std::cout << "\n  [" << static_cast<int>(Field::FE)    << "] Enter Final Exam ";
    std::cout << "\n  [" << static_cast<int>(Field::NONE)  << "] DISPLAY ";
    std::cout << "\n  [" << static_cast<int>(Field::QUIT)  << "] EXIT ";
    std::cout << "\n**************************************";
}

void modifyRecord(Students& table, StudentRecord const& sr) {
    Field field = Field::NONE;

    std::cout << "You are going to modify record " << sr << "\n";

    auto& idx = table.get<byName>();
    auto it   = idx.find(sr.strName);
    assert(idx.end()!=it);

    do {
        displayOptionInput();
        std::cout << "******************\n";
        std::cout << "ENTER YOUR OPTION : ";
        int mode;
        std::cin >> mode;
        std::cout << "******************\n\n";

        field = static_cast<Field>(mode);

        if (!idx.modify(it, [&](StudentRecord &sr) {
                switch (field) {
                    case Field::NAME:  std::cout << "NEW NAME:   "; std::cin >> sr.strName;           break;
                    case Field::ID:    std::cout << "NEW ID:     "; std::cin >> sr.strID;             break;
                    case Field::QUIZ1: std::cout << "NEW QUIZ#1: "; std::cin >> sr.score.fQuiz[0];    break;
                    case Field::QUIZ2: std::cout << "NEW QUIZ#2: "; std::cin >> sr.score.fQuiz[1];    break;
                    case Field::QUIZ3: std::cout << "NEW QUIZ#3: "; std::cin >> sr.score.fQuiz[2];    break;
                    case Field::MP1:   std::cout << "NEW MP1:    "; std::cin >> sr.score.fMacProb[0]; break;
                    case Field::MP2:   std::cout << "NEW MP2:    "; std::cin >> sr.score.fMacProb[1]; break;
                    case Field::FE:    std::cout << "NEW FE:     "; std::cin >> sr.score.fFinalExam;  break;
                    //
                    case Field::QUIT:  
                    case Field::NONE:  viewStudentRecord(sr); break;
                }
            })) 
        {
            std::cerr << "Edit was rejected\n";
        }

        if (!std::cin) {
            if (!std::cin.eof()) {
                std::cin.clear();
                std::cin.ignore(1ul<<10, '\n');
            }
        }
    } while (Field::QUIT != field);
}

void chooseNameOrID(std::string& str, Field& nMode) {
    std::cout << "[" << static_cast<int>(Field::NAME) << "] By name\n";
    std::cout << "[" << static_cast<int>(Field::ID)   << "] By ID\n";
    std::cout << "Choose: ";

    int number;
    if (std::cin >> number) {
        nMode = static_cast<Field>(number);
        switch(nMode) {
            case Field::NAME:
                std::cout << "Find name: ";
                std::cin >> str;
                break;
            case Field::ID:
                std::cout << "Find ID: ";
                std::cin >> str;
                break;
            default:
                std::cout << "Illegal entry\n";
                nMode = Field::NONE;
        }
    }

    if (!std::cin) {
        if (!std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(1ul<<10, '\n');
            
            nMode = Field::NONE;
        }
    }
}

void viewClassRecordTable(Students const& c) {
    if (c.empty()) {
        std::cout << "No entries\n";
        return;
    }

    size_t i = 0;
    char ch = '\0';

    do {
        viewStudentRecord(c[i]);
        std::cout << "Enter [P]rev, [N]ext or [Q]uit: ";
        std::cin >> ch;

        switch(ch) {
            case 'P': case 'p':
                i = (i + c.size() - 1) % c.size();
                break;
            case 'N': case 'n':
                i = (i + 1) % c.size();
        }
    } while (std::cin && ch != 'Q' && ch != 'q');
}

int main() {
    Students table;

    int choice = 0;
    do {
        displayOption();
        std::cout << "***************\n";
        std::cout << "OPTION:";

        std::string input;
        Field mode;

        if (std::cin >> choice) switch (choice) {
            case 1: {
                        addRecord(table);
                        std::cout << "NUM REC" << table.size();
                        break;
                    }
            case 2: {
                        chooseNameOrID(input, mode);
                        auto sr = searchRecord(table, input, mode);
                        if (sr) {
                            viewStudentRecord(*sr);
                        } else {
                            std::cerr << "Corresponding record not found\n";
                        }
                        break;
                    }
            case 3: {
                        chooseNameOrID(input, mode);
                        auto sr = searchRecord(table, input, mode);
                        if (sr) {
                            modifyRecord(table, *sr);
                        } else {
                            std::cerr << "Corresponding record not found\n";
                        }
                        break;
                    }
            case 4: {
                        viewClassRecordTable(table);
                        break;
                    }
        } else
        {
            if (!std::cin.eof()) {
                std::cin.clear();
                std::cin.ignore(1ul<<10, '\n');
            }
            std::cerr << "Try again\n";
        }
    } while (choice != 5);
}
