#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

int main(int argc, char** argv) {
    printf("const: RAND_MAX | %d; # <stdlib.h>\n", RAND_MAX);
    printf("const: MB_CUR_MAX | %d; # <stdlib.h>\n", MB_CUR_MAX);
    printf("const: EXIT_SUCCESS | %d; # <stdlib.h>\n", EXIT_SUCCESS);
    printf("const: EXIT_FAILURE | %d; # <stdlib.h>\n", EXIT_FAILURE);
    printf("const: CLOCKS_PER_SEC | %d; # <time.h>\n", CLOCKS_PER_SEC);
    printf("const: SIG_DFL | %d; # <signal.h>\n", SIG_DFL);
    printf("const: SIG_ERR | %d; # <signal.h>\n", SIG_ERR);
    printf("const: SIG_IGN | %d; # <signal.h>", SIG_IGN);
}
