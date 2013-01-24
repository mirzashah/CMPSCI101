//Containers.h
//*****************************************************************************
//Functional style wrappers for STL
//*****************************************************************************

#ifndef CONTAINERS_H_DEFINED
#define CONTAINERS_H_DEFINED

#include <vector>
#include <string>
#include <map>
#include <list>
#include <algorithm>

using std::vector;
using std::list;
using std::string;
using std::map;

namespace Beeber
{
namespace Containers
{

class ContainerException
{
    public:
        ContainerException(){}
        ~ContainerException(){}
};

/*****************************************************/
template <typename T>
struct LessThanFunctor : public std::binary_function<T, T, bool>
/*****************************************************/
{
    LessThanFunctor(bool (*lessThanFunc)(T, T))
    {
        _lessThanFunc = lessThanFunc;
    }
    bool operator()(T x, T y)
    {
        return(_lessThanFunc(x,y));
    }

    bool (*_lessThanFunc)(T, T);

};

/********************************************************/
template <typename T> vector<T> Append(const vector<T>& v1, const vector<T>& v2)
/********************************************************/
{
    vector<T> toReturn;
    for(unsigned int c=0; c<v1.size(); c++)
        toReturn.push_back(v1.at(c));
    for(unsigned int c=0; c<v2.size(); c++)
        toReturn.push_back(v2.at(c));
    return(toReturn);
}

/********************************************************/
template <typename T> vector<T> Append(const T& v1, const T& v2)
/********************************************************/
{
    return(Append(Construct(v1), v2));
}

/********************************************************/
template <typename T> vector<T> Append(const T& v1, const vector<T>& v2)
/********************************************************/
{
    return(Append(Construct(v1), v2));
}

/********************************************************/
template <typename T> vector<T> Append(const vector<T>& v1, const T& v2)
/********************************************************/
{
    return(Append(v1, Construct(v2)));
}

/********************************************************/
template <typename T> vector<T> Construct(const T& firstItem)
/********************************************************/
{
	vector<T> toReturn;
	toReturn.push_back(firstItem);
	return(toReturn);
}

/********************************************************/
template <typename T> bool Contains(const vector<T>& v, const T& item)
/********************************************************/
{
    return(FindIndex(v, item) != -1);
}

/********************************************************/
template <typename S, typename T> bool ContainsKey(const map<S,T>& m, const S& key)
/********************************************************/
{
    typename std::map<S, T>::const_iterator itr;
    for(itr = m.begin(); itr!=m.end(); itr++)
    {
        if(itr->first == key)
            return(true);
    }
    return(false);
}

/********************************************************/
template <typename T> int FindIndex(const vector<T>& v, const T& item)
/********************************************************/
{
    for(unsigned int c=0; c<v.size(); c++)
        if(v.at(c)==item)
            return(c);
    return(-1);
}

/********************************************************/
template <typename T> T FirstItem(const vector<T>& v)
/********************************************************/
{
    if(v.size()==0)
        throw ContainerException();
    else
        return(v.at(0));
}

/********************************************************/
template <typename T> T LastItem(const vector<T>& v)
/********************************************************/
{
    if(v.size()==0)
        throw ContainerException();
    else
        return(v.at(v.size()-1));
}

/********************************************************/
template <typename T> vector<T> RemoveLast(const vector<T>& v)
/********************************************************/
{
    vector<T> toReturn;
    for(unsigned int c=0; c<v.size()-1; c++)
        toReturn.push_back(v.at(c));
    return(toReturn);
}

/********************************************************/
template <typename T> vector<T> RemoveFirst(const vector<T>& v)
/********************************************************/
{
    vector<T> toReturn;
    for(unsigned int c=1; c<v.size(); c++)
        toReturn.push_back(v.at(c));
    return(toReturn);
}

/********************************************************/
template <typename T> vector<T> Remove(const vector<T>& v, const T& toRemove)
/********************************************************/
{
    vector<T> toReturn;
    for(unsigned int c=0; c<v.size(); c++)
    {
        if(v.at(c)!=toRemove)
            toReturn.push_back(v.at(c));
    }
    return(toReturn);
}

/********************************************************/
template <typename T> vector<T> Reverse(const vector<T>& v)
/********************************************************/
{
	vector<T> toReturn;
	for(int c=((int)(v.size()))-1; c>=0; c--)
		toReturn.push_back(v.at(c));
	return(toReturn);
}


/********************************************************/
template <typename T> vector<T> SortAscending(const vector<T>& v)
/********************************************************/
{
    vector<T> temp = v;
	std::sort(temp.begin(), temp.end());
	return(temp);
}

/********************************************************/
template <typename T> vector<T> SortAscending(const vector<T>& v, bool (*lessThanFunc)(T, T))
/********************************************************/
{
    vector<T> temp = v;
	std::sort(temp.begin(), temp.end(), LessThanFunctor<T>(lessThanFunc));
	return(temp);
}

/********************************************************/
template <typename T> vector<T> SortDescending(const vector<T>& v)
/********************************************************/
{
	return(Reverse(SortAscending(v)));
}

/********************************************************/
template <typename T> vector<T> SortDescending(const vector<T>& v, bool (*lessThanFunc)(T, T))
/********************************************************/
{
	return(Reverse(SortAscending(v, lessThanFunc)));
}

/********************************************************/
template <typename T> void Swap(T& v1, T& v2)
/********************************************************/
{
    T temp = v1;
    v1 = v2;
    v2 = temp;
}

};
};

#endif
