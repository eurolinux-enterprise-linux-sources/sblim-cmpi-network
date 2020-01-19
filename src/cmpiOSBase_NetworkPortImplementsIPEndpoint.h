#ifndef _CMPIOSBASE_NETWORKPORTIMPLEMENTSIPENDPOINT_H_
#define _CMPIOSBASE_NETWORKPORTIMPLEMENTSIPENDPOINT_H_

/*
 * cmpiOSBase_NetworkPortImplementsIPEndpoint.h
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
 * Interface Type : Common Magabeablity Programming Interface ( CMPI )
 *
 * Description:
 * This file defines the interfaces for the factory implementation of the
 * CIM class Linux_NetworkPortImplementsIPEndpoint.
 *
*/


/* ---------------------------------------------------------------------------*/

#include "cmpidt.h"

/* ---------------------------------------------------------------------------*/

static char * _ClassName = "Linux_NetworkPortImplementsIPEndpoint";

static char * _RefLeft         = "Antecedent";
static char * _RefRight        = "Dependent";
static char * _RefLeftClass    = "CIM_NetworkPort";
static char * _RefLeftClass_bk = "CIM_NetworkPort";
static char * _RefLeftClassEth = "Linux_EthernetPort";
static char * _RefLeftClassTr  = "Linux_TokenRingPort";
static char * _RefLeftClassLo  = "Linux_LocalLoopbackPort";
static char * _RefRightClass   = "Linux_IPProtocolEndpoint";

/* ---------------------------------------------------------------------------*/


int _assoc_create_inst_NetworkPortImplementsIPEndpoint( const CMPIBroker * _broker,
							const CMPIContext * ctx,
							const CMPIResult * rslt,
							const CMPIObjectPath * cop,
							int inst,
							CMPIStatus * rc);

CMPIInstance * _assoc_get_networkPort_INST( const CMPIBroker * _broker,
					    const CMPIContext * ctx,
					    const CMPIObjectPath * ref,
					    CMPIStatus * rc);

CMPIInstance * _assoc_get_ipEndpoint_INST( const CMPIBroker * _broker,
					   const CMPIContext * ctx,
					   const CMPIObjectPath * ref,
					   CMPIStatus * rc);

int _assoc_NetworkPortImplementsIPEndpoint( const CMPIBroker * _broker,
					    const CMPIContext * ctx,
					    const CMPIResult * rslt,
					    const CMPIObjectPath * ref, 
					    int inst,
					    int associators,
					    CMPIStatus * rc);

CMPIObjectPath * _assoc_get_assoc_OP_NetworkPortImplementsIPEndpoint( 
		 const CMPIBroker * _broker,
		 const CMPIObjectPath * ref_left,
		 const CMPIObjectPath * ref_right,
		 CMPIStatus * rc);

CMPIInstance * _assoc_get_assoc_INST_NetworkPortImplementsIPEndpoint( 
               const CMPIBroker * _broker,
	       const CMPIObjectPath * ref_left,
	       const CMPIObjectPath * ref_right,
	       CMPIStatus * rc);


/* ---------------------------------------------------------------------------*/

#endif

