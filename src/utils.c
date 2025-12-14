/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchernia <tchernia@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 14:01:22 by tchernia          #+#    #+#             */
/*   Updated: 2025/12/14 14:01:23 by tchernia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_error(const char *msg)
{
	ssize_t	err;

	ft_putendl_fd("Error", 2);
	err = write(2, msg, ft_strlen(msg));
	if (err < 0)
		return ;
	err = write(2, "\n", 1);
	if (err < 0)
		return ;
}

int	free_arrays(t_objects *obj, t_light *arr)
{
	free(obj->sps);
	free(obj->pls);
	free(obj->cys);
	free(arr);
	return (1);
}

void	handle_esc(mlx_key_data_t key_info, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (key_info.key == MLX_KEY_ESCAPE && key_info.action == MLX_PRESS)
		mlx_close_window(mlx);
}

void	*growing_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = ft_calloc(1, new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, old_ptr, old_size);
	return (new_ptr);
}
