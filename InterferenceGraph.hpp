#ifndef __INTERFERENCE_GRAPH__HPP
#define __INTERFERENCE_GRAPH__HPP

#include <exception>
#include <string>
#include <unordered_set>
#include <map>


class UnknownVertexException : public std::runtime_error {
public:
    UnknownVertexException(const std::string& v)
        : std::runtime_error("Unknown vertex " + v) {}
};

class UnknownEdgeException : public std::runtime_error {
public:
    UnknownEdgeException(const std::string& v, const std::string& w)
        : std::runtime_error("Unknown edge " + v + " - " + w) {}
};

// InterferenceGraph
//
// This is a class representing an interference graph
// as described in "Part 1: Interference Graph" of the README.md
// file.
template <typename T> class InterferenceGraph {
public:
    // Custom type used to represent edges. This is mainly
    // used in the utility function for reading and writing
    // the graph structure to/from files. You don't need to use it.
    using EdgeTy = std::pair<T, T>;

    InterferenceGraph();

    ~InterferenceGraph();

    void addEdge(const T& v, const T& w);

    void addVertex(const T& vertex) noexcept;

    void removeEdge(const T& v, const T& w);

    void removeVertex(const T& vertex);

    std::unordered_set<T> vertices() const noexcept;

    std::unordered_set<T> neighbors(const T& vertex) const;

    unsigned numVertices() const noexcept;

    unsigned numEdges() const noexcept;

    bool interferes(const T& v, const T& w) const;

    unsigned degree(const T& v) const;

private:
    // Private member variables here.
    std::map<T, std::unordered_set<T>> adjacencyList;
    unsigned num_edge{};
};

template <typename T> InterferenceGraph<T>::InterferenceGraph() {}

template <typename T> InterferenceGraph<T>::~InterferenceGraph() {}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::neighbors(const T& vertex) const {
    if (adjacencyList.find(vertex) == adjacencyList.end())
    {
        throw UnknownVertexException(vertex);
    }

    std::unordered_set<T> s;
    s = adjacencyList.at(vertex);
    return s;
}

template <typename T>
std::unordered_set<T> InterferenceGraph<T>::vertices() const noexcept {
    std::unordered_set<T> s;
    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++)
    {
        s.insert(it->first);
    }
    return s;
}

template <typename T>
unsigned InterferenceGraph<T>::numVertices() const noexcept 
{
    return adjacencyList.size();
}

template <typename T> unsigned InterferenceGraph<T>::numEdges() const noexcept 
{
    return num_edge;
}

template <typename T>
void InterferenceGraph<T>::addEdge(const T& v, const T& w) 
{
    if (adjacencyList.find(v) == adjacencyList.end() || adjacencyList.find(w) == adjacencyList.end())
    {
        throw UnknownEdgeException(v,w);
    }
    adjacencyList.at(v).insert(w);
    adjacencyList.at(w).insert(v);
    num_edge++;

}

template <typename T>
void InterferenceGraph<T>::removeEdge(const T& v, const T& w) 
{
    if (adjacencyList.find(v) == adjacencyList.end() || adjacencyList.find(w) == adjacencyList.end())
    {
       throw UnknownEdgeException(v,w);
    }
    adjacencyList.at(v).erase(w);
    adjacencyList.at(w).erase(v);
    num_edge--;
}

template <typename T>
void InterferenceGraph<T>::addVertex(const T& vertex) noexcept 
{
    if (adjacencyList.find(vertex) != adjacencyList.end())
    {
        return;
    }
    adjacencyList.insert({ vertex,{} });
}

template <typename T>
void InterferenceGraph<T>::removeVertex(const T& vertex) 
{
    if (adjacencyList.find(vertex) == adjacencyList.end())
    {
        throw UnknownVertexException(vertex);
    }
    adjacencyList.erase(vertex);
    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++)
    {
        if (it->second.find(vertex) != it->second.end())
            it->second.erase(vertex);
    }
}

template <typename T>
bool InterferenceGraph<T>::interferes(const T& v, const T& w) const 
{
    if (adjacencyList.find(v) == adjacencyList.end() || adjacencyList.find(w) == adjacencyList.end())
    {
        throw UnknownEdgeException(v,w);
    }
    if (adjacencyList.at(v).find(w) != adjacencyList.at(v).end() && adjacencyList.at(w).find(v) != adjacencyList.at(w).end())
        return true;
    return false;
}

template <typename T>
unsigned InterferenceGraph<T>::degree(const T& v) const 
{ 
    std::unordered_set<T> s;
    s = adjacencyList.at(v);
    unsigned num = 0;
    for (auto it = s.begin(); it != s.end(); it++)
    {
        num++;
    }
    return num;
}

#endif

