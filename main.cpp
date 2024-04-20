// Name: Shaashvat Mittal
// ASUID: 1224208336
// Description: main.cpp conatins the entier program execution. All the input values are being 
// called to their respective functions in mai only.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "util.h"
#include "heap.h"
#include "graph.h"
#include "math.h"
using namespace std;

int main(int argc, char **argv)
{
    // declaring variables
    int ver1;
    int ver2;
    int returnV;
    char Word[50];
    int numEdge = 0;
    int numVer=0;
    FILE *fp = NULL; // file operation - read and write

    // check for the arguments.
    if (argc < 3){
        fprintf(stdout, "Usage: %s <inputfile> <Graphtype> <Flag> \n", argv[0]);
        exit(0);
    }

    // check for the validity of the flags.
    if(strcmp(argv[3], "1")!=0 && strcmp(argv[3], "2")!=0)
    {
        exit(0);
    }

    // open the input file.
    fp = fopen(argv[1],"r");
    // if fp is open or file pointer is not null.
    if(fp)
    {
        // read number of vertices and edges from the file.
        fscanf(fp, "%d %d", &numVer, &numEdge); 
    }
    
    // allocating memory for adjacency list.
    pEDGE *ADJ = new pEDGE[numVer];
    for (int i = 0; i < numVer; i++) 
    {
        ADJ[i] = NULL;  // initialize each and every pointer to null.
    }
    // allocating memory for vertex list.
    pVertex *vertexList = new pVertex[numVer];
    // iterating through each vertex.
    for(int i=0;i<numVer;i++)
    {
        // allocating memory for vertex and setting id
        vertexList[i] = new VERTEX;
        vertexList[i]->id = i+1;
    }

    // is file read is correct and is not null
    if(fp)
    {
        int index; // for id
        int u; // start
        int v; // end
        double w; // weight
        // iterating thorugh each edge of the graph
        for(int i = 0; i< numEdge; i++) 
        {
            // read edge data from file and allocate memory.
            fscanf(fp, "%d %d %d %lf", &index, &u,&v,&w);
            pEDGE startEdge = (pEDGE)malloc(sizeof(EDGE));
            // set as required.
            startEdge->id = index;
            startEdge->start = u;
            startEdge->end = v;
            startEdge->weight = w;

                // adding the edge to the adjcency list accoring to the graph and type of flag.
                if(strcmp(argv[2], "DirectedGraph") == 0)
                {
                    // Directed graph
                    // if list is empty then add new edge to the frot of the list.
                    if(ADJ[u-1] == NULL)
                    {
                        ADJ[u-1] = startEdge;
                    }
                    // if list is not empty, check for the flags.
                    else
                    {
                        // if flag = 1
                        if(strcmp(argv[3], "1")==0)
                        {
                            // set pointer and update head of the list.
                            startEdge->next = ADJ[u - 1];
                            ADJ[u - 1] = startEdge; 
                        }
                        //if flag = 2
                        if(strcmp(argv[3], "2")==0)
                        {
                            // iterate to the end of the list and add at the last.
                            pEDGE loop = ADJ[u - 1];
                            while (loop->next != NULL) 
                            {
                                loop = loop->next;
                            }
                            // adding to the last of the list or from behind.
                            loop->next = startEdge;
                        }
                    }
                }
                // if graph i snot directed ie it is undirected.
                else
                {
                    // allocate memory for new edge and set accordingly.
                    pEDGE endEdge = (pEDGE)malloc(sizeof(EDGE));
                    endEdge->id = index;
                    endEdge->start = v;
                    endEdge->end = u;
                    endEdge->weight = w;
                    
                    // adding edges based on the cases.
                    // if both the vertex have empty adjcency list then add the new vertex at start and other at last.
                    if (ADJ[u - 1] == NULL && ADJ[v - 1] == NULL) 
                    {
                        ADJ[u - 1] = startEdge;
                        ADJ[v - 1] = endEdge;
                    } 
                    // if start vertex has empty adjacency list.
                    else if (ADJ[u - 1] == NULL && ADJ[v - 1] != NULL)
                    {
                        // add new edge to the start.
                        ADJ[u - 1] = startEdge;
                        pEDGE loop2 = ADJ[v-1];

                        // if flag is 2 
                        if(strcmp(argv[3], "2"))
                        {
                            pEDGE temp = ADJ[v - 1];
                            ADJ[v - 1] = endEdge;
                            endEdge->next =temp;
                        }
                        // if flag is 1.
                        if(strcmp(argv[3], "1"))
                        {
                            while(loop2->next != NULL)
                            {
                                loop2 = loop2->next;
                            }
                            loop2->next = endEdge;
                        }
                    } 
                    // if only end vertex has adjacency list.
                    else if (ADJ[u - 1] != NULL && ADJ[v - 1] == NULL) 
                    {
                        // add end vertex(otheredge) to the end
                        ADJ[v - 1] = endEdge;
                        pEDGE loop = ADJ[u-1];
                        // if flag is 2
                        if(strcmp(argv[3], "2"))
                        {
                            pEDGE temp = ADJ[u - 1];
                            ADJ[u - 1] = startEdge;
                            startEdge->next = temp;
                        }
                        // if flag is 1
                        if(strcmp(argv[3], "1"))
                        {
                            while(loop->next != NULL)
                            {
                                loop = loop->next;
                            }
                            loop->next = startEdge;
                        }
                    } 
                    // if both the vertices has non-empty adjacency list.
                    else 
                    {
                        // if flag is 1 - undirected graph
                        if (strcmp(argv[3], "1") == 0) 
                        {
                            // next pointer of start edge to the start vertex
                            startEdge->next = ADJ[u - 1];
                            ADJ[u - 1] = startEdge;

                            // next pointer of last edge to the last vertex.
                            endEdge->next = ADJ[v - 1];
                            ADJ[v - 1] = endEdge;
                        } 
                        // if flag is 2 - undirected.
                        else 
                        {
                            // add start edge to the end of the list.
                            pEDGE loop = ADJ[u - 1];
                            while (loop->next != NULL) 
                            {
                                loop = loop->next;
                            }
                            loop->next = startEdge;

                            // add last edge to the end of the list.
                            pEDGE loop2 = ADJ[v - 1];
                            while (loop2->next != NULL) 
                            {
                                loop2 = loop2->next;
                            }
                            loop2->next = endEdge;
                        }
                    }
                }
    }
    // close file
    fclose(fp); 

    // processing commands
    while (1)
    {
        // next instruction from the user.
        returnV = nextInstruction(Word, &ver1, &ver2);

        // cehcking if function is valid or not.
        if (returnV == 0)
        {
            fprintf(stdout, "Warning: Invalid instruction\n");
            continue;
        }

        // Stop command is entered - terminate.
        if (strcmp(Word, "Stop")==0)
        {
            return 0;
        }

        // User entered PrintADJ
        if(strcmp(Word, "PrintADJ")==0)
        {
            // Prnt the adjacency list.
            for(int i =0; i < numVer ; i++)
            {
                fprintf(stdout,"ADJ[%d]:-->[%d %d: %.2f]",i+1,ADJ[i]->start,ADJ[i]->end,ADJ[i]->weight);
                pEDGE loop = ADJ[i]->next;
                while(loop != NULL)
                {
                    fprintf(stdout,"-->[%d %d: %.2f]",loop->start,loop->end,loop->weight);
                    loop = loop->next;
                }
                fprintf(stdout,"\n");
            }
            continue;
        }

        // User entered Single Source
        if(strcmp(Word, "SingleSource")==0)
        {
            // calling relevant functions.
            initSingleSource(vertexList,numVer,ver1);
            singleSource(vertexList,numVer,ver1,ADJ, 0);
            continue;
        }

        // User entered SinglePair
        if(strcmp(Word, "SinglePair")==0)
        {
            // Calling relevant functions.
            initSinglePair(vertexList,numVer,ver1,ver2);
            singleSource(vertexList,numVer,ver1,ADJ,ver2);
            continue;
        }

        // User entered Print Length
        if(strcmp(Word, "PrintLength")==0)
        {
            // Calling relevant functions.
            printlength(ver1,ver2);
            continue;
        }

        // User entered PrintPath.
        if(strcmp(Word, "PrintPath")==0)
        {
            // check is source and target are not equal to 0
            if(recent_source != 0 || recent_destination != 0)
            {
                // if source is correct
                if(recent_source == ver1)
                {
                    // call relevant function.
                    printPath(ver1,ver2);
                    continue;
                }
            }
        }
    }
}
}