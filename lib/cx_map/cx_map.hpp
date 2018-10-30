#pragma once

#include <vector>
#include <utility>
#include <functional>

template <class T, class K>
class __base_map 
{
    std::vector< std::pair<T, K> > _map;

    __base_map();
    __base_map(std::vector< std::pair<T, K> >)

    virtual std::pair<T, K> find_pair(T);

};

template<class T, class Func = std::function<void(void*)> >
class CX_Map : protected __base_map
{
    __base_map< __base_map<T, Func>, Func > _map;

    

};
