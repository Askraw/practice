#include<vector>
#include<string>
#include<iostream>
using namespace std;

class President{
public:
    string name;
    string country;
    int year;
    President(string &&_name, string &&_country, int &&_year):name(move(_name)), country(move(_country)), year(move(_year)){
        cout << "I'm  being constructed\n";
    }
    President(President &&_president):name(move(_president.name)), country(move(_president.country)), year(move(_president.year)){
        cout << "I'm being moved\n";
    }
    President& operator=(const President& other) = default;
};

int main()
{
    std::vector<President> elections;
    std::cout << "emplace_back:\n";
    elections.emplace_back("Nelson Mandela", "South Africa", 1994);

    std::vector<President> reElections;
    std::cout << "\npush_back:\n";
    reElections.push_back(President("Franklin Delano Roosevelt", "the USA", 1936));

    std::cout << "\nContents:\n";
    for (President const& president : elections) {
        std::cout << president.name << " was elected president of "
            << president.country << " in " << president.year << ".\n";
    }
    for (President const& president : reElections) {
        std::cout << president.name << " was re-elected president of "
            << president.country << " in " << president.year << ".\n";
    }
}
