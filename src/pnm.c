/**
 * pnm.c
 *
 * This file contains type definitions and
 * PNM image manipulation functions.
 *
 * @author: Smeers Timothy S200930
 * @date: 23-02-21
 * @project: INFO0030 Project 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "pnm.h"

#define BUFFER_SIZE 1000000
#define CHAR_SIZE 12200
#define COMMENT "#"
#define EXTENSION_PNM ".pnm"
#define EXTENSION_PBM ".pbm"
#define EXTENSION_PGM ".pgm"
#define EXTENSION_PPM ".ppm"
#define MAGIC_NUMBER_1 "P1"
#define MAGIC_NUMBER_2 "P2"
#define MAGIC_NUMBER_3 "P3"
#define MAX_CHARACTER 5

/** prototype */
const char *extension_check(const char p_path[]);
PNM *constructor(PNM *p_image);
PNM *destructor(PNM *p_pnm);
FILE *check_file(char *p_filename);
int read_matrice(unsigned int p_col, unsigned int p_line, FILE *p_file, PNM *p_pnm);

/**
 * @struct PNM_t
 * @brief Definition of the PNM opaque type
 */
struct PNM_t {

	char format[CHAR_SIZE];
	unsigned int line;
	unsigned int column;
	unsigned int color;
	unsigned int **matrix[CHAR_SIZE][CHAR_SIZE];
};

/**
 * @fn	read_matrice(unsigned int,,, PNM)
 * @brief read the line and column of matrix
 * @pre	p_col >= 0 ^ p_line >= 0 ^ p_file != NULL ^ p_pnm != NULL
 * @post &p_pnm->matrix = a matrix comprising the columns and line
 * @param p_col	The number of columns
 * @param p_line The number of lines
 * @param p_file The file read
 * @param p_pnm	The pointer to pnm
 */
int read_matrice(unsigned int p_col, unsigned int p_line, FILE *p_file, PNM *p_pnm) {
	assert(p_col >= 0 && p_line >= 0 && p_file != NULL && p_pnm != NULL);

	char s_tmp[BUFFER_SIZE];
	unsigned int s_position = ftell(p_file);

	fgets(s_tmp, BUFFER_SIZE, p_file);

	if(strstr(s_tmp, COMMENT) != NULL) {
		for(unsigned int i = 0; i < p_line; i++) {
			for(unsigned int j = 0; j < p_col; j++) {
				fscanf(p_file, "%u", &p_pnm->matrix[i][j]);
			}
		}
	}else {
		fseek(p_file, s_position , SEEK_SET);
		for(unsigned int i = 0; i < p_line; i++) {
			for(unsigned int j = 0; j < p_col; j++) {
				fscanf(p_file, "%u", &p_pnm->matrix[i][j]);
			}
		}
	}
}

/**
 * @fn const char extension_check*(const char[])
 * @brief Check the file extension
 * @pre p_path != NULL
 * @post
 * @param p_path the file path
 * @return The file extension
 */
const char *extension_check(const char p_path[]) {
	assert(p_path != NULL);

    const char *s_result;
    unsigned int i;
    unsigned int n;

    n = strlen(p_path);
    i = n - 1;

    while ((i >= 0) && (p_path[i] != '.') && (p_path[i] != '/') && (p_path[i] != '\\')) {
        i--;
    }
    if ((i > 0) && (p_path[i] == '.') && (p_path[i - 1] != '/') && (p_path[i - 1] != '\\')) {
        s_result = p_path + i;
    }else {
        s_result = p_path + n;
    }
    return(s_result);

}

/**
 * @fn FILE check_file*(char*)
 * @brief check if file is oppened correctly
 *
 * @pre p_filename != NULL
 * @post p_filename is opened
 * @param p_filename The path of file
 * @return s_pnmFile
 */
FILE *check_file(char *p_filename) {
   assert(p_filename != NULL);

   FILE *s_pnmFile;
   s_pnmFile = fopen(p_filename, "r");

   if (s_pnmFile == NULL) {
      printf("Error while trying to open file '%s'\n", p_filename);
      return NULL;

   }else {
	   return (s_pnmFile);
   }
}

/**
 * @fn PNM constructor*(PNM*)
 * @brief Allows memory to be allocated for a PNM structure
 * @pre p_image != NULL
 * @post
 * @param p_image The image to be allocated memory
 * @return s_image
 */
PNM *constructor(PNM *p_image) {
	assert(p_image != NULL);

	   PNM *pnm = malloc(sizeof(PNM));

	   if (pnm == NULL){
	      return NULL;
	   }
	   return(pnm);
}

/**
 * @fn PNM destructor*(PNM*)
 * @brief Destructor of memory allocation
 * @pre p_pnm != NULL
 * @post p_pnm = free
 * @param p_pnm The variable to liberate
 * @return
 */
PNM *destructor(PNM *p_pnm) {
	assert(p_pnm != NULL);

	for (unsigned int x = 0; x < p_pnm->line; x++) {
	      free(p_pnm->matrix[x]);
	   }

	free(p_pnm->matrix);
	free(p_pnm);

	return(0);
}

/**
 * @fn int load_pnm(PNM**, char*)
 * @brief
 * @pre
 * @post
 * @param p_image
 * @param p_filename
 * @return
 */
