#ifndef _OSBASE_IPPROTOCOLENDPOINT_H_
#define _OSBASE_IPPROTOCOLENDPOINT_H_

/*
 * OSBase_IPProtocolEndpoint.h
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
 * This file defines the interfaces for the resource access implementation 
 * of the CIM class Linux_IPProtocolEndpoint.
 * 
*/

/* ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------------*/

struct cim_ipProtocolEndpoint {
  char         * name;
  char         * address;
  char         * subnetmask;
  unsigned short enabled;
  unsigned short type; 
  unsigned short version;
};

struct ipPEndpointList {
  struct cim_ipProtocolEndpoint * sptr ;
  struct ipPEndpointList        * next ;
};

int enum_all_ipProtocolEndpoints( struct ipPEndpointList ** lptr );
int get_ipProtocolEndpoint_data( const char * id, 
				 struct cim_ipProtocolEndpoint ** sptr );

void free_ipPEndpointList( struct ipPEndpointList * );
void free_ipProtocolEndpoint( struct cim_ipProtocolEndpoint * );


/* ---------------------------------------------------------------------------*/

#ifdef __cplusplus
   }
#endif

/* ---------------------------------------------------------------------------*/

#endif


