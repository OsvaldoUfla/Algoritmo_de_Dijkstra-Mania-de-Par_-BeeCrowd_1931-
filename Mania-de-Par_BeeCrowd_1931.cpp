#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<functional>
using namespace std;

/*
 * Variaveis globais
 */

// lista de adjacencia
vector<pair<int, double>>* LA;

// numero de vertices do grafo
int n;

// numeor de arestas do grafo
int m;

// distancia da origem "org" a cada vertice do grafo
vector<double> d;

void dijkstra(int org)
{
    d.assign(n, 1.0);
    
    // a distance da origem "org" eh sempre zero
    d[org] = 1.0;
    
    // heap que auxilia na obtencao do vertice com maior prioridade, a cada iteracao
    priority_queue< pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>> > heap;

    // primeiro par inserido na heap: "org" com custo zero
    heap.push(make_pair(1.0, org));
 
    vector<bool> visitado;
    visitado.assign(n, false);
 
    // o algoritmo para quando a heap estiver vazia
    while(!heap.empty())
    {
        pair<double, int> vertice = heap.top();
        heap.pop();

        double distancia = vertice.first;
        int u = vertice.second;
     
        if(visitado[u]) // "u" jah foi explorado
          continue;
     
        visitado[u] = true;
     
        double custo;
        for(int j = 0; j < (int) LA[u].size(); j++)
        {
            pair<int, double> vizinho = LA[u][j];
            int v = vizinho.first;
            double prob = vizinho.second;
         
            // tentativa de melhorar a estimativa de menor caminho da origem ao vertice v
            custo = d[u] * prob;
            if(custo < d[v]) 
            { 
                d[v] = custo; 
                heap.push(make_pair(d[v], v)); 
            }
        }
    }
}

int main()
{
    cin >> n >> m;
   
    LA = new vector<pair<int, double>>[n];
    int u, v;
    double p;
    for(int i = 0; i < m; i++)
    {
        cin >> u >> v; 
        cin >> p;
        u--;
        v--;
        LA[u].push_back(make_pair(v, 1.0 - p/10.0));
    }
 
    for(int i = 0; i < n; i++)
    {
        cout << "vertice " << i << ": ";
        for(int j = 0; j < (int) LA[i].size(); j++)
        {
            cout << "(" << LA[i][j].first << ", " << LA[i][j].second << ") ";
        }
        cout << endl;
    }

    dijkstra(0);
 
    for(int i = 0; i < n; i++)
      cout << "d[" << i + 1 << "]: " << 1.0 - d[i] << endl;

    return 0;
}