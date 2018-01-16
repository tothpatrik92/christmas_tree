/*
 * tree.h
 *
 *  Created on: Nov 27, 2017
 *      Author: patrik
 */

#ifndef TREE_H_
#define TREE_H_
#include "config.h"


extern struct M_ELEMENTS tree_matrix;
extern struct M_ELEMENTS sine_matrix;
extern struct M_ELEMENTS fin_matrix;

void init_tree(void);
void create_top(struct M_ELEMENTS *);
void create_mid(struct M_ELEMENTS *);
void create_bot(struct M_ELEMENTS *);
void create_sin(struct M_ELEMENTS *);
void merge(struct M_ELEMENTS *,struct M_ELEMENTS *,struct M_ELEMENTS *);

#endif /* TREE_H_ */
