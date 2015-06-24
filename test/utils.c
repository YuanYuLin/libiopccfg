#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define STR_LEN		256

struct query_json_obj_t {
    int isFound;
    char cmp_key[STR_LEN];
    char key_str[STR_LEN];
    enum json_type type;
    struct json_object *obj;
};

static void parse_json_obj(char *key_str, struct json_object *obj_val);
static void parse_json_obj_by_query_obj(struct query_json_obj_t *query_json_obj, char *key_str, struct json_object *obj_val);

static void parse_value_obj(char*key_str, struct json_object *obj_val)
{
    char tmp_str[STR_LEN]={0};
    json_object_object_foreach(obj_val, tmpkey, tmpval) {
        sprintf(tmp_str, "%s.%s", key_str, tmpkey);
        parse_json_obj(tmp_str, tmpval);
    }
}

static void parse_value_array(char *key_str, struct json_object *obj_val)
{
    struct json_object *ele_obj;
    int array_len = 0;
    int i = 0;
    char tmp_str[STR_LEN]={0};
    array_len = json_object_array_length(obj_val);
    for(i=0; i<array_len; i++) {
        ele_obj = json_object_array_get_idx(obj_val, i);
        sprintf(tmp_str, "%s[%d]", key_str, i);
        parse_json_obj(tmp_str, ele_obj);
    }
}

static void parse_json_obj(char *key_str, struct json_object *obj_val)
{
    enum json_type type;
    type = json_object_get_type(obj_val);

    switch(type){
    case json_type_null:
        printf("%s=%s\n", key_str, "NULL");
    break;
    case json_type_boolean:
        printf("%s=%d\n", key_str, json_object_get_boolean(obj_val));
    break;
    case json_type_double:
        printf("%s=%f\n", key_str, json_object_get_double(obj_val));
    break;
    case json_type_int:
        printf("%s=%d\n", key_str, json_object_get_int(obj_val));
    break;
    case json_type_object:
        parse_value_obj(key_str, obj_val);
    break;
    case json_type_array:
        parse_value_array(key_str, obj_val);
    break;
    case json_type_string:
        printf("%s=%s\n", key_str, json_object_get_string(obj_val));
    break;
    default:
        printf("JSON type error\n");
    break;
    }
}

static void parse_value_obj_by_query_obj(struct query_json_obj_t *query_json_obj, char *key_str, struct json_object *obj_val)
{
    char tmp_str[STR_LEN]={0};
    json_object_object_foreach(obj_val, tmpkey, tmpval) {
        sprintf(tmp_str, "%s.%s", key_str, tmpkey);

        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0){
            query_json_obj->isFound = 1;
            query_json_obj->obj = tmpval;
            query_json_obj->type = json_object_get_type(tmpval);
            strcpy(query_json_obj->key_str, tmp_str);
            return;
        }
        parse_json_obj_by_query_obj(query_json_obj, tmp_str, tmpval);
    }
}

static void parse_value_array_by_query_obj(struct query_json_obj_t *query_json_obj, char *key_str, struct json_object *obj_val)
{
    struct json_object *ele_obj;
    int array_len = 0;
    int i = 0;
    char tmp_str[STR_LEN]={0};
    array_len = json_object_array_length(obj_val);
    for(i=0; i<array_len; i++) {
        ele_obj = json_object_array_get_idx(obj_val, i);
        sprintf(tmp_str, "%s[%d]", key_str, i);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0){
            query_json_obj->isFound = 1;
            query_json_obj->obj = ele_obj;
            query_json_obj->type = json_object_get_type(ele_obj);
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
        parse_json_obj_by_query_obj(query_json_obj, tmp_str, ele_obj);
        if(query_json_obj->isFound)
            return ;
    }
}

