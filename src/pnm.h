/**
 * pnm.h
 *
 * This file contains type declarations and prototypes
 * functions for handling PNM images.
 *
 * @author: Smeers Timothy S200930
 * @date: 23-02-21
 * @project: INFO0030 Project 1
 */

/*
 * Include guard (to avoid problems of multiple inclusions
 * Good practice: always frame a header with an include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * PNM Opaque Type Declaration
 *
 */
typedef struct PNM_t PNM;

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
static int read_matrice(unsigned int p_col, unsigned int p_line, FILE *p_file, PNM *p_pnm);

/**
 * @fn const char extension_check*(const char[])
 * @brief Check the file extension
 * @pre p_path != NULL
 * @post
 * @param p_path the file path
 * @return The file extension
 */
static const char *extension_check(const char p_path[]);

/**
 * @fn PNM destructor*(PNM*)
 * @brief Destructor of memory allocation
 * @pre p_pnm != NULL
 * @post p_pnm = free
 * @param p_pnm The variable to liberate
 * @return
 */
PNM *destructor(PNM *p_pnm);

/**
 * @fn PNM create_pnm*(PNM*)
 * @brief Allows memory to be allocated for a PNM structure
 * @pre p_image != NULL
 * @post
 * @param p_image The image to be allocated memory
 * @return s_image
 */
PNM *constructor(PNM *p_image);

/**
 * load_pnm
 *
 * Charge une image PNM depuis un fichier.
 *
 * @param p_image l'adresse d'un pointeur sur PNM à laquelle �crire l'adresse
 *              de l'image charg�e.
 * @param p_filename le chemin vers le fichier contenant l'image.
 *
 * @pre: p_image != NULL, p_filename != NULL
 * @post: p_image pointe vers l'image charg�e depuis le fichier.
 *
 * @return:
 *     0 Succ�s
 *    -1 Erreur de l'allocation de m�moire
 *    -2 Nom du fichier malform�e
 *    -3 Contenu du fichier malform�e
 *
 */
int load_pnm(PNM **p_image, char* p_filename);

/**
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0 Succ�s
 *    -1 Nom du fichier malform�
 *    -2 Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *p_image, char* p_filename);

#endif __PNM__

