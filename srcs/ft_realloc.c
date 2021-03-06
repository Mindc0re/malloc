/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:13:46 by sgaudin           #+#    #+#             */
/*   Updated: 2018/11/29 16:13:48 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*create_empty_block(t_head *ptr_head, size_t size)
{
	t_head *tmp_next;
	t_head *new_block;

	ptr_head->size = size;
	tmp_next = ptr_head->next;
	new_block = (void *)(&ptr_head->mem + size);
	new_block->size = ptr_head->sp_before_n - HEAD_SIZE;
	new_block->status = FREE;
	new_block->sp_before_n = ptr_head->sp_before_n -
							(new_block->size + HEAD_SIZE);
	new_block->mem = new_block + HEAD_SIZE;
	new_block->next = tmp_next;
	ptr_head->next = new_block;
	return (ptr_head->mem);
}

void		*move_alloc(void *ptr, size_t asked_size, size_t ptr_size)
{
	void	*new_ptr;
	size_t	cpy_size;

	cpy_size = asked_size > ptr_size ? ptr_size : asked_size;
	new_ptr = malloc(asked_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, cpy_size);
	free(ptr);
	return (new_ptr);
}

void		*merge_blocks(t_head *ptr_head, size_t size)
{
	size_t tmp_size;
	t_head *new;
	t_head *tmp_next;

	tmp_size = ptr_head->size + ptr_head->sp_before_n +
				ptr_head->next->size + ptr_head->next->sp_before_n;
	ptr_head->size = size;
	ptr_head->sp_before_n = 0;
	tmp_next = ptr_head->next->next;
	if (((tmp_size - size) + HEAD_SIZE) > HEAD_SIZE)
	{
		new = ptr_head->mem + size;
		new->status = FREE;
		new->size = tmp_size - size;
		new->sp_before_n = 0;
		new->mem = ptr_head->mem + size + HEAD_SIZE;
		new->next = ptr_head->next->next;
		ptr_head->next = new;
		ptr_head->next->next = tmp_next;
	}
	else
		ptr_head->next = ptr_head->next->next;
	return (ptr_head->mem);
}

void		*merge_or_new(t_head *ptr_head, size_t size)
{
	if (ptr_head->next && ptr_head->next->status == FREE &&
		(ptr_head->next->size + ptr_head->next->sp_before_n +
			ptr_head->size + ptr_head->sp_before_n) >= size)
		return (merge_blocks(ptr_head, size));
	else
		return (move_alloc(ptr_head->mem, size, ptr_head->size));
}

void		*realloc(void *ptr, size_t size)
{
	t_head	*ptr_head;
	t_map	*z_ptr;

	pthread_mutex_lock(&g_mutex);
	size = ((size - 1) + 4) - ((size - 1) % 4);
	if (ptr == NULL)
		return (malloc(size));
	if (size <= 0)
	{
		free(ptr);
		return (NULL);
	}
	ptr_head = ptr - HEAD_SIZE;
	if (!(z_ptr = which_zone(ptr_head)))
		return (NULL);
	if (z_ptr->type == LARGE)
		return (move_alloc(ptr, size, ptr_head->size));
	else if (ptr_head->size == size)
		return (ptr);
	else if (ptr_head->size > size && (ptr_head->size - size) > (HEAD_SIZE + 1))
		return (create_empty_block(ptr_head, size));
	else
		return (merge_or_new(ptr_head, size));
	pthread_mutex_unlock(&g_mutex);
	return (NULL);
}