static void parse_json_obj_by_query_obj(struct query_json_obj_t *query_json_obj, char *key_str, struct json_object *obj_val)
{
    enum json_type type;
    char tmp_str[STR_LEN]={0};
    type = json_object_get_type(obj_val);

    switch(type){
    case json_type_null:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_null;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
    break;
    case json_type_boolean:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_boolean;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
    break;
    case json_type_double:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_double;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
    break;
    case json_type_int:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_int;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
    break;
    case json_type_object:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_object;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
        parse_value_obj_by_query_obj(query_json_obj, key_str, obj_val);
    break;
    case json_type_array:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {
            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_array;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
        parse_value_array_by_query_obj(query_json_obj, key_str, obj_val);
    break;
    case json_type_string:
        sprintf(tmp_str, "%s", key_str);
        if(strcmp(tmp_str, query_json_obj->cmp_key) == 0) {

            query_json_obj->isFound = 1;
            query_json_obj->obj = obj_val;
            query_json_obj->type = json_type_string;
            strcpy(query_json_obj->key_str, tmp_str);
            return ;
        }
    break;
    default:
        printf("JSON type error\n");
    break;
    }
}

static void show_json(struct json_object *json_obj)
{
    json_object_object_foreach(json_obj, obj_key, obj_val) {
        parse_json_obj(obj_key, obj_val);
    }
}

static void show_json_array_len(char* json_key, struct json_object *json_obj)
{
    enum json_type type;
    struct query_json_obj_t query_json_obj;
    int array_len = 0;
    query_json_obj.isFound = 0;
    strcpy(query_json_obj.cmp_key, json_key);
    memset(query_json_obj.key_str, 0, STR_LEN);
    query_json_obj.obj = NULL;

    json_object_object_foreach(json_obj, obj_key, obj_val) {
        parse_json_obj_by_query_obj(&query_json_obj, obj_key, obj_val);
        if(query_json_obj.isFound)
            break;
    }
    if(json_type_array == query_json_obj.type)
        printf("%d", json_object_array_length(query_json_obj.obj));
    else
        printf("Error");
}

static void show_json_value(char* json_key, struct json_object *json_obj)
{
    enum json_type type;
    struct query_json_obj_t query_json_obj;
    int array_len = 0;
    query_json_obj.isFound = 0;
    strcpy(query_json_obj.cmp_key, json_key);
    memset(query_json_obj.key_str, 0, STR_LEN);
    query_json_obj.obj = NULL;

    json_object_object_foreach(json_obj, obj_key, obj_val) {
        parse_json_obj_by_query_obj(&query_json_obj, obj_key, obj_val);
        if(query_json_obj.isFound)
            break;
    }
    switch(query_json_obj.type){
    case json_type_null:
        printf("%s", "NULL");
    break;
    case json_type_boolean:
        printf("%d", json_object_get_boolean(query_json_obj.obj));
    break;
    case json_type_double:
        printf("%f", json_object_get_double(query_json_obj.obj));
    break;
    case json_type_int:
        printf("%d", json_object_get_int(query_json_obj.obj));
    break;
    case json_type_object:
        printf("error");
    break;
    case json_type_array:
        printf("error");
    break;
    case json_type_string:
        printf("%s", json_object_get_string(query_json_obj.obj));
    break;
    default:
        printf("error");
    break;
    }
}

enum{
    SHOW_JSON		= 0x01,
    SHOW_ARRAY_LEN	= 0x02,
    SHOW_VALUE		= 0x04,
};

unsigned long parse_paramegers(int argc, char** argv, char* json_file, char* json_key)
{
    unsigned long func = 0x0;
    int cmd_opt = 0;
    while(1) {
        cmd_opt = getopt(argc, argv, "f:k:slv");

        if(cmd_opt == -1) {
            return func;
        }

        switch(cmd_opt) {
        case 'k': // json key
            strcpy(json_key, optarg);
        break;
        case 'f': // json file
            strcpy(json_file, optarg);
        break;
        case 's': // show all json
            func |= SHOW_JSON;
        break;
        case 'l': // show json array len
            func |= SHOW_ARRAY_LEN;
        break;
        case 'v': // show json value
            func |= SHOW_VALUE;
        break;
        }
    }

    return func;
}

static void show_usage()
{
    printf("-f: input json file\n");
    printf("-k: json key string\n");
    printf("-s: show all elements of file\n");
    printf("-l: show length of array element\n");
    printf("-v: show vale of element\n");
    printf("example : \n");
    printf("    utils -f vmcfg.json -s\n");
}

int main(int argc, char** argv)
{
    char* path;
    struct json_object *json_obj;
    char json_file[STR_LEN];
    char json_key[STR_LEN];
    unsigned long func = 0x0;

    if(argc < 2) {
        show_usage();
        return 1;
    }

    func = parse_paramegers(argc, argv, &json_file[0], &json_key[0]);
    json_obj = json_object_from_file(json_file);

    switch(func) {
    case SHOW_JSON:
        show_json(json_obj);
    break;
    case SHOW_ARRAY_LEN:
        show_json_array_len(json_key, json_obj);
    break;
    case SHOW_VALUE:
        show_json_value(json_key, json_obj);
    break;
    }
    return 0;
}

