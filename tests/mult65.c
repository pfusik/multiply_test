// mult65.c

// specify range of input values
static const uint64_t INPUT_START = 0UL;
static const uint64_t INPUT_END   = 65536UL;

// **************************************************************************************
void test_pre(thread_context_t* threadContext, uint64_t input) {
    zuint8* memory = threadContext->machine.context;

    // set high bytes of addresses of table 2
    // normally done by calling mul_init once
    memory[7] = 2;
    memory[9] = 4;
    threadContext->machine.state.x = input & 255UL;
    threadContext->machine.state.y = (input / 256UL) & 255UL;
}

// **************************************************************************************
uint64_t test_post(thread_context_t* threadContext) {
    zuint8* memory = threadContext->machine.context;

    uint64_t low = memory[10];
    uint64_t high = threadContext->machine.state.a;

    return low + 256*high;
}

// **************************************************************************************
int is_correct(thread_context_t* threadContext, uint64_t input, uint64_t actual_result, uint64_t* expected) {
    uint64_t a = input & 255UL;
    uint64_t b = (input / 256UL) & 255UL;

    uint64_t e = a*b;
    *expected = e;

    return actual_result == e;
}

// **************************************************************************************
void test_cleanup()
{
}