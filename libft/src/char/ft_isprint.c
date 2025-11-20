/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:32:05 by ppontet           #+#    #+#             */
/*   Updated: 2025/11/20 19:49:12 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int character);

// could return 16384 or 0x10000000000000 instead of 1
/**
 * @brief Check if arg is in ascii table and printable
 *
 * @param character character to check
 * @return int 0 not in ascii table, anything else if in ascii table
 */
int	ft_isprint(int character)
{
	if (character >= 32 && character <= 126)
		return (1);
	return (0);
}