int load_pnm(PNM **p_image, char* p_filename) {
	assert(p_image != NULL && p_filename != NULL);

	PNM *s_pnm = p_image;

	char s_tmp[BUFFER_SIZE];
	unsigned int s_position;


	if(s_pnm == NULL) {
		printf("Error! memory not allocated.\n");
		return(-1);
	}

	FILE *s_file = check_file(p_filename);

	if (s_file == NULL) {
		printf("The file not opened successfully \n");
		fclose(s_file);
		return(-2);
	}

/* Checking the file extension */
	if(!((strcmp(extension_check(p_filename), EXTENSION_PNM) == 0)
		|| (strcmp(extension_check(p_filename), EXTENSION_PBM) == 0)
		|| (strcmp(extension_check(p_filename), EXTENSION_PGM) == 0)
		|| (strcmp(extension_check(p_filename), EXTENSION_PPM) == 0))) {

		printf("\nError the file extension is invalid \n"
				"Your extension is of type: %s \n", extension_check(p_filename));
		fclose(s_file);
		return(-2);
	}

/* Format scan */
	s_position = ftell(s_file);

	fgets(s_tmp, BUFFER_SIZE, s_file);

	if(strstr(s_tmp, COMMENT) != NULL) {
		fscanf(s_file,"%s", &s_pnm->format);
	}else {
		fseek(s_file, s_position , SEEK_SET);
		fscanf(s_file,"%s", &s_pnm->format);
	}

/* Format verification */
	if((strstr(s_pnm->format, MAGIC_NUMBER_1) == NULL)
			&& (strstr(s_pnm->format, MAGIC_NUMBER_2) == NULL)
			&& (strstr(s_pnm->format, MAGIC_NUMBER_3) == NULL)) {
		printf("Error the magic number does not conform \n"
				"Your magic number is: %s \n", s_pnm->format);
		return(-3); // @suppress("Avoid magic numbers") // @suppress("Line comments")
	}

/* Line and column scan */
	fscanf(s_file, "%u %u", &s_pnm->column, &s_pnm->line);
	fgets(s_tmp, BUFFER_SIZE, s_file);

	while(strstr(s_tmp, COMMENT) != NULL){
		fscanf(s_file, "%u %u", &s_pnm->column, &s_pnm->line);
		fgets(s_tmp, BUFFER_SIZE, s_file);
	}

/* Column verification */
	if(s_pnm->column == NULL && s_pnm->column != '0') {
		printf("Error the number of columns is empty \n");
		return(-3); // @suppress("Avoid magic numbers") // @suppress("Line comments")
	}

/* Line verification */
	if(s_pnm->line == NULL && s_pnm->line != '0') {
		printf("Error the number of line is empty \n");
		return(-3); // @suppress("Avoid magic numbers") // @suppress("Line comments")
	}

/* Color scan */
	if((strcmp(s_pnm->format, MAGIC_NUMBER_1)) != 0) {
		fscanf(s_file, "%u", &s_pnm->color);
		fgets(s_tmp, BUFFER_SIZE, s_file);

		while(strstr(s_tmp, COMMENT) != NULL){
			fscanf(s_file, "%u", &s_pnm->color);
			fgets(s_tmp, BUFFER_SIZE, s_file);
		}
	}

/* Color verification */
		if(s_pnm->color == NULL && s_pnm->color != '0') {
			printf("Error the number of color is empty \n");
			return(-3); // @suppress("Avoid magic numbers") // @suppress("Line comments")
		}

		if(s_pnm->color == NULL && s_pnm->color > "255") {
			printf("Error the number of color is out of range \n");
			return(-3); // @suppress("Avoid magic numbers") // @suppress("Line comments")
		}


/* Matrix scan */
	read_matrice(s_pnm->column, s_pnm->line, s_file, s_pnm);

	fclose(s_file);
	p_image = &s_pnm;

	return (0);
}


char *get_format(PNM *image){
  assert (image != NULL);
  return image->format;
}

unsigned int *get_line(PNM *image){
  assert (image != NULL);
  return image->line;
}

unsigned int *get_column(PNM *image){
  assert (image != NULL);
  return image->column;
}

unsigned int *get_color(PNM *image){
  assert (image != NULL);
  return image->color;
}

/**
 * @fn int write_pnm(PNM*, char*)
 * @brief
 * @pre
 * @post
 * @param p_image
 * @param p_filename
 * @return
 */
int write_pnm(PNM *p_image, char* p_filename) {
	assert(p_image != NULL && p_filename != NULL);

	FILE *s_file = fopen(p_filename, "w");

	char s_column[MAX_CHARACTER];
	char s_line[MAX_CHARACTER];
	char s_color[MAX_CHARACTER];

	sprintf(s_column, "%i", get_column(p_image));
	sprintf(s_line, "%i", get_line(p_image));
	sprintf(s_color, "%i", get_color(p_image));

	fputs(get_format(p_image), s_file);
	fputs("\n", s_file);
	fputs(s_column, s_file);
	fputs(" ", s_file);
	fputs(s_line, s_file);
	fputs("\n", s_file);

	if((strcmp(get_format(p_image), MAGIC_NUMBER_2) == 0)
			|| (strcmp(get_format(p_image), MAGIC_NUMBER_3) == 0)) {
		fputs(s_color, s_file);
		fputs("\n", s_file);
	}

	for(unsigned int i = 0; i < p_image->line; i++) {
		if(i!=0)
		fprintf(s_file,"\n");
		for(unsigned int j = 0; j < p_image->column; j++) {
			fscanf(s_file, "%u", &p_image->matrix[i][j]);
			fprintf(s_file, "%d ", p_image->matrix[i][j]);
		}
	}
	free(p_image->matrix);
	fclose(s_file);
	return (0);
}
