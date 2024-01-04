/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_lst_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonas <jonas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:35:14 by jopeters          #+#    #+#             */
/*   Updated: 2024/01/04 14:46:15 by jonas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"

// delete fir node of a linked list
void	lst_delete_first(t_list **llist)
{
	t_list	*temp;

	if (*llist == NULL)
		return ;
	temp = *llist;
	*llist = (*llist)->next;
	free(temp->content);
	free(temp);
}

// free llist and optional the content
void	lst_dealloc(t_list **llist, int free_content)
{
	t_list	*cur;
	t_list	*aux;

	if (!llist)
		return ;
	//else
	//	printf("llst is TRUE \n");

	cur = *llist;
	while (cur != NULL)
	{
		aux = cur;
		cur = cur->next;
		if (aux->content && free_content)
		{
			//printf("free content: >%s<\n", (char*)aux->content);
			free(aux->content);
		}
		free(aux);
	}
	*llist = NULL;
}

// updates the content of a node 
void	update_content_in_node(t_list *node, char *new_content)
{
	//c_yellow();
	//printf("update_content_in_node() --> new_content >%s<   old node->content >%s<\n", new_content, (char*)node->content);c_reset();
	if (node && node->content)
		free(node->content);
	else
		return ;
	node->content = (char *)malloc(sizeof(char) * (ft_strlen(new_content) + 1));
	ft_strlcpy(node->content, new_content, ft_strlen(new_content) + 1);
}

// finds var in llst and returns the node
t_list	*find_var_in_llst(t_list **llst, char *var)
{
	t_list	*tmp_lst;
	char	*tmp_str;

	tmp_lst = *llst;
	//c_yellow(); printf("find_var_in_llst() --> var >%s<\n", var); c_reset();
	while (tmp_lst)
	{
		tmp_str = (char *)tmp_lst->content;
		if ((ft_strncmp(var, (char *)tmp_lst->content, ft_strlen(var)) == 0)
			&& ((ft_strlen(tmp_str) == ft_strlen(var))
				|| (tmp_str[ft_strlen(var)] == '=')))
		{
			//c_green(); printf("  -> found var >%s< with = \n", var);
			//c_purple(); printf("  -> content >%s< \n", tmp_str);
			return (tmp_lst);
			break ;
		}
		tmp_lst = tmp_lst->next;
	}
	//c_red(); printf("~find_var_in_llst() --> not found >%s<\n", var); c_reset();
	return (NULL);
}

/* adding a node with a string to a linked list i.a "A=hello"; no parsing involved!;
creates a new llist if llist is null; mallocs for char *   */
void	add_variable_to_llst(t_list **llst, char *var)
{
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(var) + 1));
	ft_strlcpy(str, var, ft_strlen(var) + 1);
	if (!llst)
		*llst = ft_lstnew((void *)str);
	else
		ft_lstadd_back(llst, ft_lstnew((void *)str));
}
