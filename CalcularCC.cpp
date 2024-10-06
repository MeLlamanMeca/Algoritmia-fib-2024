#include <vector>
#include <list>
#include <queue>
using namespace std;

int calcularCC (vector<list<int>> g) {
    vector<bool> visited (g.size(),false);
    queue<int> c;
        
    int cc = 0;

    for (int i = 0; i < g.size(); ++i) {

        if (not visited[i]) {
            ++cc;

            c.push(i);

            while (not c.empty()) {
                int vertex = c.front();
                c.pop();
                visited[vertex] = true;

                list<int>::iterator it = g[vertex].begin();
                while (it != g[vertex].end()) {
                    if (not visited[*it]) c.push(*it);
                }
            }
        }
    }
    return cc;
}