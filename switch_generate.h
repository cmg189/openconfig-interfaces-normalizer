/*man
    MODULE
        switch_generate.h - Switch generate global definitions
    AUTHOR
        cmg189
    DESCRIPTION
        This module contains global functions to be used in generating switch configuration
endman*/

#ifndef SWITCH_GENERATE_H
#define SWITCH_GENERATE_H

/*man
    NAME
        openconfig_interfaces_interface_ethernet_config - Parse configuration from openconfig-interfaces:interfaces/interface[NAME]/ethernet/config
    DESCRIPTION
        This function sets members in the switch_port_t struct
    INPUTS
        const json_object *config_obj - Pointer to json_object containing interface ethernet configuration
        const char *if_name - Name of interface being processed
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        void
endman*/
void openconfig_interfaces_interface_ethernet_config(const json_object *config_obj, const char *if_name, switch_cfg_t *switch_cfg);

/*man
    NAME
        openconfig_interfaces_interface - Parse configuration from openconfig-interfaces:interfaces/interface[NAME]
    DESCRIPTION
        This function sets members in the switch_port_t struct
    INPUTS
        const json_object *interface_obj - Pointer to json_object containing interface configuration
        const char *if_name - Name of interface being processed
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        void
endman*/
void openconfig_interfaces_interface(const json_object *interface_obj, switch_cfg_t *switch_cfg);

/*man
    NAME
        openconfig_interfaces - Starting point of json parsing
    DESCRIPTION
        This function starts the parsing of the openconfig_interfaces model
    INPUTS
        const json_object *interfaces_obj - Pointer to json_object containing entire json of openconfig_interfaces
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        void
endman*/
void openconfig_interfaces(const json_object *interfaces_obj, switch_cfg_t *switch_cfg);




#endif  /* SWITCH_GENERATE_H */




