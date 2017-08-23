#include <stdio.h>
#include <string.h>

#define MAX_CHAR 256
#define SIZE 256
#define MAX(x, y) (x) > (y) ? (x) : (y)

void BoyerMoore(char *pattern, int m, char *text, int n);


void print(int *array, int n, char *arrayName)
{
	int i;
	printf("%s: ", arrayName);
	for (i = 0; i < n; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

void PreBmBc(char *pattern, int m, int bmBc[])
{
	int i;

	for (i = 0; i < MAX_CHAR; i++)
	{
		bmBc[i] = m;
	}

	for (i = 0; i < m - 1; i++)
	{
		bmBc[pattern[i]] = m - 1 - i;
	}

}


void suffix(char *pattern, int m, int suff[]) {
	int f, g, i;

	suff[m - 1] = m;
	g = m - 1;
	for (i = m - 2; i >= 0; --i) {
		if (i > g && suff[i + m - 1 - f] < i - g)
			suff[i] = suff[i + m - 1 - f];
		else {
			if (i < g)
				g = i;
			f = i;
			while (g >= 0 && pattern[g] == pattern[g + m - 1 - f])
				--g;
			suff[i] = f - g;
		}
	}

	//   print(suff, m, "suff[]");
}

void PreBmGs(char *pattern, int m, int bmGs[])
{
	int i, j;
	int suff[SIZE];

	// �����׺����
	suffix(pattern, m, suff);

	// ��ȫ����ֵΪm������Case3
	for (i = 0; i < m; i++)
	{
		bmGs[i] = m;
	}

	// Case2,���j�ͱ���text��j������˼·�Ļ��ң���ʵ����������������ʱ���ʱ��jӦ���Ǵ���ģʽ���Ŀ�ͷ
	j = 0;
	for (i = m - 1; i >= 0; i--)
	{
		if (suff[i] == i + 1)
		{
			for (; j < m - 1 - i; j++)
			{
				if (bmGs[j] == m)
					bmGs[j] = m - 1 - i;
			}
		}
	}

	// Case1
	for (i = 0; i <= m - 2; i++)
	{
		bmGs[m - 1 - suff[i]] = m - 1 - i;
	}

	//  print(bmGs, m, "bmGs[]");
}

void BoyerMoore(char *pattern, int m, char *text, int n)
{
	int i, j, bmBc[MAX_CHAR], bmGs[SIZE];

	// Preprocessing
	PreBmBc(pattern, m, bmBc);
	PreBmGs(pattern, m, bmGs);

	// Searching
	j = 0;
	while (j <= n - m)
	{
		for (i = m - 1; i >= 0 && pattern[i] == text[i + j]; i--);
		if (i < 0)
		{
			printf("Find it, the position is %d\n", j);
			j += bmGs[0];
			return;
		}
		else
		{
			j += MAX(bmBc[text[i + j]] - m + 1 + i, bmGs[i]);
		}
	}

	printf("No find.\n");
}

int main()
{
	char p[] = "abcccab";
	int m = 7;
	char text[] = "absccabcccabdesf";
	int n = strlen(text);
	BoyerMoore(p, m, text, n);
	printf("1");
}