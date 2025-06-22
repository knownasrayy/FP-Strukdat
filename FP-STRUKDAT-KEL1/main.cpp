#include <iostream>
#include <string>
#include <stdexcept>
#include "graph/graph.hpp"
#include "algorithm/dijkstra.hpp"
#include "algorithm/aStar.hpp"
#include "io/csvhandler.hpp"
#include "io/jsonhandler.hpp"
#include "preference/preference.hpp"
#include "utils/logger.hpp"
#include <cstdlib> // Untuk system()

void printPath(const Graph& graph, const std::vector<std::string>& path) {
    std::cout << "\nRecommended Route:\n";
    std::cout << "=================\n";
    for (size_t i = 0; i < path.size(); ++i) {
        const auto& vertex = graph.getVertex(path[i]);
        std::cout << i + 1 << ". " << vertex.getId() << " ";
        if (i < path.size() - 1) {
            std::cout << "-> ";
        }
        if ((i + 1) % 5 == 0) std::cout << "\n";
    }
    std::cout << "\n\n";
}

void printPathDetails(const Graph& graph, const std::vector<std::string>& path) {
    double totalDistance = Dijkstra::getPathDistance(graph, path);
    double totalTime = Dijkstra::getPathTime(graph, path);
    double totalCost = Dijkstra::getPathCost(graph, path);

    std::cout << "Path Details:\n";
    std::cout << "============\n";
    std::cout << "Total Distance: " << totalDistance << " km\n";
    std::cout << "Total Time: " << totalTime << " minutes\n";
    std::cout << "Total Cost: $" << totalCost << "\n\n";
}

void addVertexMenu(Graph& graph) {
    std::string id;
    double x, y;
    std::cout << "Masukkan ID vertex (string): "; std::cin >> id;
    std::cout << "Masukkan koordinat x: "; std::cin >> x;
    std::cout << "Masukkan koordinat y: "; std::cin >> y;
    graph.addVertex(Vertex(id, x, y));
    std::cout << "Vertex berhasil ditambahkan!\n";
}

void editVertexMenu(Graph& graph) {
    std::string id;
    std::cout << "Masukkan ID vertex yang ingin diubah: "; std::cin >> id;
    if (!graph.hasVertex(id)) {
        std::cout << "Vertex tidak ditemukan!\n";
        return;
    }
    double x, y;
    std::cout << "Masukkan koordinat x baru: "; std::cin >> x;
    std::cout << "Masukkan koordinat y baru: "; std::cin >> y;
    graph.removeVertex(id);
    graph.addVertex(Vertex(id, x, y));
    std::cout << "Vertex berhasil diubah!\n";
}

void deleteVertexMenu(Graph& graph) {
    std::string id;
    std::cout << "Masukkan ID vertex yang ingin dihapus: "; std::cin >> id;
    if (!graph.hasVertex(id)) {
        std::cout << "Vertex tidak ditemukan!\n";
        return;
    }
    graph.removeVertex(id);
    std::cout << "Vertex berhasil dihapus!\n";
}

void addEdgeMenu(Graph& graph) {
    std::string from, to;
    double distance, time, cost;
    std::cout << "Masukkan ID asal: "; std::cin >> from;
    std::cout << "Masukkan ID tujuan: "; std::cin >> to;
    std::cout << "Masukkan jarak: "; std::cin >> distance;
    std::cout << "Masukkan waktu: "; std::cin >> time;
    std::cout << "Masukkan biaya: "; std::cin >> cost;
    graph.addEdge(Edge(from, to, distance, time, cost));
    std::cout << "Edge berhasil ditambahkan!\n";
}

void editEdgeMenu(Graph& graph) {
    std::string from, to;
    std::cout << "Masukkan ID asal edge yang ingin diubah: "; std::cin >> from;
    std::cout << "Masukkan ID tujuan edge yang ingin diubah: "; std::cin >> to;
    if (!graph.hasEdge(from, to)) {
        std::cout << "Edge tidak ditemukan!\n";
        return;
    }
    graph.removeEdge(from, to);
    double distance, time, cost;
    std::cout << "Masukkan jarak baru: "; std::cin >> distance;
    std::cout << "Masukkan waktu baru: "; std::cin >> time;
    std::cout << "Masukkan biaya baru: "; std::cin >> cost;
    graph.addEdge(Edge(from, to, distance, time, cost));
    std::cout << "Edge berhasil diubah!\n";
}

void deleteEdgeMenu(Graph& graph) {
    std::string from, to;
    std::cout << "Masukkan ID asal edge yang ingin dihapus: "; std::cin >> from;
    std::cout << "Masukkan ID tujuan edge yang ingin dihapus: "; std::cin >> to;
    if (!graph.hasEdge(from, to)) {
        std::cout << "Edge tidak ditemukan!\n";
        return;
    }
    graph.removeEdge(from, to);
    std::cout << "Edge berhasil dihapus!\n";
}

void showGraphMenu(const Graph& graph) {
    std::cout << "\nDaftar Vertex:\n";
    for (const auto& v : graph.getAllVertices()) {
        std::cout << v.getId() << " (" << v.getLatitude() << ", " << v.getLongitude() << ")\n";
    }
    std::cout << "\nDaftar Edge:\n";
    for (const auto& e : graph.getAllEdges()) {
        std::cout << e.getSource() << " -> " << e.getDestination()
                  << " | Jarak: " << e.getDistance() << " | Waktu: " << e.getTime() << " | Biaya: " << e.getCost() << "\n";
    }
}

