#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>

#define N 5

int menorDistancia(int distancia[], bool visitado[])
{
  int min = INT_MAX;
  int minIndex = -1;

  for (int v = 0; v < N; v++)
  {
    if (!visitado[v] && distancia[v] <= min)
    {
      min = distancia[v];
      minIndex = v;
    }
  }
  return minIndex;
}

void reconstruirCaminho(int anterior[], int destino, char *rotulos[])
{
  if (anterior[destino] == -1)
  {
    printf("%s", rotulos[destino]);
    return;
  }
  reconstruirCaminho(anterior, anterior[destino], rotulos);
  printf(" -> %s", rotulos[destino]);
}

void dijkstra(int grafo[N][N], int origem, int destinoE, int destinoD, char *rotulos[])
{
  int distancia[N];
  bool visitado[N];
  int anterior[N];

  for (int i = 0; i < N; i++)
  {
    distancia[i] = INT_MAX;
    visitado[i] = false;
    anterior[i] = -1;
  }
  distancia[origem] = 0;

  for (int i = 0; i < N - 1; i++)
  {
    int u = menorDistancia(distancia, visitado);
    if (u == -1)
      break;
    visitado[u] = true;

    for (int v = 0; v < N; v++)
    {
      if (grafo[u][v] && !visitado[v] && distancia[u] != INT_MAX && distancia[u] + grafo[u][v] < distancia[v])
      {
        distancia[v] = distancia[u] + grafo[u][v];
        anterior[v] = u;
      }
    }
  }

  if (distancia[destinoE] != INT_MAX)
  {
    printf("1. Menor tempo para chegar de %s até %s: %d horas\n", rotulos[origem], rotulos[destinoE], distancia[destinoE]);
    printf("2. Caminho completo de %s até %s: ", rotulos[origem], rotulos[destinoE]);
    reconstruirCaminho(anterior, destinoE, rotulos);
    printf("\n");
  }
  else
  {
    printf("1. Não há caminho de %s até %s.\n", rotulos[origem], rotulos[destinoE]);
  }

  if (distancia[destinoD] != INT_MAX)
  {
    printf("3. Menor tempo para chegar de %s até %s: %d horas\n", rotulos[origem], rotulos[destinoD], distancia[destinoD]);
    printf("4. Caminho completo de %s até %s: ", rotulos[origem], rotulos[destinoD]);
    reconstruirCaminho(anterior, destinoD, rotulos);
    printf("\n");
  }
  else
  {
    printf("3. Não há caminho de %s até %s.\n", rotulos[origem], rotulos[destinoD]);
  }
}

int main()
{
  int grafo[N][N] = {
      {0, 4, 2, 7, 0}, // A
      {4, 0, 1, 0, 1}, // B
      {2, 1, 0, 3, 3}, // C
      {7, 0, 3, 0, 2}, // D
      {0, 1, 3, 2, 0}  // E
  };

  char *rotulos[N] = {"A", "B", "C", "D", "E"};
  int origem = 0;
  int destinoE = 4;
  int destinoD = 3;

  dijkstra(grafo, origem, destinoE, destinoD, rotulos);

  return 0;
}
