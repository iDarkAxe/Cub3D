/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppontet <ppontet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 09:49:30 by ppontet           #+#    #+#             */
/*   Updated: 2025/11/20 18:37:39 by ppontet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int character);

/**
 * @brief Transform minuscules into majuscules
 *
 * @param character character to check
 * @return character in majuscule if was in minuscule
 * OR character isn´t minuscule
 */
int	ft_toupper(int character)
{
	if (character >= 'a' && character <= 'z')
		return (character - 32);
	return (character);
}
