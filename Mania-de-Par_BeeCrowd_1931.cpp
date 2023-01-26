#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include<functional>
#include<fstream>
using namespace std;

#define INF 1000000000

/*
 * Variaveis globais
 */

// lista de adjacencia
vector<pair<int, int>>* LA;

// numero de vertices do grafo
int n;

// numeor de arestas do grafo
int m;

// distancia da origem "org" a cada vertice do grafo
vector<int> d;

void dijkstra(int org)
{
    d.assign(n, INF);
    
    // a distance da origem "org" eh sempre zero
    d[org] = 0;
    
    // heap que auxilia na obtencao do vertice com maior prioridade, a cada iteracao
    priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > heap;

    // primeiro par inserido na heap: "org" com distância zero
    heap.push(make_pair(0, org));
 
    vector<bool> visitado;
    visitado.assign(n, false);
 
    // o algoritmo para quando a heap estiver vazia
    while(!heap.empty())
    {
        pair<int, int> vertice = heap.top();
        heap.pop();

        int distancia = vertice.first;
        int u = vertice.second;
     
        if(visitado[u]) // "u" jah foi explorado
          continue;
     
        visitado[u] = true;
     
        int custo;
        for(int j = 0; j < (int) LA[u].size(); j++)
        {
            pair<int, int> vizinho = LA[u][j];
            int v = vizinho.first;
            int prob = vizinho.second;
         
            // tentativa de melhorar a estimativa de menor caminho da origem ao vertice v
            custo = d[u] + prob;
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
    ifstream arquivo("02.in");
    if(arquivo){
        arquivo >> n >> m;
    
        LA = new vector<pair<int, int>>[n];
        int u, v;
        int p;
        for(int i = 0; i < m; i++)
        {
            arquivo >> u >> v; 
            arquivo >> p;
            u--;
            v--;
            LA[u].push_back(make_pair(v, p));
        }
        /*
        for(int i = 0; i < n; i++)
        {
            cout << "vertice " << i+1 << ": ";
            for(int j = 0; j < (int) LA[i].size(); j++)
            {
                cout << "(" << LA[i][j].first +1 << ", " << LA[i][j].second << ") ";
            }
            cout << endl;
        }
        */

        dijkstra(0);
    
        for(int i = 0; i < n; i++)
        cout << "d[" << i + 1 << "]: " << d[i] << endl;
    }
    else
        cout << "Erro ao abrir o arquivo" << endl;

    return 0;
}