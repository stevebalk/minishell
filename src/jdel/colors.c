
void	c_red(void)
{
	printf("\033[0;31m");
}

void	c_green(void)
{
	printf("\033[0;32m");
}

void	c_blue(void)
{
	printf("\033[0;34m");
}

void	c_purple(void)
{
	printf("\033[0;35m");
}

void	c_yellow(void)
{
	printf("\033[0;33m");
}

void	c_cyan(void)
{
	printf("\033[0;36m");
}

void	clear_screen(void)
{
	printf("\e[1;1H\e[2J");
}

void	c_reset(void)
{
	printf("\033[0m");
}
