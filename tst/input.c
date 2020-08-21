int g_var = 0;
const int g_const = 1;
static int s_var = 2;
static const int s_const = 3;

void g_void_func()
{
    
}

int g_int_func()
{
    return 0;
}

void g_void_func_int(int i)
{
    
}

void g_void_func_int_str(int i, char * s)
{
    
}

static void s_void_func()
{
    
}

static int s_int_func()
{
    return 0;
}

static void s_void_func_int(int i)
{
    
}

static void s_void_func_int_str(int i, char * s)
{
    
}

static inline void inline_func()
{
    
}

union union_t
{
    int i;
    float f;
};

union
{
    char * no_name;
};


struct struct_t
{
    int i;
    char * s;
};

struct
{
    char * no_name;
};

enum enum_t
{
    const1,
    const2
};

enum
{
    no_name
};
