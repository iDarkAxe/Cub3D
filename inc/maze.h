/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maze.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 19:23:53 by rdesprez          #+#    #+#             */
/*   Updated: 2025/09/14 21:16:05 by rdesprez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAZE_H
# define MAZE_H

# include "data_structure.h"
# include <stddef.h>

# define MAZE_N 1
# define MAZE_S 2
# define MAZE_E 4
# define MAZE_W 8

/**
 * @brief Maximum random value possible
 */
# define FT_RAND_MAX 32768

/**
 * @brief Minimum maze size
 */
# define MAZE_MIN_SIZE 3

/**
 * @brief Maximum maze size
 */
# define MAZE_MAX_SIZE 1000

typedef struct s_posvec	t_posvec;

/**
 * @brief Vector implementation that stores t_pos2 objects
 */
struct		s_posvec
{
	t_pos2	*data;
	size_t	len;
	size_t	capacity;
};

/**
 * @brief Maze direction on x axis
 * 
 * @param[in] dir direction
 * @return int value considering maze MACROS
 */
int				maze_dir_x(int dir);
/**
 * @brief Maze direction on y axis
 * 
 * @param[in] dir direction
 * @return int value considering maze MACROS
 */
int				maze_dir_y(int dir);
/**
 * @brief Maze inverted direction on x and y axis
 * 
 * @param[in] dir direction
 * @return int value considering maze MACROS
 */
int				maze_dir_opp(int dir);

/**
 * @defgroup Vector Vector implementation with t_pos2
 * @brief Vector functions used to work woth t_pos2
 * @{
 *
 */

/**
 * @brief Create a vector with an initial starting size
 * 
 * @param[in] size initial size
 * @return t_posvec* pointer to the new vector
 */
t_posvec		*posvecnew(size_t size);
/**
 * @brief Add a new element to the vector
 * 
 * @param[in,out] vec vector pointer
 * @param[in] data payload to add
 * @return int 1 OK, 0 otherwise
 */
int				posvecpush(t_posvec *vec, t_pos2 data);
/**
 * @brief Pops the last element of the vector if not empty
 * 
 * @param[in,out] vec vector pointer
 * @param[in,out] pos if non-null, copy the last element to this location
 * @return int 1 OK, 0 otherwise
 */
int				posvecpop(t_posvec *vec, t_pos2 *pos);
/**
 * @brief Removes the element at the specified index from the vector if found
 * 
 * @param[in,out] vec vector pointer
 * @param[in] index index of the element to define
 * @param[in,out] result if non-null, copy the removed element to this location
 * @return int 
 */
int				posvecremove(t_posvec *vec, size_t index,
					t_pos2 *result);
/**
 * @brief Free the vector
 * 
 * @param[in,out] vec vector pointer
 */
void			posvecfree(t_posvec *vec);
/** @} */

/**
 * @defgroup Random Random implementation based on libc
 * @brief Random functions used to generated randomness
 * @{
 *
 */

/**
 * @brief Sets the initial random state from the given seed
 * 
 * @param[in] seed random seed
 */
void			ft_srand(unsigned int seed);
/**
 * @brief Generate a random unsigned int
 * 
 * @return unsigned int number generated
 */
unsigned int	ft_rand(void);
/**
 * @brief Shuffle an array
 * 
 * @param[in,out] arr array to shuffle
 * @param[in] len number of element to shuffle
 */
void			array_shuffle(int *arr, int len);
/**
 * @brief Parse the argument for generation
 *
 * @param[in] gen args to parse
 * @param[out] width width of future maze
 * @param[out] height height of future maze
 * @return int
 */
int				cub_parse_generation_arg(char *gen, size_t *width,
					size_t *height);
/**
 * @brief Allocates a new map with the given dimension
 * 
 * @param[in] dimensions dimensions
 * @return t_map_raoul* new map on success, NULL otherwise
 */
t_map_raoul		*cub_new_map_from_dimensions(char *dimensions);
/**
 * @brief Cub3D Maze Generator, uses dimensions from gen, store them in map and
 * create a random perfect maze
 *
 * @param[in,out] map map structure
 * @return int 1 OK, 0 error
 */
int				cub_growing_tree(t_map_raoul *map);
/** @} */

#endif
