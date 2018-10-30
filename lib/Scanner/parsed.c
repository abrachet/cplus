
typedef int alex_t;

int test()
{
    const char* test = "I am a test";
    int a = 5;
}

int func(int should_be_const)
{
    int should_not_be = should_be_const;

    should_not_be++;
}

int main()
{
    func(1);
}
