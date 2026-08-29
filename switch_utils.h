/*man
    MODULE
        switch_utils.h - Switch utilities global definitions
    AUTHOR
        cmg189
    DESCRIPTION
        This module contains global utility functions to be used in populating switch data structures
endman*/

#ifndef SWITCH_UTILS_H
#define SWITCH_UTILS_H

/*man
NAME
        switch_cfg_output_config - Output configuration to stdout
    DESCRIPTION
        This function outputs the switch configuration to stdout
    INPUTS
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        void
endman*/
void switch_cfg_output_config(switch_cfg_t *cfg);

/*man
    NAME
        switch_cfg_cleanup_ports - Free allocated memory from data structure
    DESCRIPTION
        This function frees allocated memory from the switch_port_t structure found in switch_cfg_t
    INPUTS
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        void
endman*/
void switch_cfg_cleanup_ports(switch_cfg_t *cfg);

/*man
    NAME
        switch_cfg_add_port - Determines if a new entry in the switch_port_t structure linked list is needed
    DESCRIPTION
        This function determines if a new entry in the switch_port_t structure linked list is needed
    INPUTS
        const char *if_name - Name of interface acting as a key among entries in linked list of switch_port_t structures
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        switch_status_e - Returns status resulting from adding a port
endman*/
switch_status_e switch_cfg_add_port(const char *if_name, switch_cfg_t *cfg);

/*man
    NAME
        switch_cfg_set_port_type - Sets the port_type member in the switch_port_t structure
    DESCRIPTION
        This function sets the port_type member in the switch_port_t structure
    INPUTS
        const char *if_name - Name of interface acting as a key among entries in linked list of switch_port_t structures
        const char *type - Value to set port_type member
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        switch_status_e - Returns status resulting from setting port_type
endman*/
switch_status_e switch_cfg_set_port_type(const char *if_name, const char *type, switch_cfg_t *cfg);

/*man
    NAME
        switch_cfg_set_port_description - Sets the description member in the switch_port_t structure
    DESCRIPTION
        This function sets the description member in the switch_port_t structure
    INPUTS
        const char *if_name - Name of interface acting as a key among entries in linked list of switch_port_t structures
        const char *desc - Value to set description member
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        switch_status_e - Returns status resulting from setting description
endman*/
switch_status_e switch_cfg_set_port_description(const char *if_name, const char *desc, switch_cfg_t *cfg);

/*man
    NAME
        switch_cfg_set_port_enabled - Sets the enabled member in the switch_port_t structure
    DESCRIPTION
        This function sets the enabled member in the switch_port_t structure
    INPUTS
        const char *if_name - Name of interface acting as a key among entries in linked list of switch_port_t structures
        const bool enabled - Value to set enabled member
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        switch_status_e - Returns status resulting from setting enabled
endman*/
switch_status_e switch_cfg_set_port_enabled(const char *if_name, const bool enabled, switch_cfg_t *cfg);

/*man
    NAME
        switch_cfg_set_port_mtu - Sets the mtu member in the switch_port_t structure
    DESCRIPTION
        This function sets the mtu member in the switch_port_t structure
    INPUTS
        const char *if_name - Name of interface acting as a key among entries in linked list of switch_port_t structures
        const int mtu - Value to set mtu member
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        switch_status_e - Returns status resulting from setting mtu
endman*/
switch_status_e switch_cfg_set_port_mtu(const char *if_name, const int mtu, switch_cfg_t *cfg);

/*man
    NAME
        switch_cfg_set_port_speed - Sets the speed member in the switch_port_t structure
    DESCRIPTION
        This function sets the speed member in the switch_port_t structure
    INPUTS
        const char *if_name - Name of interface acting as a key among entries in linked list of switch_port_t structures
        const char *speed - Value to set speed member
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        switch_status_e - Returns status resulting from setting speed
endman*/
switch_status_e switch_cfg_set_port_speed(const char *if_name, const char *speed, switch_cfg_t *cfg);

/*man
    NAME
        switch_cfg_set_port_advertised_speed - Sets the advertised_speed member in the switch_port_t structure
    DESCRIPTION
        This function sets the advertised_speed member in the switch_port_t structure
    INPUTS
        const char *if_name - Name of interface acting as a key among entries in linked list of switch_port_t structures
        const char *speed - Value to set advertised_speed member
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        switch_status_e - Returns status resulting from setting advertised_speed
endman*/
switch_status_e switch_cfg_set_port_advertised_speed(const char *if_name, const char *speed, switch_cfg_t *cfg);

/*man
    NAME
        switch_cfg_set_port_auto_negotiate - Sets the auto_negotiate member in the switch_port_t structure
    DESCRIPTION
        This function sets the auto_negotiate member in the switch_port_t structure
    INPUTS
        const char *if_name - Name of interface acting as a key among entries in linked list of switch_port_t structures
        const bool autoneg - Value to set auto_negotiate member
        switch_cfg_t *cfg - Pointer to switch_cfg_t containing linked list of switch_port_t
    RETURN
        switch_status_e - Returns status resulting from setting auto_negotiate
endman*/
switch_status_e switch_cfg_set_port_auto_negotiate(const char *if_name, const bool autoneg, switch_cfg_t *cfg);




#endif  /* SWITCH_UTILS_H */




