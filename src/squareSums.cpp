#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <vector>

void printArray(const std::vector<int>& array, bool current = true) {
  if (current) {
    std::cout << "current: ";
  } else {
    std::cout << "prev   : ";
  }
  std::cout << '[';
  for (const int number : array) {
    std::cout << number << ", ";
  }
  std::cout << std::endl;
}

void printQueue(const std::vector<std::vector<int>>& queue) {
  std::cout << "QUEUE:\n";
  for (const auto edges: queue) {
    std::cout << "edge: [";
    for (const int number : edges) {
      std::cout << number << ", ";
    }
    std::cout << std::endl;
  }
}

void printGraphElements(const std::map<int, std::set<int>>& graph) {
  for (const auto& [value, possibleDestinations] : graph) {
    std::cout << value << " : [";
    for (const int number : possibleDestinations) {
      std::cout << number << ", ";
    }
    std::cout << std::endl;
  }
}

void updategraph(std::map<int, std::set<int>>* graph, int n) {
  
  std::cout << "current graph for n: " << n << std::endl;
  
  // preInitializeElements
  int end = graph->size() + 1;
  for (int i = end; i <= n; i++) {
    graph->insert(graph->end(), std::make_pair(i, std::set<int>()));
  }
  
  for (int i = end; i <= n; i++) {
    for (auto& [number, _] : *graph) {
      int potentialSquare = std::sqrt(number + i);
      
      if (number != i && potentialSquare * potentialSquare == number + i) {
        (*graph)[i].insert(number);
        (*graph)[number].insert(i);
      }
    }
  }
  
  // printGraphElements(*graph);
  
}

void printVisited(const std::vector<int>& visited) {
  std::cout << "VISITED" << std::endl;
  for (size_t i = 1; i < visited.size(); i++) {
    std::cout << i << " -> at: " << visited[i] << ", ";
  }
  std::cout << std::endl;
}

std::vector<int> getEdgesToVisit(const std::map<int, std::set<int>>& graph,
                                 int currentNode,
                                 const std::vector<int>& visited,
                                 int target,
                                 bool pretendNoneWasVisited = false) {
  
    std::vector<int> edgesToVisit;
    
    for (const int neighboor : graph.at(currentNode)) {
      if (neighboor != currentNode && neighboor <= target && (visited[neighboor] == -1 || pretendNoneWasVisited)) {
        edgesToVisit.push_back(neighboor);
      }
    }
    
    return edgesToVisit;
}

std::optional<size_t> getIndexOfElementInArray(const std::vector<int>& array, int element) {
  for (size_t i = 0; i < array.size(); i++) {
    if (array[i] == element) {
      return i;
    }
  }
  
  return std::nullopt;
}

void launchEndingAction(std::vector<int>&& current, std::vector<int>* previousSolution) {
  printArray(*previousSolution, false);
  *previousSolution = current;
  printArray(*previousSolution);
}

bool traverseGraph(std::vector<int>* current,
                   std::vector<int>* visited,
                   std::vector<std::vector<int>>* queue,
                   const std::map<int, std::set<int>>& graph,
                   int targetSize) { 
  
  int lastElement = current->back();
  
  while (!queue->empty()) {
    size_t queueSize = queue->size();
    auto& currentEdges = queue->back();
    if (!currentEdges.empty()) {
      
      int currentElement = currentEdges.back();
      currentEdges.pop_back();
      current->push_back(currentElement);
      
      (*visited)[currentElement] = current->size() - 1;
      queue->push_back(getEdgesToVisit(graph, currentElement, *visited, targetSize));
    }
    
    if (current->size() == static_cast<size_t>(targetSize)) {
      return true;
    } 
    
    // There is new element in the path
    if (queue->size() > queueSize) {
      continue;
    }
    
    while (!queue->empty()) {
      queue->pop_back();

      if (!current->empty()) {
        int notValidVisited = current->back();
        if (lastElement == notValidVisited) {
          return false;
        }
        (*visited)[notValidVisited] = false;
        current->pop_back();
      }

      if (!queue->empty()) {
        auto& edge = queue->back();
        // if there are still elements to visit in this permutation of path
        // We need to halt cleaning process and proceed to traverse a path
        if (!edge.empty()) {
          break;
        }
      }
    }
  }
  return false;
}

