/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jopeters <jopeters@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:12:12 by jopeters          #+#    #+#             */
/*   Updated: 2023/11/10 11:16:57 by jopeters         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int main(void)
{
    char *prompt_in;

    clear_screen();

    while(1)
    {
        prompt_in = prompt(prompt_in);
        free(prompt_in);
    }
    
    return 0;
}