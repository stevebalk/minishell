/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:16:37 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/10 11:20:01 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char *prompt(char *in)
{
    c_red();printf("minihell");
    c_yellow();printf(">>");
        
    c_cyan();
    in = readline("");
        
    c_green();
    printf("|%s|\n", in);

    return in;  
}	