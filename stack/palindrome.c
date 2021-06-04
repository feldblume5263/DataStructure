#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE	100

typedef struct		node
{
	char			data;
	struct node		*link;
}					node;

node			*top;

void			print_stack()
{
	node		*p;

	p = top;
	printf("\n STACK[");
	while (p)
	{
		printf("%c ", p->data);
		p = p->link;
	}
	printf("]\n");
}

void			push(char item)
{
	node		*temp;
	 
	if (!(temp = (node *)malloc(sizeof(node))))
		return ;
	temp->data = item;
	temp->link = top;
	top = temp;
}


void			pop(char item, int idx)
{
	node		*temp;

	if (top == NULL)
		printf("\n\n stack is Empty!\n");
	else
	{
		temp = top;
		top = top->link;
		if (temp->link->data != item)
		{
			printf("회문이 아님!!\n");
			exit(1);
		}
		free(temp);
	}
}

int				main(void)
{
	int			idx;
	char		item[20];
	
	top = NULL;
	puts("문자열을 입력 : ");
	fgets(item, sizeof(item), stdin);
	idx = 0;
	while (idx < strlen(item))
	{
		push(item[idx]);
		idx++;
	}
	idx = 0;
	while (idx < strlen(item) - 1)
	{
		pop(item[idx], idx);
		idx++;
	}
	printf("회문이 맞음!\n");
	getchar();
}
