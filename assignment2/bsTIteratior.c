#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct			s_Node
{
	int					content;
	struct s_Node		*left;
	struct s_Node		*right;
}						TreeNode;

typedef struct			s_binary_search_tree
{
	TreeNode			*root;
	int					(*cmp)(int, int);
	int					size;
}						Tree;

typedef struct			s_Iterator
{
	int					*Tree;
	int					idx;
}						BSTIterator;

int						tree_count = 0;
int						print_idx = 0;

size_t		count_start(char const *s, char c, size_t idx)
{
	size_t			count;

	count = 0;
	if (idx == 0 && s[idx] != c)
		count++;
	else if (s[idx] != c && s[idx - 1] == c)
		count++;
	return (count);
}

size_t		inspect_chunk_len(char const *s, char c, size_t idx)
{
	size_t			len;

	len = 0;
	while (s[idx] && s[idx] != c)
	{
		len++;
		idx++;
	}
	return (len);
}

char		**split_and_put_str(char const *s, char c, char **str)
{
	size_t			idx;
	size_t			chunk;
	size_t			word;
	size_t			chunk_len;

	idx = 0;
	chunk = 0;
	while (s[idx])
	{
		if (count_start(s, c, idx) == 1)
		{
			chunk_len = inspect_chunk_len(s, c, idx);
			if (!(str[chunk] = (char *)malloc(sizeof(char) * (chunk_len + 1))))
				return (0);
			word = 0;
			while (word < chunk_len)
				str[chunk][word++] = s[idx++];
			str[chunk++][word] = 0;
		}
		else
			idx++;
	}
	return (str);
}

char		**split(char const *s, char c)
{
	char			**str;
	size_t			chunk;
	size_t			idx;

	if (!(s))
		return (NULL);
	chunk = 0;
	idx = 0;
	while (s[idx])
	{
		if (count_start(s, c, idx) == 1)
			chunk++;
		idx++;
	}
	if (!(str = (char **)malloc(sizeof(char *) * (chunk + 1))))
		return (NULL);
	str[chunk] = 0;
	if (!(str = split_and_put_str(s, c, str)))
		return (0);
	return (str);
}

char		*gnl_join(char *line, char buff)
{
	char	*ret;
	int		size;

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

int			get_input(char **line)
{
	char	*buff;
	int		flag;

	buff = (char *)malloc(sizeof(char) * 2);
	if (!buff || !line || !(*line = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	*line[0] = '\0';
	while ((flag = read(0, buff, 1)) > 0)
	{
		if (buff[0] == '\n')
			break;
		*line = gnl_join(*line, buff[0]);
	}
	free(buff);
	buff = NULL;
	return (flag);
}

// 중위 순회
void					set_inorder_tree(TreeNode *root, BSTIterator *ret)
{
	if (root)
	{
		set_inorder_tree(root->left, ret);
		(ret->Tree)[ret->idx] = root->content;
		ret->idx++;
		set_inorder_tree(root->right, ret);
	}


}

BSTIterator				*bSTIteratorCreate(TreeNode *root)
{
	BSTIterator* ret = (BSTIterator *)malloc(sizeof(BSTIterator));

	if (!(ret->Tree = (int*)malloc(sizeof(int) * (tree_count))))
		return (NULL);
	ret->idx = 0;
	set_inorder_tree(root, ret);
	return (ret);
}

int						bSTIteratorNext(BSTIterator *obj)
{
	int					ret;

	if(obj->idx)
	{
		ret = obj->Tree[print_idx + 1];
		obj->idx--;
		print_idx++;
	}
	else
	{
		ret = 1;
		printf("]\n");
		printf("\nERROR: Have no Next content!\n");
		printf("\nERROR: Process over\n");
		exit(ret);
	}
	return (ret);
}

bool					bSTIteratorHasNext(BSTIterator *obj)
{
	return (obj->idx - 1 > 0);
}

void					bSTIteratorFree(BSTIterator *obj)
{
	free(obj->Tree);
	free(obj);
}

char					**parse_input(char **input)
{
	int					idx;

	idx = 0;
	while (idx < strlen(*input))
	{
		if ((*input)[idx] == '[' || (*input)[idx] == ']' || (*input)[idx] == ' ' | (*input)[idx] == '"')
			(*input)[idx] = ',';
		idx++;
	}
	return (split(*input, ','));
}


TreeNode		*create_elem(int data)
{
	TreeNode	*node;

	node = malloc(sizeof(TreeNode));
	if (!node)
		return (0);
	node->content = data;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int						make_complete_binary_tree(Tree *tree, int data)
{

	TreeNode			*new;
	TreeNode			*curr;
	TreeNode			*prev;
	int					cmp_result;

	if (!tree)
		return (0);
	curr = tree->root;
	prev = 0;
	while (curr)
	{
		if (!(cmp_result = tree->cmp(data, curr->content)))
			return (0);
		prev = curr;
		if (cmp_result < 0)
			curr = curr->left;
		else
			curr = curr->right;
	}
	if (!(new = create_elem(data)))
		return (0);
	if (!prev)
		tree->root = new;
	else if (cmp_result < 0)
		prev->left = new;
	else
		prev->right = new;
	tree->size++;
	return (1);
}

int						get_input_count(char **tree_input)
{
	int					count;

	count = 0;
	while (tree_input[count])
	{
		if (strlen(tree_input[count]) == 3 && !(strncmp(tree_input[count], "null", 3)))
		{
			continue ;
		}
		count++;
	}
	return (count);
}


Tree				*tree_init(int (*cmp)(int, int))
{
	Tree			*tree;

	if (!cmp || !(tree = malloc(sizeof(Tree))))
		return (0);
	tree->root = 0;
	tree->cmp = cmp;
	tree->size = 0;
	return (tree);
}

int						cmp(int a, int b)
{
	return (a - b);
}

int						main()
{
	BSTIterator			*iterator;
	Tree				*root;
	char				*input1;
	char				*input2;
	char				**command_input;
	char				**tree_input;
	int					idx;

	printf("Enter Commands : \n");
	get_input(&input1);
	printf("\nEnter Tree : \n");
	get_input(&input2);

	command_input = parse_input(&input1);

	tree_input = parse_input(&input2);
	tree_count = get_input_count(tree_input);

	root = tree_init(cmp);
	idx = 0;
	while (tree_input[idx])
	{
		if (strlen(tree_input[idx]) == 3 && !(strncmp(tree_input[idx], "null", 3)))
		{
			idx++;
			continue ;
		}
		make_complete_binary_tree(root, atoi(tree_input[idx]));
		idx++;
	}

	iterator = bSTIteratorCreate(root->root);
	idx = 0;
	printf("\n\nresult:\n[");
	while (command_input[idx])
	{
		if (strlen(command_input[idx]) == 4 && strncmp(command_input[idx], "next", 4) == 0)
		{
			printf("%d", bSTIteratorNext(iterator));
		}
		else if (strlen(command_input[idx]) == 7 && strncmp(command_input[idx], "hasNext", 7) == 0)
		{
			if (bSTIteratorHasNext(iterator) == true)
				printf("true");
			else
				printf("false");
		}
		else if (strlen(command_input[idx]) == 11 && strncmp(command_input[idx], "BSTIterator", 11) == 0)
		{
			printf("null");
		}
		if (command_input[idx + 1])
			printf(", ");
		idx++;
	}
	printf("]\n");


	free(input1);
	input1 = NULL;
	free(input2);
	input2 = NULL;
	bSTIteratorFree(iterator);
}
