#include "global.h"
#include "stream.h"
#include "parson.h"

typedef struct kinds_t kinds_t;
struct kinds_t
{
    bool unions;
    bool structs;
    bool variables;
    bool functions;
    bool static_variables;
    bool static_functions;
};

void print_usage();
char *parse_signature(const char *signature);
char *parse_properties(const char *properties);
char *parse_type(const char *typeref);
bool starts_with(const char *string, const char *prefix);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        print_usage();
        return ~0;
    }

    kinds_t kinds = {0};

    if (argc == 2)
    {
        kinds.unions = true;
        kinds.structs = true;
        kinds.variables = true;
        kinds.functions = true;
        kinds.static_functions = true;
        kinds.static_variables = true;
    }
    else
    {
        for (int i = 2; i < argc; i++)
        {
            if (!strcmp("unions", argv[i]))
            {
                kinds.unions = true;
            }
            else if (!strcmp("structs", argv[i]))
            {
                kinds.structs = true;
            }
            else if (!strcmp("variables", argv[i]))
            {
                kinds.variables = true;
            }
            else if (!strcmp("functions", argv[i]))
            {
                kinds.functions = true;
            }
            else if (!strcmp("static_variables", argv[i]))
            {
                kinds.static_variables = true;
            }
            else if (!strcmp("static_functions", argv[i]))
            {
                kinds.static_functions = true;
            }
        }
    }

    const char *ctags = "ctags --sort=no --output-format=json --language-force=c "
                        "--c-kinds=\"{struct}{union}{variable}{function}\" "
                        "--fields=\"{kind}{name}{typeref}{signature}\" --fields-c=\"{properties}\" ";

    char *command = null;
    asprintf(&command, "%s%s", ctags, argv[1]);
    stream_t *ctags_stream = stream_open_process(command, "r");
    memory_free(command);

    json_set_allocation_functions(memory_alloc, free);

    char *line = null;
    while (stream_read_line(&line, ctags_stream))
    {
        JSON_Value *root = json_parse_string(line);
        JSON_Object *declaration = json_value_get_object(root);
        const char *name = json_object_get_string(declaration, "name");
        const char *typeref = json_object_get_string(declaration, "typeref");
        const char *kind = json_object_get_string(declaration, "kind");
        const char *properties = json_object_get_string(declaration, "properties");
        const char *signature = json_object_get_string(declaration, "signature");

        if (!strcmp(kind, "variable"))
        {
            char *type = parse_type(typeref);

            if (!properties)
            {
                if (kinds.variables)
                {
                    printf("%s %s;\n", type, name);
                }
            }
            else
            {
                char *props = parse_properties(properties);
                bool is_static = strstr(props, "static") != null;

                if (is_static && kinds.static_variables || !is_static && kinds.variables)
                {
                    printf("%s %s %s;\n", props, type, name);
                }

                memory_free(props);
            }

            memory_free(type);
        }
        else if (!strcmp(kind, "function"))
        {
            char *type = parse_type(typeref);
            char *sign = parse_signature(signature);

            if (!properties)
            {
                if (kinds.functions)
                {
                    printf("%s %s%s;\n", type, name, sign);
                }
            }
            else
            {
                char *props = parse_properties(properties);
                bool is_static = strstr(props, "static") != null;

                if (is_static && kinds.static_functions || !is_static && kinds.functions)
                {
                    printf("%s %s %s%s;\n", props, type, name, sign);
                }

                memory_free(props);
            }

            memory_free(type);
            memory_free(sign);
        }
        else if (!strcmp(kind, "struct") && kinds.structs)
        {
            if (!starts_with(name, "__anon"))
            {
                printf("typedef struct %s %s;\n", name, name);
            }
        }
        else if (!strcmp(kind, "union") && kinds.unions)
        {
            if (!starts_with(name, "__anon"))
            {
                printf("typedef union %s %s;\n", name, name);
            }
        }

        json_value_free(root);
    }

    memory_free(line);
    stream_close_process(ctags_stream);

    return 0;
}

void print_usage()
{
    puts("usage: cdecl file.c [kinds]");
    puts("kinds:");
    puts(" - unions");
    puts(" - structs");
    puts(" - variables");
    puts(" - functions");
    puts(" - static_variables");
    puts(" - static_functions");
}

char *parse_signature(const char *signature)
{
    if (signature == null)
    {
        return "";
    }

    int count = 0;
    int length = strlen(signature);

    for (int i = 0; i < length; i++)
    {
        if (signature[i] == ',')
        {
            count++;
        }
    }

    int result_length = length + count + 1;
    char *result = memory_alloc(sizeof(char) * result_length);

    for (int i = 0, j = 0; i < result_length; i++, j++)
    {
        char c = signature[j];
        result[i] = c;
        if (c == ',')
        {
            i++;
            result[i] = ' ';
        }
    }

    return result;
}

char *parse_properties(const char *properties)
{
    if (properties == null)
    {
        return "";
    }

    int length = strlen(properties) + 1;
    char *result = memory_alloc(sizeof(char) * length);

    for (int i = 0; i < length; i++)
    {
        char c = properties[i];
        if (c == ',')
        {
            result[i] = ' ';
        }
        else
        {
            result[i] = c;
        }
    }

    return result;
}

char *parse_type(const char *typeref)
{
    if (typeref == null)
    {
        return "";
    }

    int index = 0;
    int length = strlen(typeref);

    while (typeref[index] != ':')
    {
        if (typeref[index] == '\0')
        {
            return "";
        }
        index++;
    }

    index++;

    int result_length = length - index + 1;
    char *result = memory_alloc(sizeof(char) * result_length);

    for (int i = 0; i < result_length; i++)
    {
        result[i] = typeref[index + i];
    }

    return result;
}

bool starts_with(const char *string, const char *prefix)
{
    while (*prefix)
    {
        if (*prefix++ != *string++)
        {
            return false;
        }
    }

    return true;
}