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

typedef struct			s_Iterator
{
	int					*Tree;
	int					idx;
}						BSTIterator;

int						command_count = 0;
int						tree_count = 0;

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
		inorder(root->left, ret);
		(ret->Tree)[ret->idx] = root->content;
		ret->idx++;
		inorder(root->right, ret);
	}


}

BSTIterator				*bSTIteratorCreate(TreeNode *root)
{
	BSTIterator* ret = (BSTIterator *)malloc(sizeof(BSTIterator));

	if (!(ret->Tree = (int*)malloc(sizeof(int) * (tree_count))))
		return (NULL);
	ret->idx = 0; // start
	set_inorder_tree(root, ret);
	return (ret);
}

int						bSTIteratorNext(BSTIterator *obj)
{



}

bool					bSTIteratorHasNext(BSTIterator *obj)
{


}

void					bSTIteratorFree(BSTIterator *obj)
{



}

char					**refine_input(char **input)
{
	int					idx;

	idx = 0;
	while (idx < strlen(*input))
	{
		if ((*input)[idx] == '[' || (*input)[idx] == ']' || (*input)[idx] == ' ')
			(*input)[idx] = ',';
		idx++;
	}
	return (split(*input, ','));
}


void					make_complete_binary_tree(char **tree_input, TreeNode *root)
{
	int					idx;
	int					count;

	count = 1;
	idx = 0;
	while (tree_input[idx])
	{
		while (idx < count)
		{
			if (!(strlen(tree_input[idx]) == 3 && !strncmp(tree_input[idx], "null", 3)))
			{
				idx++;
				continue ;
			}
			idx++;
		}
	}
}

int						get_tree_count(char **tree_input)
{
	int					count;

	count = 0;
	while (tree_input[count])
	{
		count++;
	}
	return (count);
}

int						main()
{
	BSTIterator			iterator;
	TreeNode			root;
	char				*input1;
	char				*input2;
	char				**command_input;
	char				**tree_input;

	get_input(&input1);
	get_input(&input2);

	command_input = refine_input(&input1);
	tree_input = refine_input(&input2);
	tree_count = get_tree_count(tree_input);
	make_complete_binary_tree(tree_input, &root);

	free(input1);
	input1 = NULL;
	free(input2);
	input2 = NULL;


}