void exportGraphToDOT(const Graph& graph, const std::string& filename) {
    std::ofstream ofs(filename);
    ofs << "digraph G {\n";
    // Vertex
    for (const auto& v : graph.getAllVertices()) {
        ofs << "  \"" << v.getId() << "\" [label=\"" << v.getId() << "\n(" << v.getLatitude() << "," << v.getLongitude() << ")\"]\n";
    }
    // Edge
    for (const auto& e : graph.getAllEdges()) {
        ofs << "  \"" << e.getSource() << "\" -> \"" << e.getDestination() << "\" [label=\"Jarak: " << e.getDistance() << "\\nWaktu: " << e.getTime() << "\\nBiaya: " << e.getCost() << "\"]\n";
    }
    ofs << "}\n";
}

void visualizeGraph(const Graph& graph) {
    const std::string dotFile = "graphviz_output.dot";
    const std::string pngFile = "graphviz_output.png";
    exportGraphToDOT(graph, dotFile);
    // Jalankan Graphviz
    std::string cmd = "dot -Tpng " + dotFile + " -o " + pngFile;
    int res = std::system(cmd.c_str());
    if (res == 0) {
        std::cout << "Graph image generated: " << pngFile << "\n";
        // Coba buka gambar (Linux: xdg-open, Windows: start, Mac: open)
        #ifdef __linux__
        std::system(("xdg-open " + pngFile + " &").c_str());
        #elif _WIN32
        std::system(("start " + pngFile).c_str());
        #elif __APPLE__
        std::system(("open " + pngFile).c_str());
        #endif
    } else {
        std::cout << "Gagal menjalankan Graphviz. Pastikan 'dot' sudah terinstall.\n";
    }
}

int main() {
    try {
        Logger::init("app.log");
        Logger::info("Application started");

        // Load graph data
        std::cout << "Loading graph data...\n";
        Graph graph = CSVHandler::loadGraphFromCSV(
            "data/location.csv",
            "data/route.csv"
        );
        Logger::info("Graph data loaded successfully");

        // Load user preferences
        std::cout << "Loading user preferences...\n";
        Preference preferences = JSONHandler::loadPreferencesFromJSON(
            "data/preference.json"
        );
        Logger::info("User preferences loaded successfully");

        // Loop utama aplikasi
        while (true) {
            // CRUD menu
            int menu = -1;
            do {
                std::cout << "\n==== MENU CRUD GRAPH ====\n";
                std::cout << "1. Tampilkan graph\n";
                std::cout << "2. Tambah vertex\n";
                std::cout << "3. Ubah vertex\n";
                std::cout << "4. Hapus vertex\n";
                std::cout << "5. Tambah edge\n";
                std::cout << "6. Ubah edge\n";
                std::cout << "7. Hapus edge\n";
                std::cout << "8. Lanjut ke pencarian rute\n";
                std::cout << "9. Visualisasikan graph\n";
                std::cout << "0. Keluar\n";
                std::cout << "Pilih menu: ";
                std::cin >> menu;
                switch(menu) {
                    case 1: showGraphMenu(graph); break;
                    case 2: addVertexMenu(graph); break;
                    case 3: editVertexMenu(graph); break;
                    case 4: deleteVertexMenu(graph); break;
                    case 5: addEdgeMenu(graph); break;
                    case 6: editEdgeMenu(graph); break;
                    case 7: deleteEdgeMenu(graph); break;
                    case 8: break;
                    case 9: visualizeGraph(graph); break;
                    case 0: std::cout << "Keluar aplikasi.\n"; return 0;
                    default: std::cout << "Menu tidak valid!\n";
                }
            } while(menu != 8);

            // Get user input
            std::string start, goal;
            std::cout << "\nAvailable locations:\n";
            for (const auto& vertex : graph.getAllVertices()) {
                std::cout << vertex.getId() << " ";
            }
            std::cout << "\n\nEnter start location: ";
            std::cin >> start;
            std::cout << "Enter destination: ";
            std::cin >> goal;

            // Find path using both algorithms
            std::cout << "\nFinding optimal route...\n";

            // Using Dijkstra's algorithm
            std::vector<std::string> dijkstraPath = Dijkstra::findShortestPath(
                graph, start, goal, preferences
            );
            std::cout << "\nDijkstra's Algorithm Result:\n";
            printPath(graph, dijkstraPath);
            printPathDetails(graph, dijkstraPath);

            // Using A* algorithm
            std::vector<std::string> aStarPath = AStar::findPath(
                graph, start, goal
            );
            std::cout << "\nA* Algorithm Result:\n";
            printPath(graph, aStarPath);
            printPathDetails(graph, aStarPath);

            // Compare results
            if (dijkstraPath == aStarPath) {
                std::cout << "Both algorithms found the same optimal path!\n";
            } else {
                std::cout << "Algorithms found different paths. "
                         << "This might be due to different heuristics "
                         << "or weighting strategies.\n";
            }

            Logger::info("Path finding completed successfully");
            // Kembali ke menu utama
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        Logger::error(std::string("Application error: ") + e.what());
        return 1;
    }
}