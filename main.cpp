#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "util.h"
#include "heap.h"
#include "graph.h"
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
        fprintf(stderr, "Usage: %s <inputfile> <Graphtype> <Flag> \n", argv[0]);
        exit(0);
    }
    fp = fopen(argv[1],"r");
    ifstream file(argv[1]);
    if(fp){
        string line;
        int num1,num2;
        getline(file, line) ;
            istringstream iss(line);
                if (iss >> num1 >> num2) {
                    numEdge = num2;
                    numVer = num1;
                }
    }
    fclose(fp);

    fp = fopen(argv[1],"r");
    pNODE *ADJ = new pNODE[numVer];
    for (int i = 0; i < numVer; i++) {
        ADJ[i] = NULL; // Allocate memory for each element
    }
    pVERTEX *vertexList = new pVERTEX[numVer];
    for(int i=0;i<numVer;i++){
        vertexList[i] = new VERTEX;
        vertexList[i]->id = i+1;
    }
    if(fp){
        string line2;
        int index,u,v;
        double w;
        while (getline(file, line2)) {
            istringstream iss(line2);
            iss >> index >> u >> v >> w;
            pNODE newEdge = new NODE;
            newEdge->index = index;
            newEdge->u = u;
            newEdge->v = v;
            newEdge->w = w;

                if(strcmp(argv[2], "DirectedGraph") == 0){
                    //directed
                    if(ADJ[u-1] == NULL){
                        //fprintf(stderr,"I was here ADJ[u] == NULL\n");
                        ADJ[u-1] = newEdge; // add the new edge to the front of the list
                    }else{
                        if(strcmp(argv[3], "1")==0){
                            // directed + flag 1
                                newEdge->next = ADJ[u - 1];
                                ADJ[u - 1] = newEdge; // Update head of the list
                                //fprintf(stderr,"flag 1 not NULL\n");
                        }else{
                            //directed + flag 2
                            pNODE loop = ADJ[u - 1];
                            while (loop->next != NULL) {
                                loop = loop->next;
                            }
                            loop->next = newEdge; // Add to the rear
                        }
                    }
                }else {
                    pNODE otherEdge = new NODE;
                    otherEdge->index = index;
                    otherEdge->v = u;
                    otherEdge->u = v;
                    otherEdge->w = w;

                    if (ADJ[u - 1] == NULL && ADJ[v - 1] == NULL) {
                    // Both vertices have empty adjacency lists
                    ADJ[u - 1] = newEdge;
                    ADJ[v - 1] = otherEdge;
                    } else if (ADJ[u - 1] == NULL && ADJ[v - 1] != NULL) {
                    // Vertex u has an empty adjacency list
                    ADJ[u - 1] = newEdge;
                    pNODE loop2 = ADJ[v - 1];
                        while (loop2->next != NULL) {
                            loop2 = loop2->next;
                        }
                        loop2->next = otherEdge;
                } else if (ADJ[u - 1] != NULL && ADJ[v - 1] == NULL) {
                // Vertex v has an empty adjacency list
                    ADJ[v - 1] = otherEdge;
                    pNODE loop = ADJ[u - 1];
                        while (loop->next != NULL) {
                           loop = loop->next;
                        }
                        loop->next = newEdge;
                } else {
                    // Both vertices have non-empty adjacency lists
                    if (strcmp(argv[3], "1") == 0) {
                        // Undirected with flag 1
                        newEdge->next = ADJ[u - 1];
                        ADJ[u - 1] = newEdge;

                        otherEdge->next = ADJ[v - 1];
                        ADJ[v - 1] = otherEdge;
                    } else {
                        // Undirected with flag 2
                        pNODE loop = ADJ[u - 1];
                        while (loop->next != NULL) {
                           loop = loop->next;
                        }
                        loop->next = newEdge;

                        pNODE loop2 = ADJ[v - 1];
                        while (loop2->next != NULL) {
                            loop2 = loop2->next;
                        }
                        loop2->next = otherEdge;
                    }
                }
            }
    }
    fclose(fp);

    while (1){

        returnV = nextInstruction(Word, &ver1, &ver2);
        //if the funtion returns 0 the instruction is invalid
        if (returnV == 0){
            fprintf(stderr, "Warning: Invalid instruction\n");
            continue;
        }
        // end if STOP is entered
        if (strcmp(Word, "Stop")==0){
            return 0;
        }
        // print command is entered
        if(strcmp(Word, "PrintADJ")==0){
            for(int i =0; i < numVer ; i++){
                fprintf(stderr,"ADJ[%d]:-->[%d %d: %f]",i+1,ADJ[i]->u,ADJ[i]->v,ADJ[i]->w);
                pNODE loop = ADJ[i]->next;
                while(loop != NULL){
                    fprintf(stderr,"-->[%d %d: %f]",loop->u,loop->v,loop->w);
                    loop = loop->next;
                }
                fprintf(stderr,"\n");
            }

            continue;
        }
        // SinglePair command is entered
        if(strcmp(Word, "SinglePair")==0){
            continue;
        }

        //SingleSource commanmd is entered
        if(strcmp(Word, "SingleSource")==0){
            initSingleSource(vertexList,numVer,ver1);
            dijkistra(vertexList,numVer,ver1,ADJ);//pNODE to arrayS
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