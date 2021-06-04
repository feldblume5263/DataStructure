
#include <stdio.h>

int	main()
{
	char a[10] = {'a', (char)1, 'b'};

	int idx =0;
	while (idx < 3)
	{
		if (idx != 1)
			printf("%c\n", a[idx]);
		else
			printf("%d\n", a[idx]);
		idx++;
	}
}
