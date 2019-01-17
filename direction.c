/*
 * =====================================================================================
 *
 *       Filename:  direction.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  17/01/2019 13:19:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonathan Matthews
 *	    Email:  jonathanpetermatthews@protonmail.com
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

size_t size = 1;
size_t * map = NULL;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  remap
 *  Description:  
 * =====================================================================================
 */
size_t * remap (size_t * map)
{
	size = size + 2;
	size_t * new_map = calloc(size * size, sizeof(size_t));
	size_t y = 1;
	while (y < size - 1) {
		size_t x = 1;
		while (x < size - 1) {
			*(new_map + (y * size) + x) = *(map + ((y - 1) * (size - 2)) + (x - 1));
			x++;
		}
		y++;
	}
	return new_map;
}		/* -----  end of function remap  ----- */

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
int main ( int argc, char *argv[] )
{
	if (argc != 2) {
		return 1;
	}
	size_t input_length = strlen(argv[1]) + 1;
	char input[input_length];
	strncpy(input, argv[1], input_length);
	map = calloc(size, sizeof(size_t));
	size_t i = 0;
	map[0] = 1;
	size_t current_x_pos = 0;
	size_t current_y_pos = 0;
	while (i < input_length - 1) {
		if (input[i] == '>') {
			if (current_x_pos + 1 >= size) {
				size_t * old_map = map;
				map = remap(old_map);
				free(old_map);
				current_y_pos++;
				current_x_pos = size - 2;
			}
			current_x_pos++;
			*(map + (current_y_pos * size) + current_x_pos) = 1;
		}
		else if (input[i] == 'v') {
			if (current_y_pos + 1 >= size) {
				size_t * old_map = map;
				map  = remap(old_map);
				free(old_map);
				current_x_pos++;
				current_y_pos = size - 2;
			}
			current_y_pos++;
			*(map + (current_y_pos * size) + current_x_pos) = 1;
		}
		else if (input[i] == '<') {
			if (current_x_pos <= 0) {
				size_t * old_map = map;
				map = remap(old_map);
				free(old_map);
				current_y_pos++;
				current_x_pos = 1;
			}
			current_x_pos--;
			*(map + (current_y_pos * size) + current_x_pos) = 1;
		}
		else {
			if (current_y_pos  <= 0) {
				size_t * old_map = map;
				map = remap(old_map);
				free(old_map);
				current_x_pos++;
				current_y_pos = 1;
			}
			current_y_pos--;
			*(map + (current_y_pos * size) + current_x_pos) = 1;
		}
		i++;
	}
	i = 0;
	size_t houses = 0;
	while (i < (size * size)) {
		if (*(map + i) == 1) {
			houses++;
		}
		i++;
	}
	free(map);
	printf("%zu \n", houses);
	return 0;
}				/* ----------  end of function main  ---------- */
