#ifndef IOPCCFG_H
#define IOPCCFG_H

#include <json.h>
#include <json_object.h>

#define STR_LEN		256

struct query_json_obj_t {
    int isFound;
    char cmp_key[STR_LEN];
    char key_str[STR_LEN];
    enum json_type type;
    struct json_object *obj;
};

void get_json_obj_by_query_obj(struct query_json_obj_t *query_json_obj, struct json_object *json_obj);
void show_json(struct json_object *json_obj);

#endif
