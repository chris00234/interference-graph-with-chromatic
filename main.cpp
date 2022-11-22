#include "CSVReader.hpp"
#include "IGWriter.hpp"
#include "InterferenceGraph.hpp"
#include "proj6.hpp"
#include <cassert>
#include <iostream>

int main() 
{
	//const auto& GRAPH = "simple.csv";

	/*const InterferenceGraph<Variable>& ig = CSVReader::load(GRAPH);
	assert(ig.numEdges() == 3);
	assert(ig.numVertices() == 3);
	

	const std::unordered_set<Variable>& expected_vertices = { "z", "x", "y" };
	assert(ig.vertices() == expected_vertices);

	std::unordered_set<Variable> expected_neighbors;
	expected_neighbors = { "y", "z" };
	assert(ig.neighbors("x") == expected_neighbors);

	expected_neighbors = { "x", "y" };
	assert(ig.neighbors("z") == expected_neighbors);

	expected_neighbors = { "z", "x" };
	assert(ig.neighbors("y") == expected_neighbors);
	std::cout << "first test completed" << std::endl << std::endl;

	assert(ig.interferes("x", "y"));
	assert(ig.interferes("y", "x"));
	assert(ig.interferes("x", "z"));
	assert(ig.interferes("z", "x"));
	assert(ig.interferes("z", "y"));
	assert(ig.interferes("y", "z"));
	std::cout << "second test completed" << std::endl << std::endl;

	assert(ig.degree("x") == 2);
	assert(ig.degree("y") == 2);
	assert(ig.degree("z") == 2);
	std::cout << "third test completed" << std::endl << std::endl;


	InterferenceGraph<Variable> ig2 = CSVReader::load(GRAPH);

	ig2.removeEdge("x", "y");
	assert(ig2.numEdges() == 2);
	ig2.removeEdge("x", "z");
	assert(ig2.numEdges() == 1);
	ig2.removeEdge("z", "y");
	assert(ig2.numEdges() == 0);

	assert(ig2.numVertices() == 3);
	ig2.removeVertex("z");
	assert(ig2.numVertices() == 2);
	ig2.removeVertex("y");
	assert(ig2.numVertices() == 1);
	ig2.removeVertex("x");
	assert(ig2.numVertices() == 0);
	std::cout << "fourth test completed" << std::endl << std::endl;

	const std::unordered_set<Variable>& expected_neighbors = { "y", "z" };*/

	/*const InterferenceGraph<Variable>& ig = CSVReader::load(GRAPH);
	
	const std::unordered_set<Variable>& expected_neighbors = { "y", "z" };
	assert(ig.neighbors("x") ==  expected_neighbors);
	std::cout << "fifth test completed" << std::endl << std::endl;*/

	/*InterferenceGraph<Variable> ig3 = CSVReader::load(GRAPH);
	ig3.removeEdge("x", "y");

	std::unordered_set<Variable> s;

	s = ig3.neighbors("x");
	std::cout << std::boolalpha << ig3.interferes("x", "y") << std::endl;
	for (auto i : s)
	{
		std::cout << i << std::endl;
	}*/
	const auto& GRAPH = "big_bipartite.csv";
	InterferenceGraph<Variable> ig3 = CSVReader::load(GRAPH);
	/*std::unordered_set<Variable> s;

	s = ig3.neighbors("7");
	for (auto i : s)
	{
		std::cout << i << std::endl;
	}*/
	//std::cout << ig3.degree("1") << std::endl;
	//ig3.removeEdge("1", "2");
	//std::cout << ig3.degree("1") << std::endl;
	////ig3.removeEdge("1", "3");
	//std::cout << ig3.degree("1") << std::endl;
	//std::cout << ig3.numEdges() << std::endl;
	std::unordered_map<Variable, int> m;
	m = assignRegisters(GRAPH, 1);
	for (auto it = m.begin(); it != m.end(); it++)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}


}
