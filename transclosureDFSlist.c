/*********************************************************
 * File        : list.c
 * Borce Gjorgjievski
 * Homework 9: Transitive Closure with Adjacency list representation
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>

#define MAX_V 50
#define UNSEEN 0

struct node{
  int v;
  struct node* next;
};

int V = 0;
int E = 0;
int val[MAX_V];
int id = 0;
// an array of linked lists
struct node* adj[MAX_V];

void createAdjList()
{
  int j, x, y;
  struct node *t, *s;

  //init array
  for(j = 1; j <= V; j++) adj[j] = NULL;

  for(j = 1; j <= E; j++){
    printf("Enter 2 nodes for %d. edge: ", j);
    scanf("%d %d", &x, &y);

    // add node x to adj list of y
    t = (struct node *) malloc(sizeof(struct node));
    t->v = x;
    t->next = adj[y];
    adj[y] = t;

    // add node y to adj list of x
    t = (struct node *) malloc(sizeof(struct node));
    t->v = y;
    t->next = adj[x];
    adj[x] = t;
  }
}

//print all edges
void printAllEdges()
{
  struct node* t; 
  int j;

  for(j = 1; j <= V; j++)
    for(t = adj[j]; t != NULL; t = t->next)
      printf("%d --> %d\n",j, t->v);
}

//print linked nodes
void printNodes(int k)
{
  struct node* t;

  printf("Node %d\n", k);
  val[k] = ++id;
  
  for(t = adj[k]; t != NULL; t = t->next)
    if(val[t->v] == UNSEEN)
      printNodes(t->v);
}

//print all nodes in adj list
void printAllNodes()
{
  int k;

  for(k = 1; k <= V; k++)
    val[k] = UNSEEN;

  for(k = 1; k <= V; k++)
    if(val[k] == UNSEEN)
      printNodes(k);
}

void addEdge(int x, int y) {
  struct node *t, *s;

  //check if the edge exists
  s = adj[x];
  while (s != NULL) {
    if (s->v == y) return; //the edge already exists (non directed graphs)
    s=s->next;
  }

// add node x to adj list of y
t = (struct node *) malloc(sizeof(struct node));
t->v = x;
t->next = adj[y];
adj[y] = t;

// add node y to adj list of x
t = (struct node *) malloc(sizeof(struct node));
t->v = y;
t->next = adj[x];
adj[x] = t;
}

void visit(int k) {
  struct node *t;

  val[k] = ++id;
  for(t = adj[k]; t!=NULL; t=t->next)
    if (val[t->v] == UNSEEN)
      visit(t->v);
}

int DFS(int x, int y) {
  int k;

  id = 0;
  for (k=1; k<=V; k++) val[k] = UNSEEN;
  visit(x);
  if (val[y] != UNSEEN) return 1;
  else return 0;
}

transClosure(){
  int i,j;

  for (i=1; i<=V; i++)
    for(j=i+1; j<=V; j++)
      if(DFS(i,j)==1) //if there's a path from i to j (i is root) 
	addEdge(i,j); //add edge i to j (if already exists, just return)
}

int main()
{
  int v1, v2;

  printf("Enter the number of nodes and edges: ");
  scanf("%d %d", &V, &E);
  createAdjList();
  printf("Printing all nodes:\n");
  printf("---------------------\n");  
  printAllNodes();
  printf("Printing all edges (directional):\n"); 
  printf("-----------------------------\n");
  printAllEdges();
  printf("\nCalculating transitive closure ...\n");
  transClosure();
  printf("Printing all edges (directional):\n"); 
  printf("-----------------------------\n");
  printAllEdges();
}
