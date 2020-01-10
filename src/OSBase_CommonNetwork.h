#ifndef _OSBASE_COMMONNETWORK_H_
#define _OSBASE_COMMONNETWORK_H_

/*
 * OSBase_CommonNetwork.h
 *
 * (C) Copyright IBM Corp. 2002, 2009
 *
 * THIS FILE IS PROVIDED UNDER THE TERMS OF THE ECLIPSE PUBLIC LICENSE
 * ("AGREEMENT"). ANY USE, REPRODUCTION OR DISTRIBUTION OF THIS FILE
 * CONSTITUTES RECIPIENTS ACCEPTANCE OF THE AGREEMENT.
 *
 * You can obtain a current copy of the Eclipse Public License from
 * http://www.opensource.org/licenses/eclipse-1.0.php
 *
 * Author:       Heidi Neumann <heidineu@de.ibm.com>
 * Contributors: 
 *
 * Description: 
 * This file defines the interfaces for the common resource access 
 * implementation for network instrumentation.
 * 
*/

/* ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------*/

unsigned short _get_port_status( const char * id );

char * _get_ipProtocolEndpoint_name( const char * id );

/* ---------------------------------------------------------------------------*/

struct cim_netPort {
  char             * name;
  char             * mac_addr;
  unsigned short     linkTec;
  unsigned short     type;
  unsigned short     enabled;
  unsigned long long speed; 
  unsigned long long maxSpeed;
  //  void * spec;           // for future use 
};

struct netPortList {
  struct cim_netPort * sptr ;
  struct netPortList * next ;
};


int enum_all_netPorts( struct netPortList ** lptr );
int get_netPort_data( const char * id, unsigned short type, struct cim_netPort ** sptr );

void free_netPortList( struct netPortList * lptr );
void free_netPort( struct cim_netPort * sptr );


/* ---------------------------------------------------------------------------*/

#ifdef __cplusplus
   }
#endif

/* ---------------------------------------------------------------------------*/

#endif


