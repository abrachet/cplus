#include "./UserTypes.hpp"

extern std::vector<UserTypes> user_types;

void ut_push_back(UserTypes ut) 
{
    assert(ut._ID.length > 0);
    user_types.push_back(ut);
}

void ut_push_back(UserTypes* ut)
{

}