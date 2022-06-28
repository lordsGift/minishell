/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarinel <mmarinel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 08:22:23 by mmarinel          #+#    #+#             */
/*   Updated: 2022/06/28 13:00:15 by mmarinel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_utils.h"

t_tree_node	*new_tree_node(t_tree_node *left, t_node_content *content, t_tree_node *right)
{
	t_tree_node	*new_node;

	new_node = (t_tree_node *) malloc(sizeof(t_tree_node));
	new_node->content = content;
	new_node->left = left;
	new_node->right = right;
}

void	free_tree(t_tree_node *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	ft_free(root->content->infile);
	ft_free(root->content->outfile);
	free(root->content);
	free(root);
}