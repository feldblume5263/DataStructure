#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define ERROR				-1

typedef struct			s_elemet
{
	char				*word;
	char				*mean;
}						t_element;

typedef struct			s_tree_node
{
	t_element			element;
	struct s_tree_node	*right;
	struct s_tree_node	*left;
}						t_tree_node;

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
**				표준 입력
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
**				4. Print
*/

void			print_all_word(t_tree_node *root)
{
	if (root)
	{
		print_all_word(root->left);
		printf("\n----------------------------------------------------\n\n");
		printf("word:\t\t%s\nmeaning:\t%s\n\n", root->element.word, root->element.mean);
		print_all_word(root->right);
	}
}

void			print(t_tree_node *root)
{
	system("clear");
	printf("\n[Dictionary list]\n");
	print_all_word(root);
	printf("\n----------------------------------------------------\n\n");
	printf("(press Enter to continue)\n");
	system ("read");
}

/*
**				3. Search
*/

t_element		*search_word_using_bst(t_tree_node *root, char *search_word)
{
	t_tree_node	*new;
	int			compare;

	new = root;
	while (new != NULL)
	{
		compare = strcmp(search_word, new->element.word);
		if (compare < 0)
			new = new->left;
		else if (compare > 0)
			new = new->right;
		else
			return (&(new->element));
	}
	return (NULL);
}


void			search(t_tree_node *root)
{
	char		*search_word;
	t_element	*ret;

	system("clear");
	write(1, "[Search] Enter the word you want to search for\n : ", strlen("[Search] Enter the word you want to search for\n : "));
	get_input(&search_word);
	if (!(ret = search_word_using_bst(root, search_word)))
	{
		system("clear");
		printf("The word [%s] is not in the dictionary.\n", search_word);
		printf("(press Enter to continue)\n");
		system("read");
		return ;
	}
	printf("word [%s] meaning : %s\n\n", ret->word, ret->mean);
	printf("(press Enter to continue)\n");
	system("read");
}

/*
**				2. Delete
*/

t_tree_node		*search_node_using_bst(t_tree_node *root, char *search_word)
{
	t_tree_node	*new;
	int			compare;

	new = root;
	while (new != NULL)
	{
		compare = strcmp(search_word, new->element.word);
		if (compare < 0)
			new = new->left;
		else if (compare > 0)
			new = new->right;
		else
			return (new);
	}
	return (NULL);
}

void			delete(t_tree_node *root)
{
	char		*delete_word;
	t_tree_node	*finded_element;

	write(1, "[Delete] Enter word to delte\n : ", strlen("[Delete] Enter word to delte\n : "));
	get_input(&delete_word);
	if (!(finded_element = search_node_using_bst(root, delete_word)))
	{
		system("clear");
		printf("The word [%s] is not in the dictionary.\n", delete_word);
		printf("(press Enter to continue)\n");
		system("read");
		return ;
	}
	else
	{
		printf("%s\n%s\n", finded_element->element.word, finded_element->element.mean);
		system("read");
	}

}


/*
**				1. Insert
*/

t_tree_node		*insert_new_node(t_tree_node *node, t_element *new_word)
{
	t_tree_node	*new_node;
	int			compare;

	if (node == NULL)
	{
		new_node = (t_tree_node *)malloc(sizeof(t_tree_node));
		new_node->element = *new_word;
		new_node->left = NULL;
		new_node->right = NULL;
		return (new_node);
	}
	else
	{
		compare = strcmp(new_word->word, node->element.word);
		if (compare < 0)
		{
			node->left = insert_new_node(node->left, new_word);
			return (node);
		}
		else if (compare > 0)
		{
			node->right = insert_new_node(node->right, new_word);
			return (node);
		}
		else
		{
			system("clear");
			printf("\nWe already have the same word!\n");
			printf("(press Enter to continue)\n");
			system("read");
			return (node);
		}
	}

}

void			insert_announce(t_element *new_word)
{
	char		*input;

	write(1, "\n[Insert] Enter new word\n : ", strlen("\n[Insert] Enter new word\n : "));
	get_input(&input);
	new_word->word = strdup(input);
	free(input);
	write(1, "\n[Insert] Enter meaning of new word\n : ", strlen("\n[Insert] Enter meaning of new word\n : "));
	get_input(&input);
	new_word->mean = strdup(input);
	free(input);
}

void			insert(t_tree_node **root)
{
	t_element	new_word;

	system("clear");
	insert_announce(&new_word);
	*root = insert_new_node(*root, &new_word);
}


/*
**				Menu 표시, Menu 선택화면
*/

void					print_menu()
{
	printf("* -------------------------------- *\n");
	printf("*                                  *\n");
	printf("*          [ Dictionary ]          *\n");
	printf("*                                  *\n");
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
	t_tree_node			*root;

	root = NULL;
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
			insert(&root);
		else if (input == 2)
			delete(root);
		else if (input == 3)
			search(root);
		else if (input == 4)
			print(root);
		free(line);
		system("clear");
	}

}
