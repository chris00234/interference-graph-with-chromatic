#include "proj6.hpp"
#include "CSVReader.hpp"
#include "InterferenceGraph.hpp"
#include <algorithm>
#include <unordered_set>
#include <map>
#include <vector>
#include <queue>


using namespace proj6;

bool compare(std::pair<Variable, int> p1, std::pair<Variable, int> p2)
{
    return p1.second > p2.second;
}
// assignRegisters
//
// This is where you implement the register allocation algorithm
// as mentioned in the README. Remember, you must allocate at MOST
// d(G) + 1 registers where d(G) is the maximum degree of the graph G.
// If num_registers is not enough registers to accomodate the passed in
// graph you should return an empty map. You MUST use registers in the
// range [1, num_registers] inclusive.
RegisterAssignment proj6::assignRegisters(const std::string& path_to_graph,
    int num_registers) noexcept {
    InterferenceGraph<Variable> ig = CSVReader::load(path_to_graph);

    std::unordered_map<Variable, int> m;
    if (ig.numVertices() == 0)
        return m;
    //sort
    std::unordered_set<Variable> vertices;
    vertices = ig.vertices();
    std::vector<std::pair<Variable, int>> v;
    for (auto it = vertices.begin(); it != vertices.end(); it++)
    {
        v.push_back({ *it, ig.degree(*it) });
    }
    std::sort(v.begin(), v.end(), compare);
    
    std::vector<std::pair<Variable, int>> coloring;
    for (int pos = 0; pos < v.size(); pos++)
    {
        coloring.push_back({ v[pos].first, 0 });
    }
    std::queue<int> q;
    int max_degree = v[0].second + 1;
    if (max_degree >= num_registers)
        max_degree = num_registers;
    
    for (int i = 1; i <= max_degree; i++)
    {
        q.push(i);
    }
    

    int i = 0;
    int loopCount = 1;
    std::unordered_set<Variable> discovered;
    std::unordered_set<Variable> tmp;
    while (!q.empty())
    {
        if (coloring[i].second == 0 && discovered.find(coloring[i].first) == discovered.end())
        {
            discovered.insert(coloring[i].first);
            coloring[i].second = q.front();
            tmp = ig.neighbors(coloring[i].first);
            for (auto it = tmp.begin(); it != tmp.end(); it++)
            {
                discovered.insert(*it);
            }
        }
        if (i == ig.numVertices() - 1)
        {
            q.pop();
            i = 0;
            discovered.clear();
            loopCount++;
        }
        i++;
        
    }

    for (auto it = coloring.begin(); it != coloring.end(); it++)
    {
        if (it->second == 0)
            return m;
    }
    for (auto it = coloring.begin(); it != coloring.end(); it++)
    {
        m.insert(*it);
    }

    return m;
}