#include <string>
#include <vector>


namespace vector_operations {
    template <class T>
    bool find_in_vector(std::vector<T>& vec, T to_find)
    {
        for (auto i : vec)
            if (i == to_find)
                return true;

        return false;
    }


};

