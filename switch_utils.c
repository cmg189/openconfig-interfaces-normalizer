#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#include "switch.h"
#include "switch_utils.h"




void switch_cfg_output_config(switch_cfg_t *cfg)
{
    switch_port_t *port = NULL;

    if(!cfg)
    {
        fprintf(stderr, "[ERROR] %s(%d) %s: passing null cfg\n", __FILE__, __LINE__, __func__);
        return;
    }

    port = cfg->switch_port_head;
    if(!port)
    {
        printf("No interface configuration found\n");
        return;
    }

    printf("Interface configuration\n\n");

    while(port)
    {
        printf("port: %s\n", port->if_name);
        printf("    type: %s\n", port->type);
        printf("    description: %s\n", port->description);
        printf("    enabled: %d\n", port->enabled);
        printf("    speed: %s\n", port->speed);
        printf("    advertised_speed: %s\n", port->advertised_speed);
        printf("    mtu: %d\n", port->mtu);
        printf("    auto_negotiate: %d\n", port->auto_negotiate);

        port = port->next;
    }

    return;
}

void switch_cfg_cleanup_ports(switch_cfg_t *cfg)
{
    switch_port_t *port = NULL;

    if(!cfg)
    {
        fprintf(stderr, "[ERROR] %s(%d) %s: passing null cfg\n", __FILE__, __LINE__, __func__);
        return;
    }

    // free linked list memory
    while(cfg->switch_port_head)
    {
        port = cfg->switch_port_head;
        cfg->switch_port_head = cfg->switch_port_head->next;
        port->next = NULL;
        free(port);
    }

    return;
}

static void switch_cfg_insert_port(switch_port_t *new_port, switch_cfg_t *cfg)
{
    switch_port_t *previous_port = NULL;
    switch_port_t *next_port = NULL;

    if(!new_port || !cfg)
    {
        return;
    }

    // find a space in the linked list to insert into based on ascending alphabetical order
    previous_port = cfg->switch_port_head;
    next_port = cfg->switch_port_head;
    while( previous_port && next_port && strcmp(next_port->if_name, new_port->if_name) <= 0 )
    {
        previous_port = next_port;
        next_port = next_port->next;
    }

    if(previous_port == next_port && previous_port == cfg->switch_port_head)
    {
        // add as head of list
        new_port->next = previous_port;
        cfg->switch_port_head = new_port;
    }
    else
    {
        // append or insert to list
        new_port->next = previous_port->next;
        previous_port->next = new_port;
    }

    return;
}

static switch_port_t *switch_cfg_new_port(const char *if_name, switch_cfg_t *cfg)
{
    switch_port_t *new_port = NULL;

    if(!if_name || !cfg)
    {
        return new_port;
    }

    // initalize new port with default values and insert into linked list
    new_port = calloc(1, sizeof(switch_port_t));
    if(new_port)
    {
        strlcpy(new_port->if_name, if_name, sizeof(new_port->if_name));
        strlcpy(new_port->type, "UNKNOWN", sizeof(new_port->type));
        strlcpy(new_port->description, "N/A", sizeof(new_port->description));
        strlcpy(new_port->speed, "UNKNOWN", sizeof(new_port->speed));
        strlcpy(new_port->advertised_speed, "UNKNOWN", sizeof(new_port->advertised_speed));
        new_port->enabled = -1;
        new_port->mtu = -1;
        new_port->auto_negotiate = -1;

        switch_cfg_insert_port(new_port, cfg);
    }
    else
    {
        fprintf(stderr, "[ERROR] %s(%d) %s: calloc() failed for port:%s error_num:%d error_str:%s\n", __FILE__, __LINE__, __func__, if_name, errno, strerror(errno));
    }

    return new_port;
}

static switch_port_t *switch_cfg_get_port(const char *if_name, const switch_cfg_t *cfg)
{
    switch_port_t *port = NULL;

    if(!if_name || !cfg || !cfg->switch_port_head)
    {
        return port;
    }

    // itterate through ports and return the port with matching name
    port = cfg->switch_port_head;
    while(port)
    {
        if( !strcmp(port->if_name, if_name) )
        {
            break;
        }
        port = port->next;
    }

    return port;
}

void switch_cfg_add_port(const char *if_name, switch_cfg_t *cfg)
{
    switch_port_t *port = NULL;

    if(!if_name || !cfg)
    {
        return;
    }

    // create new port if one does not exist
    port = switch_cfg_get_port(if_name, cfg);
    if(!port)
    {
        port = switch_cfg_new_port(if_name, cfg);
    }

    return;
}

void switch_cfg_set_port_type(const char *if_name, const char *type, switch_cfg_t *cfg)
{
    switch_port_t *port = NULL;

    if(!if_name || !type || !cfg)
    {
        return;
    }

    // find port and set type
    port = switch_cfg_get_port(if_name, cfg);
    if(port)
    {
        strlcpy(port->type, type, sizeof(port->type));
    }

    return;
}

void switch_cfg_set_port_description(const char *if_name, const char *desc, switch_cfg_t *cfg)
{
    switch_port_t *port = NULL;

    if(!if_name || !desc || !cfg)
    {
        return;
    }

    // find port and set description
    port = switch_cfg_get_port(if_name, cfg);
    if(port)
    {
        strlcpy(port->description, desc, sizeof(port->description));
    }

    return;
}

void switch_cfg_set_port_enabled(const char *if_name, const bool enabled, switch_cfg_t *cfg)
{
    switch_port_t *port = NULL;

    if(!if_name || !cfg)
    {
        return;
    }

    // find port and set enabled
    port = switch_cfg_get_port(if_name, cfg);
    if(port)
    {
        port->enabled = enabled ? 1 : 0;
    }

    return;
}

void switch_cfg_set_port_mtu(const char *if_name, const int mtu, switch_cfg_t *cfg)
{
    switch_port_t *port = NULL;

    if(!if_name || !cfg)
    {
        return;
    }

    // find port and set mtu
    port = switch_cfg_get_port(if_name, cfg);
    if(port)
    {
        port->mtu = mtu;
    }

    return;
}

void switch_cfg_set_port_speed(const char *if_name, const char *speed, switch_cfg_t *cfg)
{
    switch_port_t *port = NULL;

    if(!if_name || !speed || !cfg)
    {
        return;
    }

    // find port and set speed
    port = switch_cfg_get_port(if_name, cfg);
    if(port)
    {
        strlcpy(port->speed, speed, sizeof(port->speed));
    }

    return;
}

void switch_cfg_set_port_advertised_speed(const char *if_name, const char *speed, switch_cfg_t *cfg)
{
    switch_port_t *port = NULL;

    if(!if_name || !speed || !cfg)
    {
        return;
    }

    // find port and set advertised_speed
    port = switch_cfg_get_port(if_name, cfg);
    if(port)
    {
        strlcpy(port->advertised_speed, speed, sizeof(port->advertised_speed));
    }

    return;
}

void switch_cfg_set_port_auto_negotiate(const char *if_name, const bool autoneg, switch_cfg_t *cfg)
{
    switch_port_t *port = NULL;

    if(!if_name || !cfg)
    {
        return;
    }

    // find port and set auto_negotiate
    port = switch_cfg_get_port(if_name, cfg);
    if(port)
    {
        port->auto_negotiate = autoneg ? 1 : 0;
    }

    return;
}




