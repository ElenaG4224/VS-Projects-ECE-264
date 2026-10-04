/*#include <stdio.h>

int F(int n);

int main()
{
    int n;
    printf("Enter sequence length: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        int sum = F(i);
        printf("%d, ", sum);
    }
    return 0;
}

int F(int n)
{
    if (n <= 1)
    {
        return n;
    }

    int sum = F(n-1) + F(n-2);

     // how do i get this to only print for the sum, and not for the sum of each component???

    return sum;
}*/

#include <stdio.h>
void printCountdown(int n) {
if (n == 0) {
printf("Liftoff!");
return;
}
printf("%d ", n);
printCountdown(n - 1);
}
int main() {
printCountdown(3);
return 0;
}