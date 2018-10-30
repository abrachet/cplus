#include "./Scanner/scanner.hpp"
#include "./Lexer/lexer.hpp"

extern token_vector_t __tokenized_file;

#ifdef DEBUG
extern std::vector<UserTypes> user_types;
extern std::vector<KnownType> known_types;

extern std::map<std::string, void(*)(FuncArg)> function_map;

void __attribute__ ((noinline)) _break()
{
    return;
}
#endif

int main(int argc, char** argv)
{
    std::string file_name(argv[1]);

    Scanner scanner(file_name);

    auto this_vec = scanner.get_tv();

    puts("\n========\n");

    scanner.print_vector();



    lexlines();

    int break_point = 0;
    break_point++;

}