#ifndef _CMPIOSBASE_TOKENRINGPORT_H_
#define _CMPIOSBASE_TOKENRINGPORT_H_

/*
 * cmpiOSBase_TokenRingPort.h
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
 * CIM class Linux_TokenRingPort.
 *
*/


/* ---------------------------------------------------------------------------*/

#include "cmpidt.h"

/* ---------------------------------------------------------------------------*/

static char * _ClassName = "Linux_TokenRingPort";

/* ---------------------------------------------------------------------------*/


/* method to create a CMPIObjectPath of this class                            */

CMPIObjectPath * _makePath_TokenRingPort( const CMPIBroker * _broker,
                 const CMPIContext * ctx, 
                 const CMPIObjectPath * cop,
		 const struct cim_netPort * sptr,
                 CMPIStatus * rc);


/* method to create a CMPIInstance of this class                              */

CMPIInstance * _makeInst_TokenRingPort( const CMPIBroker * _broker,
               const CMPIContext * ctx, 
               const CMPIObjectPath * cop,
	       const char ** properties,
	       const struct cim_netPort * sptr,
               CMPIStatus * rc);


/* ---------------------------------------------------------------------------*/

#endif

