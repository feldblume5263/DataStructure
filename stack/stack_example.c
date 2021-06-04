/*
 * Make a Palindrome in C.
 * Noramally, spaces or punctuation marks between words are ignored,
 * but it can be implemented otherwise
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

stack			*new_stack(); // 스택 생성자
void			delete_stack(); // 스택 소멸자
int				is_full(stack *stack); // 스택이 full상태인지 확인
int				is_empty(stack *stack); // 스택이 empty상태인지 확인
void			push(stack *stack, element data); // 스택에 push
element			pop(stack *stack); // 스택에서 pop


typedef void	*element;

typedef struct	s_tack
{
	element		*buf;
	int			ssize;
	int			top;
}				t_stack;

typedef struct	s_data
{
	int			num;
	char		*name;
}				t_data;


