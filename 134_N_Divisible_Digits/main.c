

int main(int argc, char* argv[])
{
    int i = 0;
    int n_max_value = 0;
    int m_value = atoi(argv[2]);
    if(3 != argc)
    {
        printf("Invalid input: Inproper argument count \n");
        printf("    <commond> <n> <m> \n");
        return 0;
    }
    if(9 < atoi(argv[1])||(1 > atoi(argv[1])))
    {
        printf("Invalid input: N must be a value between 1 through 9 \n");
        return 0;
    }
    if((999999999 < m_value)||(2 > m_value))
    {
        printf("Invalid input: N must be a value between 2 through 999999999 \n");
        return 0;
    }
    /* determine the highest n value number */
    n_max_value = (int)(pow(10.0, (double)atoi(argv[1])) -1);
    /* loop through to determine the highest value evenly dvisible by M */
    for(i = n_max_value; i>0; i--)
    {
        if(0 == (i % m_value))
        {
            printf("%d\n",i);
            return 0;
        }
    }
    printf("No solution found\n");
    return 0;
}
