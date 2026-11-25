#include <iostream>
#include <vector>

using namespace std;

// Generates all complete triangulations of the polygon sub-chain from vertex i to vertex j.
// A triangulation is a list of triangles, where each triangle is a vector<int> of 3 vertices {i, k, j}.
vector<vector<vector<int>>> generateAllTriangulations(int i, int j) {
    // Base Case: Only 2 adjacent vertices (a single polygon edge).
    // No triangle can be formed, so there is 1 valid (empty) configuration.
    if(i + 1 == j) {
        return {{}};
    }

    vector<vector<vector<int>>> allTriangulations;

    // Fix base edge (i, j) and iterate over every possible apex vertex k
    for(int k = i + 1; k < j; k++) {
        // The fixed triangle formed by choice k
        vector<int> currentTriangle = {i, k, j};

        // Recursively find all ways to triangulate the left polygon [i ... k]
        vector<vector<vector<int>>> leftTriangulations = generateAllTriangulations(i, k);

        // Recursively find all ways to triangulate the right polygon [k ... j]
        vector<vector<vector<int>>> rightTriangulations = generateAllTriangulations(k, j);

        // Cartesian product: combine every left triangulation with every right triangulation
        for(const auto &leftConfig : leftTriangulations) {
            for(const auto &rightConfig : rightTriangulations) {
                vector<vector<int>> combined = {currentTriangle};

                // Add all triangles from the left sub-polygon
                combined.insert(combined.end(), leftConfig.begin(), leftConfig.end());

                // Add all triangles from the right sub-polygon
                combined.insert(combined.end(), rightConfig.begin(), rightConfig.end());

                allTriangulations.push_back(combined);
            }
        }
    }

    return allTriangulations;
}

int main() {
    int n = 5; // Convex polygon with vertices 0, 1, 2, 3, 4 (Pentagon)

    vector<vector<vector<int>>> results = generateAllTriangulations(0, n - 1);

    cout << "Total distinct triangulations for n = " << n << ": " << results.size() << "\n\n";

    for(size_t idx = 0; idx < results.size(); idx++) {
        cout << "Triangulation #" << idx + 1 << ":\n";
        for(const auto &tri : results[idx]) {
            cout << "  Triangle: (" << tri[0] << ", " << tri[1] << ", " << tri[2] << ")\n";
        }
        cout << "\n";
    }

    return 0;
}