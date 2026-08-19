/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larchimb <larchimb@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 18:02:47 by larchimb          #+#    #+#             */
/*   Updated: 2026/08/19 12:47:04 by larchimb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	check_and_move(t_heap *heap, t_request *first, t_request req)
{
	if (first->ticket < req.ticket)
			heap->requests[1] = req;
		else
		{
			heap->requests[1] = *first;
			*first = req;
		}
}

void	heap_push(t_heap *heap, t_request req, int scheduler)
{
	if (heap->size >= 1 && scheduler == 0)
		check_and_move(heap, &heap->requests[0], req);
	else if (heap->size >= 1 && scheduler == 1)
	{
		if (heap->requests[0].deadline < req.deadline)
			heap->requests[1] = req;
		else if (heap->requests[0].deadline > req.deadline)
		{
			heap->requests[1] = heap->requests[0];
			heap->requests[0] = req;
		}
		else
		{
			if (req.coder_id % 2 == 1)
				heap->requests[1] = req;
			else
			{
			heap->requests[1] = heap->requests[0];
			heap->requests[0] = req;
			}
		}
	}
	else
		heap->requests[0] = req;
	heap->size += 1;
}

void	heap_pop(t_heap *heap)
{
	if (heap->size == 2)
		heap->requests[0] = heap->requests[1];
	heap->size -= 1;
}

void	push_request(t_data *data, t_coder *coder)
{
	t_request 	req;
	int			scheduler;

	scheduler = data->args->scheduler;
	req.ticket = data->next_ticket++;
	req.deadline = coder->last_start + data->args->time_to_burnout;
	req.coder_id = coder->id;
	heap_push(&coder->left->queue, req, scheduler);
	heap_push(&coder->right->queue, req, scheduler);
}

int	check_priority(t_coder *coder)
{
	if (coder->left->queue.requests[0].coder_id == coder->id
		&& coder->right->queue.requests[0].coder_id == coder->id)
		return (1);
	return (0);
}