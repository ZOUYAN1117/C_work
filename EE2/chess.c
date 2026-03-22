#include <stdio.h>
int a[20][20];
int in_board(int x, int y)
{
    return x >= 0 && x < 19 && y >= 0 && y < 19;
}
int check(int x, int y, int p)
{
    for (int i = 0, j = 0; a[x + i][y + j] == p && in_board(x + i, y + j); i++, j++)
        if (i == 3 && ((a[x - 1][y - 1] == 0 && in_board(x - 1, y - 1)) || (a[x + 4][y + 4] == 0 && in_board(x + 4, y + 4))))
            return 1;
    for (int i = 0, j = 0; a[x + i][y - j] == p && in_board(x + i, y - j); i++, j++)
        if (i == 3 && ((a[x - 1][y + 1] == 0 && in_board(x - 1, y + 1)) || (a[x + 4][y - 4] == 0 && in_board(x + 4, y - 4))))
            return 1;
    for (int i = 0, j = 0; a[x + i][y] == p && in_board(x + i, y); i++, j++)
        if (i == 3 && ((a[x - 1][y] == 0 && in_board(x - 1, y)) || (a[x + 4][y] == 0 && in_board(x + 4, y))))
            return 1;
    for (int i = 0, j = 0; a[x][y + j] == p && in_board(x, y + j); i++, j++)
        if (j == 3 && ((a[x][y - 1] == 0 && in_board(x, y - 1)) || (a[x][y + 4] == 0 && in_board(x, y + 4))))
            return 1;
    return 0;
}
int main()
{
    for (int i = 0; i <= 18; i++)
    {
        for (int j = 0; j <= 18; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 0; i <= 18; i++)
    {
        for (int j = 0; j <= 18; j++)
        {
            if (a[i][j] != 0)
                if (check(i, j, a[i][j]))
                {
                    printf("%d:%d,%d\n", a[i][j], i + 1, j + 1);
                    return 0;
                };
        }
    }
    printf("No\n");
}
