/**
 * main.c
 *
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Smeers Timothy S200930
 * @date: 23-02-21
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "pnm.h"

int main(int argc, char *argv[]) {

	char *optstring = "f:i:o";

	int s_val;

	PNM *s_image = (PNM *) malloc(sizeof(PNM));

	if (s_image == NULL){
		return NULL;
	}

	while((s_val = getopt(argc, argv, optstring)) != EOF){
		switch(s_val){
		case 'f':
			printf("format = %s", optarg);
			break;
		case 'i':
			load_pnm(constructor(s_image), optarg);break;
		case 'o':
			if(strstr(optarg, (':' || '*' || '?' || '"' || '>' || '<')) != NULL){
				printf("Forbidden character error \n");
				return(-1);
			}
			write_pnm(s_image, optarg);
			destructor(s_image);
			break;
		default:
			break;
		}
		return(0);
	}
  }
