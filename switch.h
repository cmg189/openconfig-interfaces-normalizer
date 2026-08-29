



#ifndef SWITCH_H
#define SWITCH_H




#define SWITCH_LOG_LVL(lvl, msg, ...) \
    do { \
        fprintf(stderr, "[%s] %s(%d) %s: " msg "\n" , lvl, __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
    } while(0)

#define SWITCH_LOG_INFO(msg, ...) SWITCH_LOG_LVL("INFO", msg, ##__VA_ARGS__)
#define SWITCH_LOG_ERROR(msg, ...) SWITCH_LOG_LVL("ERROR", msg, ##__VA_ARGS__)

// used for return codes
typedef enum
{
    SWITCH_OK = 0,  // sucessful
    SWITCH_CFG_PRESENT = 1, // configuration present
    SWITCH_ERR_NOTFOUND = 2, // expected data not found
    SWITCH_ERR_INVAL = 3, // invalid data
    SWITCH_ERR_NULL_ARG = 4 // required argument is null
} switch_status_e;


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




