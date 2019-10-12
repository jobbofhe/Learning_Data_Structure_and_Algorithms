


void get_next(char *T, int *next)
{
    j = 0; 
    i = 1;
    next[i] = 0;

    while (i < T[0])
    {
        if (0 == j || T[i] == T[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}


int  kmp(char *S, char *T, int pos)
{
    int i = pos;
    int j = 1;
    int next[255];

    get_next(T, next);

    while(i <= S[0] && j <= t[0])
    {
        if (0 == j || S[i] == T[j])
        {
            i++;
            j++;
            if (T[i] != T[j])
            {
                next[i] = j;
            }
            else
            {
                next[i] = next[j];
            }
        }
        else
        {
            j = next[j];
        }
    }

    if (j > T[0])
    {
        return i - T[0];
    }
    else
    {
        return 0;
    }
}