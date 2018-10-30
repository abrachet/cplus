#include <vector>

template <class T>
bool find_in_vector(const std::vector<T>& _vec, T to_find)
{
    for (auto i : _vec)
        if (i == to_find)
            return true;

    return false;
}

