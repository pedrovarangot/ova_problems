#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
    int cases = 0, eff_hartals = 0;
    int days, parties, partie_h, i;
    bool daysh[3651];
    scanf("%d\n", &cases);


    while(cases > 0) {
        scanf("%d\n", &days);
        scanf("%d\n", &parties);
        bzero(daysh, 3651);
        
        while(parties > 0) {
        
            scanf("%d\n", &partie_h);
            for(i = 1; i <= days; i++) {
                if(i % 7 == 6 || i % 7 == 0) {
                    continue;
                }
                if(i % partie_h == 0 && !daysh[i]) {
                    daysh[i] = true;
                    eff_hartals++;
                }
            }

            parties--;
        }
        
        printf("%d\n", eff_hartals);
        cases--;
        eff_hartals = 0;
    }
    return 0;
}

