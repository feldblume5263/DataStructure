#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define ERROR				-1
#define MAX_WORD_LENGTH		20
#define MAX_MEAN_LENGTH		200

typedef struct			s_elemet
{
	char				word[MAX_WORD_LENGTH + 1];
	char				mean[MAX_MEAN_LENGTH + 1];
}						t_element;

typedef struct			s_tree_node
{
	t_element			element;
	struct s_tree_node	*right;
	struct s_tree_node	*reft;
}						t_tree_node;


/*
**				Insert
*/
void			insert()
{

}


/*
**				에러 처리
*/
void					print_error()
{
	system("clear");
	printf("\n\nError!! please enter number (1 ~ 5)\n");
	printf("\n\npress Enter\n\n");
	system("read");
	system("clear");
}

int						make_number_or_error(char *line)
{
	int					ret;
	int					idx;
	t_tree_node			*root;

	root = NULL;
	ret = atoi(line);
	idx = 0;
	while (line[idx])
	{
		if (!(line[idx] >= '0' && line[idx] <= '9'))
			return (ERROR);
		idx++;
	}
	if (ret < 1 || ret > 5)
		return (ERROR);
	return (ret);
}


/*
**				표준 입력을 글자 수 제한 없이 받는 함수
*/

char					*join(char *line, char buff)
{
	char				*ret;
	int					size;

	size = 0;
	while (line[size])
		size++;
	if (!(ret = (char *)malloc(sizeof(char) * (size + 2))))
		return (0);
	size = -1;
	while (line[++size])
		ret[size] = line[size];
	ret[size] = buff;
	ret[size + 1] = '\0';
	free(line);
	line = NULL;
	return (ret);
}

int						get_input(char **line)
{
	char				*buff;
	int					flag;

	buff = (char *)malloc(sizeof(char) * 2);
	if (!buff || !line || !(*line = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	*line[0] = '\0';
	while ((flag = read(0, buff, 1)) > 0)
	{
		if (buff[0] == '\n')
			break;
		*line = join(*line, buff[0]);
	}
	free(buff);
	buff = NULL;
	return (flag);
}

/*
**				Menu 표시, Menu 선택화면
*/

void					print_menu()
{
	printf("* -------------------------------- *\n");
	printf("*                                  *\n");
	printf("*          (1) : Insert            *\n");
	printf("*                                  *\n");
	printf("*          (2) : Delete            *\n");
	printf("*                                  *\n");
	printf("*          (3) : Search            *\n");
	printf("*                                  *\n");
	printf("*          (4) : Print             *\n");
	printf("*                                  *\n");
	printf("*          (5) : Exit              *\n");
	printf("*                                  *\n");
	printf("* -------------------------------- *\n");
	write(1, "Enter number (1 ~ 5)  :   ", strlen("Enter number (1 ~ 5)  :   "));
}

void					print_greeter()
{
	printf("                                                      \n");
	printf(" ____  _      _   _                                   \n");
	printf("|  _ \\(_) ___| |_(_) ___  _ __   __ _ _ __ _   _     \n");
	printf("| | | | |/ __| __| |/ _ \\| '_ \\ / _` | '__| | | |    \n");
	printf("| |_| | | (__| |_| | (_) | | | | (_| | |  | |_| |    \n");
	printf("|____/|_|\\___|\\__|_|\\___/|_| |_|\\__,_|_|   \\__, |    \n");
	printf("                                           |___/     \n");
	printf("                                                     \n");
	printf("                     (press Enter)                   \n");
}

int						main(void)
{
	int					input;
	char				*line;

	system("clear");
	print_greeter();
	system("read");
	system("clear");
	input = 0;
	while (input != 5)
	{
		input = 0;
		print_menu();
		get_input(&line);
		if ((input = make_number_or_error(line)) == ERROR)
		{
			print_error();
			free(line);
			continue ;
		}
		else if (input == 1)
			insert();
		free(line);
		system("clear");
	}

}