bool endsInsertionSolution(int target,
               const std::map<int, std::set<int>>& graph,
               std::vector<int>* previousSolution) {

    std::vector<int> current;
    current.reserve(target);
  
    auto possibleInsertions = getEdgesToVisit(graph,
                                              target,
                                              /*getAllValuesThatCanBeNextToTarget*/std::vector<int>(target+1, false),
                                              target,
                                              true);

    if (std::find(possibleInsertions.begin(),
                  possibleInsertions.end(),
                  previousSolution->front()) != possibleInsertions.end()) {
      
      current.push_back(target);
      current.insert(current.end(), previousSolution->begin(), previousSolution->end());
      
      std::cout << "ENDS INSERTION" << std::endl;
      launchEndingAction(std::move(current), previousSolution);
      return true;
      
    } else if (std::find(possibleInsertions.begin(),
                         possibleInsertions.end(),
                         previousSolution->back()) != possibleInsertions.end()) {
      
      current.insert(current.end(), previousSolution->begin(), previousSolution->end());
      current.push_back(target);
      
      std::cout << "ENDS INSERTION" << std::endl;
      launchEndingAction(std::move(current), previousSolution);
      return true;
    }
  
  return false;
}

bool middleInsertionSolution(int target,
                          const std::map<int, std::set<int>>& graph,
                          std::vector<int>* previousSolution) {
  
  std::vector<int> current;
  current.reserve(target);
  const auto possibleInsertions = getEdgesToVisit(graph,
                                              target,
                                              /*getAllValuesThatCanBeNextToTarget*/std::vector<int>(target+1, false),
                                              target,
                                              true);

  current->push_back(previousSolution->front());
  for (size_t i = 1; i < previousSolution->size(); i++) {
    if (std::find(possibleInsertions.cbegin(),
                  possibleInsertions.cend(),
                  current->back()) != possibleInsertions.cend() &&
        std::find(possibleInsertions.cbegin(),
                  possibleInsertions.cend(),
                  (*previousSolution)[i]) != possibleInsertions.cend()) {
      
      // fill the target
      current->push_back(target);
      
      // fill the rest from the previous solution
      for (size_t x = i; x < previousSolution->size(); x++) {
        current->push_back((*previousSolution)[x]);
      }
      
      std::cout << "MIDDLE INSERTION" << std::endl;
      launchEndingAction(std::move(*current), previousSolution);
      return true;
    }
    
    current->push_back((*previousSolution)[i]);
  }
  
  current->clear();
  return false;
}

bool bruteForceSolution(int target,
                        const std::map<int, std::set<int>>& graph,
                        std::vector<int>* previousSolution,
                        std::vector<int>* current) {
  std::vector<std::vector<int>> queue;
  queue.reserve(target);
  std::vector<bool> visited(target+1, false);
  
  // Calculate solution from scratch;
  for (const auto& [startingPoint, _]: graph) {
    
    if (startingPoint <= target) {
      queue.push_back(std::vector({startingPoint}));
    }
    
    if (traverseGraph(current, &visited, &queue, graph, target)) {
      std::cout << "BRUTE FORCE" << std::endl;
      launchEndingAction(std::move(*current), previousSolution);
      return true;
    }
  }    

  return false;
}


std::vector<int> square_sums_row(int target)
{
  
  std::cout << std::string(50, '=') << std::endl;
  static std::map<int, std::set<int>> graph = {{1, {}}};
  if (graph.size() < static_cast<size_t>(target)) {
    updategraph(&graph, target);
  }
  
  static std::vector<int> previousSolution = {};
  
  // Check if we can add new element to the end or beggining
  if (target - previousSolution.size() == 1) {
    if (endsInsertionSolution(target, graph, &previousSolution)) {
      return previousSolution;
    } else if (middleInsertionSolution(target, graph, &previousSolution)) {
      return previousSolution;
    }
  }
  if (bruteForceSolution(target, graph, &previousSolution, &current)) {
      return current; 
  }
  return std::vector<int>();
  
}
