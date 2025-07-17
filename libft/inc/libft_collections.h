/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_collections.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:25:12 by ppontet           #+#    #+#             */
/*   Updated: 2025/07/17 13:24:03 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_COLLECTIONS_H
# define LIBFT_COLLECTIONS_H

# include <stddef.h>

/**
 * @defgroup Vector Vector functions
 * @brief Vector functions
 * @{
 */

/**
 * A wrapper around a dynamic-size list
 */
typedef struct s_ptrvec
{
	void	**data;
	size_t	len;
	size_t	capacity;
}	t_ptrvec;

/**
 * Creates a new ptrvec with a starting capacity.
 * @param size The starting capacity.
 * @returns A new ptrvec, or NULL if allocation failed.
 */
t_ptrvec	*ptrvecnew(size_t size);

/**
 * Pushes a new value onto the ptrvec. If the ptrvec is full, the capacity
 * will be doubled, then the value will be inserted.
 * @param vec The ptrvec to push the new value onto.
 * @param data The new value to push to the ptrvec
 * @returns 1 if he value was added successfully, 0 otherwise.
 */
int			ptrvecpush(t_ptrvec *vec, void *data);

/**
 * Removes and returns the last value in the ptrvec.
 * @param vec The ptrvec to pop the last value from.
 * @returns The ptrvec's last value, or NULL if the ptrvec is empty.
 */
void		*ptrvecpop(t_ptrvec *vec);

/**
 * Frees a given ptrvec and calls a free function on every element.
 * @param vec The ptrvec to free.
 * @param free_fn The function called on every element to free.
 */
void		ptrvecfree(t_ptrvec *vec, void (*free_fn)(void *));

/** @} */

#endif
