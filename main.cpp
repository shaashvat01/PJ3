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

int main(int argc, char **argv){
    FILE *fp = NULL;
    int ver1;
    int ver2;
    int returnV;
    char Word[100];
    int numEdge = 0;
    int numVer=0;

    if (argc < 3){
        fprintf(stdout, "Usage: %s <inputfile> <Graphtype> <Flag> \n", argv[0]);
        exit(0);
    }
    fp = fopen(argv[1],"r");
    if(fp)
    {
        int num1 = 0;
        int num2 = 0;
        fscanf(fp, "%d %d", &num1, &num2);
        numVer = num1;
        numEdge = num2;
    }
    
    pEDGE *ADJ = new pEDGE[numVer];
    for (int i = 0; i < numVer; i++) {
        ADJ[i] = NULL; // Allocate memory for each element
    }
    pVertex *vertexList = new pVertex[numVer];
    for(int i=0;i<numVer;i++){
        vertexList[i] = new VERTEX;
        vertexList[i]->id = i+1;
    }
    if(fp){
        string line2;
        int index,u,v;
        double w;
        for(int i = 0; i< numEdge; i++) {
            fscanf(fp, "%d %d %d %lf", &index, &u,&v,&w);
            pEDGE newEdge = (pEDGE)malloc(sizeof(EDGE));
            newEdge->id = index;
            newEdge->start = u;
            newEdge->end = v;
            newEdge->weight = w;

                if(strcmp(argv[2], "DirectedGraph") == 0){
                    //directed
                    if(ADJ[u-1] == NULL){
                        //fprintf(stderr,"I was here ADJ[u] == NULL\n");
                        ADJ[u-1] = newEdge; // add the new edge to the front of the list
                    }
                    else{
                        if(strcmp(argv[3], "1")==0){
                            // directed + flag 1
                                newEdge->next = ADJ[u - 1];
                                ADJ[u - 1] = newEdge; // Update head of the list
                                //fprintf(stderr,"flag 1 not NULL\n");
                        }else{
                            //directed + flag 2
                            pEDGE loop = ADJ[u - 1];
                            while (loop->next != NULL) {
                                loop = loop->next;
                            }
                            loop->next = newEdge; // Add to the rear
                        }
                    }
                }
                else 
                {
                    pEDGE otherEdge = new EDGE;
                    otherEdge->id = index;
                    otherEdge->start = v;
                    otherEdge->end = u;
                    otherEdge->weight = w;

                    if (ADJ[u - 1] == NULL && ADJ[v - 1] == NULL) 
                    {
                    // Both vertices have empty adjacency lists
                    ADJ[u - 1] = newEdge;
                    ADJ[v - 1] = otherEdge;
                    } 
                    else if (ADJ[u - 1] == NULL && ADJ[v - 1] != NULL)
                    {
                        // Vertex u has an empty adjacency list
                        ADJ[u - 1] = newEdge;
                        pEDGE loop2 = ADJ[v-1];
                        // while(loop2->next != NULL)
                        // {
                        //     loop2 = loop2->next;
                        // }
                        // loop2->next = otherEdge;
                        pEDGE temp = ADJ[v - 1];
                        ADJ[v - 1] = otherEdge;
                        otherEdge->next =temp;
                    } 
                    else if (ADJ[u - 1] != NULL && ADJ[v - 1] == NULL) 
                    {
                    // Vertex v has an empty adjacency list
                        ADJ[v - 1] = otherEdge;
                        pEDGE loop = ADJ[u-1];
                        // while(loop->next != NULL)
                        // {
                        //     loop = loop->next;
                        // }
                        // loop->next = newEdge;
                        pEDGE temp = ADJ[u - 1];
                        ADJ[u - 1] = newEdge;
                        newEdge->next = temp;
                    } 
                    else 
                    {
                        // Both vertices have non-empty adjacency lists
                        if (strcmp(argv[3], "1") == 0) 
                        {
                            // Undirected with flag 1
                            newEdge->next = ADJ[u - 1];
                            ADJ[u - 1] = newEdge;

                            otherEdge->next = ADJ[v - 1];
                            ADJ[v - 1] = otherEdge;
                        } 
                        else 
                        {
                            // Undirected with flag 2
                            //fprintf(stdout,"undirected with flag 2\n");
                            pEDGE loop = ADJ[u - 1];
                            while (loop->next != NULL) 
                            {
                                loop = loop->next;
                            }
                            loop->next = newEdge;

                            pEDGE loop2 = ADJ[v - 1];
                            while (loop2->next != NULL) 
                            {
                                loop2 = loop2->next;
                            }
                            loop2->next = otherEdge;
                        }
                    }
                }
    }
    fclose(fp);

    while (1)
    {

        returnV = nextInstruction(Word, &ver1, &ver2);
        //if the funtion returns 0 the instruction is invalid
        if (returnV == 0){
            fprintf(stdout, "Warning: Invalid instruction\n");
            continue;
        }
        // end if STOP is entered
        if (strcmp(Word, "Stop")==0){
            return 0;
        }
        // print command is entered
        if(strcmp(Word, "PrintADJ")==0){
            for(int i =0; i < numVer ; i++){
                fprintf(stdout,"ADJ[%d]:-->[%d %d: %.2f]",i+1,ADJ[i]->start,ADJ[i]->end,ADJ[i]->weight);
                pEDGE loop = ADJ[i]->next;
                while(loop != NULL){
                    fprintf(stdout,"-->[%d %d: %.2f]",loop->start,loop->end,loop->weight);
                    loop = loop->next;
                }
                fprintf(stdout,"\n");
            }
            continue;
        }
        // SinglePair command is entered
        if(strcmp(Word, "SinglePair")==0){
            initSinglePair(vertexList,numVer,ver1,ver2);
            singleSource(vertexList,numVer,ver1,ADJ,ver2);
            continue;
        }

        //SingleSource commanmd is entered
        if(strcmp(Word, "SingleSource")==0){
            initSingleSource(vertexList,numVer,ver1);
            singleSource(vertexList,numVer,ver1,ADJ, 0);
            continue;
        }

        //PrintLength commanmd is entered
        if(strcmp(Word, "PrintLength")==0){
            printlength(ver1,ver2);
            continue;
        }

        if(strcmp(Word, "PrintPath")==0){
            printPath(ver1,ver2);
            continue;
        }
    }
}
}