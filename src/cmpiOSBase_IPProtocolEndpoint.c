/*
 * cmpiOSBase_IPProtocolEndpoint.c
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
 * This is the factory implementation for creating instances of CIM
 * class Linux_IPProtocolEndpoint.
 *
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cmpidt.h"
#include "cmpimacs.h"

#include "cmpiOSBase_Common.h"
#include "OSBase_Common.h"
#include "OSBase_CommonNetwork.h"

#include "cmpiOSBase_IPProtocolEndpoint.h"
#include "OSBase_IPProtocolEndpoint.h"

/* ---------------------------------------------------------------------------*/
/* private declarations                                                       */


/* ---------------------------------------------------------------------------*/



/* ---------------------------------------------------------------------------*/
/*                            Factory functions                               */
/* ---------------------------------------------------------------------------*/

/* ---------- method to create a CMPIObjectPath of this class ----------------*/

CMPIObjectPath * _makePath_IPProtocolEndpoint( const CMPIBroker * _broker,
                 const CMPIContext * ctx, 
                 const CMPIObjectPath * ref,
		 const struct cim_ipProtocolEndpoint * sptr,
		 CMPIStatus * rc) {
  CMPIObjectPath * op = NULL;
 
  _OSBASE_TRACE(2,("--- _makePath_IPProtocolEndpoint() called"));

  /* the sblim-cmpi-base package offers some tool methods to get common
   * system datas 
   * CIM_HOST_NAME contains the unique hostname of the local system 
  */ 
  if( !get_system_name() ) {   
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "no host name found" );
    _OSBASE_TRACE(2,("--- _makePath_IPProtocolEndpoint() failed : %s",CMGetCharPtr(rc->msg)));
    goto exit;
  }

  op = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(ref,rc)), 
			_ClassName, rc );
  if( CMIsNullObject(op) ) { 
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "Create CMPIObjectPath failed." ); 
    _OSBASE_TRACE(2,("--- _makePath_IPProtocolEndpoint() failed : %s",CMGetCharPtr(rc->msg)));
    goto exit; 
  }

  CMAddKey(op, "SystemCreationClassName", CSCreationClassName, CMPI_chars);  
  CMAddKey(op, "SystemName", get_system_name(), CMPI_chars);
  CMAddKey(op, "CreationClassName", _ClassName, CMPI_chars);  
  CMAddKey(op, "Name", sptr->name, CMPI_chars);
      
 exit:
  _OSBASE_TRACE(2,("--- _makePath_IPProtocolEndpoint() exited"));
  return op;                
}

/* ----------- method to create a CMPIInstance of this class ----------------*/

CMPIInstance * _makeInst_IPProtocolEndpoint( const CMPIBroker * _broker,
               const CMPIContext * ctx, 
               const CMPIObjectPath * ref,
	       const char ** properties,
	       const struct cim_ipProtocolEndpoint * sptr,
	       CMPIStatus * rc) {
  CMPIObjectPath *  op       = NULL;
  CMPIInstance   *  ci       = NULL;
  const char     ** keys     = NULL;
  int               keyCount = 0;
#ifndef CIM26COMPAT
  unsigned short    status   = 2;       /* Enabled */
#endif

  _OSBASE_TRACE(2,("--- _makeInst_IPProtocolEndpoint() called"));

  /* the sblim-cmpi-base package offers some tool methods to get common
   * system datas 
   * CIM_HOST_NAME contains the unique hostname of the local system 
  */
  if( !get_system_name() ) {   
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "no host name found" );
    _OSBASE_TRACE(2,("--- _makeInst_IPProtocolEndpoint() failed : %s",CMGetCharPtr(rc->msg)));
    goto exit;
  }

  op = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(ref,rc)), 
			_ClassName, rc );
  if( CMIsNullObject(op) ) { 
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "Create CMPIObjectPath failed." ); 
    _OSBASE_TRACE(2,("--- _makeInst_IPProtocolEndpoint() failed : %s",CMGetCharPtr(rc->msg)));
    goto exit; 
  }

  ci = CMNewInstance( _broker, op, rc);
  if( CMIsNullObject(ci) ) { 
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "Create CMPIInstance failed." ); 
    _OSBASE_TRACE(2,("--- _makeInst_IPProtocolEndpoint() failed : %s",CMGetCharPtr(rc->msg)));
    goto exit; 
  }
      
  /* set property filter */
  keys = calloc(5,sizeof(char*));
  keys[0] = strdup("SystemCreationClassName");
  keys[1] = strdup("SystemName");
  keys[2] = strdup("CreationClassName");
  keys[3] = strdup("Name");
  CMSetPropertyFilter(ci,properties,keys);
  for( ;keys[keyCount]!=NULL;keyCount++) { free((char*)keys[keyCount]); }
  free(keys);

  CMSetProperty( ci, "SystemCreationClassName", CSCreationClassName, CMPI_chars ); 
  CMSetProperty( ci, "SystemName", get_system_name(), CMPI_chars );
  CMSetProperty( ci, "CreationClassName", _ClassName, CMPI_chars ); 
  CMSetProperty( ci, "Name", sptr->name, CMPI_chars );

  CMSetProperty( ci, "NameFormat", "IP", CMPI_chars);
  CMSetProperty( ci, "ProtocolType", (CMPIValue*)&(sptr->type), CMPI_uint16);
  CMSetProperty( ci, "OtherTypeDescription", "NULL", CMPI_chars);

  if( sptr->address != NULL ) { CMSetProperty( ci, "IPv4Address", sptr->address, CMPI_chars); }
  else { CMSetProperty( ci, "IPv4Address", "NULL", CMPI_chars); }
  if( sptr->subnetmask != NULL ) { CMSetProperty( ci, "SubnetMask", sptr->subnetmask, CMPI_chars); }
  else { CMSetProperty( ci, "SubnetMask", "NULL", CMPI_chars); }
  CMSetProperty( ci, "IPv6Address", "NULL", CMPI_chars);

  CMSetProperty( ci, "IPVersionSupport", (CMPIValue*)&(sptr->version), CMPI_uint16);
  
  CMSetProperty( ci, "Caption", "Protocol Endpoint for IP (Internet Protocol) ", CMPI_chars);
  CMSetProperty( ci, "Description", "A communication point to send and receive data. This class is dedicated to link IP intefaces to Logical Networks.", CMPI_chars);
  CMSetProperty( ci, "Status", "OK", CMPI_chars);

  /* 2.7 */
#ifndef CIM26COMPAT
  CMSetProperty( ci, "ElementName", sptr->name, CMPI_chars);  
  CMSetProperty( ci, "EnabledState", (CMPIValue*)&(sptr->enabled), CMPI_uint16);
  CMSetProperty( ci, "OtherEnabledState", "NULL", CMPI_chars);
  CMSetProperty( ci, "RequestedState", (CMPIValue*)&(sptr->enabled), CMPI_uint16);
  CMSetProperty( ci, "EnabledDefault", (CMPIValue*)&(status), CMPI_uint16);
#endif

 exit:
  _OSBASE_TRACE(2,("--- _makeInst_IPProtocolEndpoint() exited"));
  return ci;
}



/* ---------------------------------------------------------------------------*/
/*                 end of cmpiOSBase_IPProtocolEndpoint.c                     */
/* ---------------------------------------------------------------------------*/

