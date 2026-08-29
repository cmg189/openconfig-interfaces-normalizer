



#ifndef SWITCH_H
#define SWITCH_H


#define MAX_IF_NAME_SZ 64

// per interface configuration
typedef struct switch_port
{
    char if_name[MAX_IF_NAME_SZ];
    char description[128];
    char type[64];
    char speed[64];
    char advertised_speed[64];
    int enabled;
    int mtu;
    int auto_negotiate;
    struct switch_port *next;
} switch_port_t;

// overall switch configuration
typedef struct switch_cfg
{
    switch_port_t *switch_port_head;
} switch_cfg_t;




#endif  /* SWITCH_H */




