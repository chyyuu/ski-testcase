#include "ski-hyper.h"

int main(int argc, char** argv){
    hypercall_debug(0, "%s", argv[1]);
    return 0;
}
