#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include <json-c/json.h>
#include <json-c/json_pointer.h>
#include <json-c/json_object.h>

#include "switch.h"
#include "switch_utils.h"
#include "switch_generate.h"




void openconfig_interfaces_interface_ethernet_config(const json_object *config_obj)
{
    json_object *value = NULL;
    char speed[128] = { 0 };

    if( json_object_object_get_ex(config_obj, "auto-negotiate", &value) )
    {
        printf("    auto-negotiate: %c\n", json_object_get_boolean(value) ? 'T' : 'F');
    }

    // handle values with and without prefix: 'openconfig-if-ethernet:'
    // example values: 'openconfig-if-ethernet:SPEED_25GB' 'SPEED_25GB'
    if( json_object_object_get_ex(config_obj, "port-speed", &value) && json_object_get_string(value) )
    {
        const char *tmp_str = json_object_get_string(value);
        const char *delim = strchr(tmp_str, ':');

        if(delim)
        {
            tmp_str = delim + 1;  // remove prefix openconfig-if-ethernet:
        }

        if( !strncmp(tmp_str, "SPEED_", sizeof("SPEED_") - 1) )
        {
            tmp_str += sizeof("SPEED_") - 1;  // remove prefix SPEED_
        }

        strlcpy(speed, tmp_str, sizeof(speed));
        printf("    port-speed: %s\n", speed);
    }

    // handle leafs with and without prefix: 'openconfig-if-ethernet-ext2:'
    // append Mbps unit EX: 25000 -> 25000Mbps
    if( json_object_object_get_ex(config_obj, "openconfig-if-ethernet-ext2:advertised-speed", &value) ||
        json_object_object_get_ex(config_obj, "advertised-speed", &value)
    )
    {
        const char *tmp_str = json_object_get_string(value);

        if( tmp_str && strlen(tmp_str) )
        {
            snprintf(speed, sizeof(speed), "%s Mbps", tmp_str);
            printf("    %s\n", speed);
        }
    }

    return;
}

void openconfig_interfaces_interface(const json_object *interfaces_obj)
{
    const size_t num_interfaces = json_object_array_length(interface_obj);
    json_object *array_obj = NULL;
    json_object *c1 = NULL;
    json_object *c2 = NULL;
    json_object *value = NULL;

    if(!num_interfaces)
    {
        printf("[INFO] %s(%d) %s: no interface configuration present\n", __FILE__, __LINE__, __func__);
        return;
    }
    printf("[INFO] %s(%d) %s: %zu interfaces configured\n", __FILE__, __LINE__, __func__, num_interfaces);

    // itterate through openconfig-interfaces:interfaces/interface[NAME]
    for(size_t i=0; i< num_interfaces; i++)
    {
        switch_status_e rc = SWITCH_OK;
        char if_name[64] = { 0 };

        array_obj = json_object_array_get_idx(interface_obj, i);

        if( json_object_object_get_ex(array_obj, "name", &value) && json_object_get_string(value) )
        {
            printf("interface #%zu %s\n", i+1, json_object_get_string(value));
        }
        else
        {
            fprintf(stderr, "[ERROR] %s(%d) %s: unable to get key:NAME from interface[%zu]\n", __FILE__, __LINE__, __func__, i);
            continue;
        }

        // interface[NAME]/config
        if( json_object_object_get_ex(array_obj, "config", &c1) )
        {
            if( json_object_object_get_ex(c1, "enabled", &value) )
            {
                printf("    enabled: %c\n", json_object_get_boolean(value) ? 'T' : 'F');
            }

            // handle values with and without prefix 'iana-if-type:'
            if( json_object_object_get_ex(c1, "type", &value) )
            {
                const char *type_str = json_object_get_string(value);
                const char *delim = strchr(type_str, ':');
                if(delim)
                {
                    type_str = delim + 1;  // remove prefix
                }
                printf("    type: %s\n", type_str);
            }

            if( json_object_object_get_ex(c1, "description", &value) )
            {
                const char *desc = json_object_get_string(value);
                if( desc && strlen(desc) )
                {
                    printf("    description: %s\n", desc);
                }
            }

            if( json_object_object_get_ex(c1, "mtu", &value) )
            {
                printf("    mtu: %d\n", json_object_get_int(value));
            }
        }

        // interface[NAME]/openconfig-if-ethernet:ethernet/config
        if( json_object_object_get_ex(array_obj, "openconfig-if-ethernet:ethernet", &c1) && json_object_object_get_ex(c1, "config", &c2) )
        {
            openconfig_interfaces_interface_ethernet_config(c2);
        }
    }

    return;
}

void openconfig_interfaces(const json_object *interfaces_obj)
{
    json_object *c1 = NULL;
    json_object *c2 = NULL;

    if( json_object_object_get_ex(interfaces_obj, "openconfig-interfaces:interfaces", &c1) )
    {
        if( json_object_object_get_ex(c1, "interface", &c2) )
        {
            openconfig_interfaces_interface(c2);  // openconfig-interfaces:interfaces/interface
        }
        else
        {
            printf("[INFO] %s(%d) %s: no interface configuration present\n", __FILE__, __LINE__, __func__);
        }
    }
    else
    {
        fprintf(stderr, "[ERROR] %s(%d) %s: openconfig-interfaces:interfaces not found in json:%s\n", __FILE__, __LINE__, __func__, json_object_get_string(interfaces_obj));
    }

    return;
}




