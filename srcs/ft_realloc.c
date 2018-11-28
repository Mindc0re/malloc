#include "malloc.h"

void	*create_empty_block(t_head *ptr_head, size_t size)
{
	t_head *tmp_next;
	t_head *new_block;

	ptr_head->size = size;
	tmp_next = ptr_head->next;
	new_block = (t_head *)(ptr_head->mem + ptr_head->size);
	new_block->size = ptr_head->spaceBeforeNext - HEAD_SIZE;
	new_block->status = FREE;
	new_block->spaceBeforeNext = ptr_head->spaceBeforeNext - (new_block->size + HEAD_SIZE);
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
	new_ptr = ft_malloc(asked_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, cpy_size);
	ft_free(ptr);
	return (new_ptr);
}

void		*merge_blocks(t_head *ptr_head, size_t size)
{
	size_t tmp_size;
	t_head *new;
	t_head *tmp_next;

	tmp_size = ptr_head->size + ptr_head->spaceBeforeNext +
				ptr_head->next->size + ptr_head->next->spaceBeforeNext;
	ptr_head->size = size;
	ptr_head->spaceBeforeNext = 0;
	tmp_next = ptr_head->next->next;
	if (((tmp_size - size) + HEAD_SIZE) > HEAD_SIZE)
	{
		new = ptr_head->mem + size;
		new->status = FREE;
		new->size = tmp_size - size;
		new->spaceBeforeNext = 0;
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
		(ptr_head->next->size + ptr_head->next->spaceBeforeNext + 
			ptr_head->size + ptr_head->spaceBeforeNext) >= size)
		return (merge_blocks(ptr_head, size));
	else
		return (move_alloc(ptr_head->mem, size, ptr_head->size));
}

void		*ft_realloc(void *ptr, size_t size)
{
	t_head	*ptr_head;
	t_map 	*z_ptr;

	if (!ptr)
		return (NULL);
	if (size <= 0)
		return (ptr);
	ptr_head = ptr - HEAD_SIZE;
	z_ptr = which_zone(ptr_head);
	if (!z_ptr)
		return (NULL);
	if (z_ptr->type == LARGE)
		return (move_alloc(ptr, size, ptr_head->size));
	else if (ptr_head->size == size)
		return (ptr);
	else if (ptr_head->size > size && (ptr_head->size - size) > (HEAD_SIZE + 1))
		return (create_empty_block(ptr_head, size));
	else
		return (merge_or_new(ptr_head, size));
}