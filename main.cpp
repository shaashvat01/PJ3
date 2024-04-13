#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "data_structures.h"
#include "graph.h"
#include "heap.h"
#include <iostream>
#include <iomanip>
using namespace std; 


int main(int argc, char **argv)
{
    FILE *fp; //File object
    HEAP *myHEAP; //Heap object

    // user argument
    int num1, num2;
    
    //sample variable for debug
    int v;
    int w;
    int x;
    int y;
    
    //Input variables 
    int numV;
    int numE;
    char Word[100];

    int returnV;

    if (argc < 3){
        fprintf(stderr, "Usage: %s <InputFile> <GraphType> <flag> \n", argv[0]);
        exit(0);
    }

    fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        fprintf(stderr,"File not found\n");
        return 0;
    }

    fscanf(fp, "%d %d", &numV, &numE);

    // Allocate memory for vList and adjList after reading numV and numE
    pVertex* list = new pVertex[numV];
    pEdge* adjList = new pEdge[numV];

    for (int i = 0; i < numV; i++) {
        // Allocate memory for each VERTEX object
        list[i] = new VERTEX;
        list[i]->id = i; // Set the index of the vertex
    }

    // Read the remaining lines
    for (int i =1; i <=numE; ++i) {
        int edgeIndex, u, v;
        double weight;
        fscanf(fp, "%d %d %d %lf", &edgeIndex, &u, &v, &weight);

        // Create a new node for the edge
        pEdge newNode = new EDGE;
        newNode->id = edgeIndex;
        newNode->u = u;
        newNode->v = v;
        newNode->w = weight;
        newNode->next = nullptr;

        // Insert the new node into the appropriate adjacency list based on the flag and graph type
        if (strcmp(argv[2], "DirectedGraph") == 0 || strcmp(argv[2], "UndirectedGraph") == 0) 
        {
            if (strcmp(argv[3], "1") == 0) {
                // Insert at the front of adjList[u]
                newNode->next = adjList[u];
                adjList[u] = newNode;
            }
            if (strcmp(argv[2], "UndirectedGraph") == 0 && strcmp(argv[3], "1") == 0) {
                // Also insert at the front of adjList[v] for undirected graphs
                pEdge newNodeV = new EDGE;
                newNodeV->id = edgeIndex;
                newNodeV->u = v;
                newNodeV->v = u;
                newNodeV->w = weight;
                newNodeV->next = adjList[v];
                adjList[v] = newNodeV;
            }
        } 
        else if (strcmp(argv[3], "2") == 0) 
        {
            if (strcmp(argv[2], "DirectedGraph") == 0 || strcmp(argv[2], "UndirectedGraph") == 0) 
            {
                // Insert at the rear of adjList[u]
                if (!adjList[u]) 
                {
                    adjList[u] = newNode;
                } 
                else 
                {
                    pEdge current = adjList[u];
                    while (current->next) 
                    {
                        current = current->next;
                    }
                    current->next = newNode;
                }
            }
            if (strcmp(argv[2], "UndirectedGraph") == 0 && strcmp(argv[3], "2") == 0) 
            {
                // Also insert at the rear of adjList[v] for undirected graphs
                pEdge newNodeV = new EDGE;
                newNodeV->id = edgeIndex;
                newNodeV->u = v;
                newNodeV->v = u;
                newNodeV->w = weight;
                if (!adjList[v])
                {
                    adjList[v] = newNodeV;
                } 
                else 
                {
                    pEdge current = adjList[v];
                    while (current->next) 
                    {
                        current = current->next;
                    }
                    current->next = newNodeV;
                }
            }
        }
    }

    // Close the file
    fclose(fp);

    while(1)
    {
        returnV = nextInstruction(Word, &num1, &num2);
        if(returnV == 0)
        {
            fprintf(stderr, "Warning: Invalid instruction\n");
            continue;
        }

        if(strcmp(Word, "Stop")==0)
        {
            return 0;
        }

        if (strcmp(Word, "PrintADJ")==0)
        { 
           // Print the adjacency lists
            for (int i = 1; i <= numV; ++i)
            {
                printf("ADJ[%d]:-->", i ); // Print the vertex index as ADJ[i]
                pEdge current = adjList[i];
                while (current != nullptr) {
                    printf("[%d %d: %.2lf]", current->u, current->v, current->w); // Print each node in the adjacency list
                    if (current->next != nullptr) {
                        printf("-->");
                    }
                    current = current->next;
                }
                printf("\n");
            }
            continue;
        }

        if (strcmp(Word, "SingleSource") == 0) 
        {
            cout << "in single source main before." << endl;
            singleSource(list, numV, num1, adjList);
            cout << "in single source main." << endl;
            continue;
        }

        if (strcmp(Word, "SinglePair")==0) 
        {

        }

        if (strcmp(Word, "PrintLength")==0)
        { 

        }

        if (strcmp(Word, "PrintPath")==0)
        { 
            
        }

        return 1;
    }

}