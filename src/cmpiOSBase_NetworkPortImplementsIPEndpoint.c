/*
 * cmpiOSBase_NetworkPortImplementsIPEndpoint.c
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
 * class Linux_NetworkPortImplementsIPEndpoint.
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

#include "cmpiOSBase_NetworkPortImplementsIPEndpoint.h"

/* ---------------------------------------------------------------------------*/
/* private declarations                                                       */


/* ---------------------------------------------------------------------------*/



/* ---------------------------------------------------------------------------*/
/*                            Factory functions                               */
/* ---------------------------------------------------------------------------*/


int _assoc_create_inst_NetworkPortImplementsIPEndpoint( const CMPIBroker * _broker,
			const CMPIContext * ctx,
			const CMPIResult * rslt,
			const CMPIObjectPath * cop,
			int inst,
			CMPIStatus * rc) {
  CMPIObjectPath  * op  = NULL;
  CMPIEnumeration * en  = NULL;
  CMPIData          data ;
  int               cmdrc = 0;

  _OSBASE_TRACE(2,("--- _assoc_create_inst_NetworkPortImplementsIPEndpoint() called"));

  op = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(cop,rc)),
			_RefRightClass, rc );
  if( CMIsNullObject(op) ) { 
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "Create CMPIObjectPath failed." ); 
    _OSBASE_TRACE(2,("--- _assoc_create_inst_NetworkPortImplementsIPEndpoint() failed : %s",CMGetCharPtr(rc->msg)));
    return -1; 
  }
  
  en = CBEnumInstanceNames( _broker, ctx, op, rc);
  if( en == NULL ) {
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "CBEnumInstanceNames( _broker, ctx, op, rc)" ); 
    _OSBASE_TRACE(2,("--- _assoc_create_inst_NetworkPortImplementsIPEndpoint() failed : %s",CMGetCharPtr(rc->msg)));
    return -1; 
  }

  /* this approach works only from OperatingSystem to the CMPIInstance(s)
   * of the different supported LocalFileSystems
   */

  while( CMHasNext( en, rc) ) {
    data = CMGetNext( en, rc);
    if( data.value.ref == NULL ) {
      CMSetStatusWithChars( _broker, rc, 
			    CMPI_RC_ERR_FAILED, "CMGetNext( en, rc)" ); 
      _OSBASE_TRACE(2,("--- _assoc_create_inst_NetworkPortImplementsIPEndpoint() failed : %s",CMGetCharPtr(rc->msg)));
      return -1; 
    }

    cmdrc = _assoc_NetworkPortImplementsIPEndpoint( _broker, ctx,rslt,data.value.ref,
						    inst,0,rc);
  }

  _OSBASE_TRACE(2,("--- _assoc_create_inst_NetworkPortImplementsIPEndpoint() exited"));
  return 0;
}


CMPIInstance * _assoc_get_networkPort_INST( const CMPIBroker * _broker,
					    const CMPIContext * ctx,
					    const CMPIObjectPath * ref,
					    CMPIStatus * rc) {
  CMPIInstance   * ci          = NULL;
  CMPIObjectPath * op          = NULL;
  CMPIString     * name        = NULL;
  char           * targetClass = NULL;
  char           * ptr         = NULL;
  char           * id          = NULL;

  _OSBASE_TRACE(2,("--- _assoc_get_networkPort_INST() called"));

  name = CMGetKey( ref, "Name", rc).value.string;
  if( name == NULL ) { goto exit; }

  ptr = CMGetCharPtr(name);
  if( strstr(ptr,"eth") != NULL ) { targetClass = _RefLeftClassEth; }
  else if( strstr(ptr,"tr") != NULL ) { targetClass = _RefLeftClassTr; }
  else if( strstr(ptr,"lo") != NULL ) { targetClass = _RefLeftClassLo; }
  else { goto exit; }

  /* tool method call to get the unique name of the system */
  if( !get_system_name() ) {   
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "no host name found" );
    _OSBASE_TRACE(2,("--- _assoc_get_networkPort_INST() failed : %s",CMGetCharPtr(rc->msg)));
    goto exit;
  }

  /* create CMPIObjectPath of subclass of NetworkPort */
  op = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(ref,rc)),
			targetClass, rc );
  if( CMIsNullObject(op) ) { 
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "Create CMPIObjectPath failed." ); 
    _OSBASE_TRACE(2,("--- _assoc_get_networkPort_INST() failed : %s",CMGetCharPtr(rc->msg)));
    goto exit;
  }

  id = calloc(1,(strlen(ptr)-4));
  strcpy(id,ptr+5);

  CMSetNameSpace(op,CMGetCharPtr(CMGetNameSpace(ref,rc)));

  CMAddKey(op, "SystemCreationClassName", CSCreationClassName, CMPI_chars);  
  CMAddKey(op, "SystemName", get_system_name(), CMPI_chars);
  CMAddKey(op, "CreationClassName", targetClass, CMPI_chars);  
  CMAddKey(op, "DeviceID", id, CMPI_chars);

  ci = CBGetInstance(_broker,ctx,op,NULL,rc);
  if( ci == NULL ) {
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "CBGetInstance(_broker,ctx,op,NULL,rc)" ); 
    _OSBASE_TRACE(2,("--- _assoc_get_networkPort_INST() failed : %s",CMGetCharPtr(rc->msg)));
  }

  if(id) free(id);

 exit:
  _OSBASE_TRACE(2,("--- _assoc_get_networkPort_INST() exited"));
  return ci;
}


CMPIInstance * _assoc_get_ipEndpoint_INST( const CMPIBroker * _broker,
					   const CMPIContext * ctx,
					   const CMPIObjectPath * ref,
					   CMPIStatus * rc) {
  CMPIInstance   * ci   = NULL;
  CMPIObjectPath * op   = NULL;
  CMPIData         id;
  char           * name = NULL;

  _OSBASE_TRACE(2,("--- _assoc_get_ipEndpoint_INST() called"));

  id = CMGetKey( ref, "DeviceID", rc);
  if( id.value.string == NULL ) { 
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "CMGetKey( ref, 'DeviceID', rc)" );
    _OSBASE_TRACE(2,("--- _assoc_get_ipEndpoint_INST() failed : %s",CMGetCharPtr(rc->msg)));
    goto exit; 
  }

  /* tool method call to get the unique name of the system */
  if( !get_system_name() ) {   
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "no host name found" );
    _OSBASE_TRACE(2,("--- _assoc_get_ipEndpoint_INST() failed : %s",CMGetCharPtr(rc->msg)));
    goto exit;
  }

  /* create CMPIObjectPath of "Linux_IPProtocolEndpoint" */
  op = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(ref,rc)),
			_RefRightClass, rc );
  if( CMIsNullObject(op) ) { 
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "Create CMPIObjectPath failed." ); 
    _OSBASE_TRACE(2,("--- _assoc_get_ipEndpoint_INST() failed : %s",CMGetCharPtr(rc->msg)));
    goto exit;
  }

  name = _get_ipProtocolEndpoint_name(CMGetCharPtr(id.value.string));

  CMSetNameSpace(op,CMGetCharPtr(CMGetNameSpace(ref,rc)));

  CMAddKey(op, "SystemCreationClassName", CSCreationClassName, CMPI_chars);  
  CMAddKey(op, "SystemName", get_system_name(), CMPI_chars);
  CMAddKey(op, "CreationClassName", _RefRightClass, CMPI_chars);  
  CMAddKey(op, "Name", name, CMPI_chars);

  ci = CBGetInstance(_broker,ctx,op,NULL,rc);
  if( ci == NULL ) {
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "CBGetInstance(_broker,ctx,op,NULL,rc)" ); 
    _OSBASE_TRACE(2,("--- _assoc_get_ipEndpoint_INST() failed : %s",CMGetCharPtr(rc->msg)));
  }

  if(name) free(name);

 exit:
  _OSBASE_TRACE(2,("--- _assoc_get_ipEndpoint_INST() exited"));
  return ci;
}


CMPIObjectPath * _assoc_get_assoc_OP_NetworkPortImplementsIPEndpoint( 
                 const CMPIBroker * _broker,
		 const CMPIObjectPath * ref_left,
		 const CMPIObjectPath * ref_right,
		 CMPIStatus * rc) {
  CMPIObjectPath * op = NULL;
  CMPIInstance   * ci = NULL;

  _OSBASE_TRACE(4,("--- _assoc_get_assoc_OP_NetworkPortImplementsIPEndpoint() called"));

  ci = _assoc_get_assoc_INST_NetworkPortImplementsIPEndpoint(_broker, 
							     ref_left,ref_right,
							     rc);
  if( ci == NULL ) { return NULL; }

  op = CMGetObjectPath(ci,rc); 
  CMSetNameSpace(op,CMGetCharPtr(CMGetNameSpace(ref_left,rc)));

  _OSBASE_TRACE(4,("--- _assoc_get_assoc_OP_NetworkPortImplementsIPEndpoint() exited"));
  return op; 
}


CMPIInstance * _assoc_get_assoc_INST_NetworkPortImplementsIPEndpoint( 
	       const CMPIBroker * _broker,
	       const CMPIObjectPath * ref_left,
	       const CMPIObjectPath * ref_right,
	       CMPIStatus * rc) {
  CMPIObjectPath * op = NULL;
  CMPIInstance   * ci = NULL;

  _OSBASE_TRACE(4,("--- _assoc_get_assoc_INST_NetworkPortImplementsIPEndpoint() called"));

  /* create CMPIObjectPath of this association <_ClassName> */
  op = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(ref_left,rc)),
			_ClassName, rc );
  if( CMIsNullObject(op) ) { 
    CMSetStatusWithChars( _broker, rc, 
			  CMPI_RC_ERR_FAILED, "Create CMPIObjectPath failed." ); 
    _OSBASE_TRACE(4,("--- _assoc_get_assoc_INST_NetworkPortImplementsIPEndpoint() failed : %s",CMGetCharPtr(rc->msg)));
    goto exit;
  }

  ci = CMNewInstance( _broker, op, rc);
  if( CMIsNullObject(ci) ) { 
    CMSetStatusWithChars( _broker, rc,
			  CMPI_RC_ERR_FAILED, "Create CMPIInstance failed." ); 
    _OSBASE_TRACE(4,("--- _assoc_get_assoc_INST_NetworkPortImplementsIPEndpoint() failed : %s",CMGetCharPtr(rc->msg)));
    goto exit;
  }

  CMSetProperty( ci, _RefLeft, (CMPIValue*)&(ref_left), CMPI_ref ); 
  CMSetProperty( ci, _RefRight, (CMPIValue*)&(ref_right), CMPI_ref );

 exit:
  _OSBASE_TRACE(4,("--- _assoc_get_assoc_INST_NetworkPortImplementsIPEndpoint() exited"));
  return ci; 
}


/* combination of int <inst> and int <associators> :
 * 0 0 -> referenceNames()
 * 1 0 -> references()
 * 0 1 -> associatorNames()
 * 1 1 -> associators()
 */

int _assoc_NetworkPortImplementsIPEndpoint( const CMPIBroker * _broker,
					    const CMPIContext * ctx,
					    const CMPIResult * rslt,
					    const CMPIObjectPath * ref,
					    int inst,
					    int associators,
					    CMPIStatus * rc) {
  CMPIInstance   * cis         = NULL;
  CMPIInstance   * ci          = NULL;
  CMPIInstance   * rci         = NULL;
  CMPIObjectPath * op          = NULL;
  CMPIObjectPath * rop         = NULL;
  const char     * targetClass = NULL;
  int              cmdrc       = 0;

  _OSBASE_TRACE(2,("--- _assoc_NetworkPortImplementsIPEndpoint() called"));

  /* check if source instance does exist */
  cis = CBGetInstance(_broker, ctx, ref, NULL, rc);
  if( cis == NULL ) {
    if( rc->rc == CMPI_RC_ERR_FAILED ) {
      CMSetStatusWithChars( _broker, rc,
			    CMPI_RC_ERR_FAILED, "GetInstance of source object failed.");
    }
    if( rc->rc == CMPI_RC_ERR_NOT_FOUND ) {
      CMSetStatusWithChars( _broker, rc,
			    CMPI_RC_ERR_NOT_FOUND, "Source object not found.");
    }
    _OSBASE_TRACE(2,("--- _assoc_NetworkPortImplementsIPEndpoint() failed : %s",
		     CMGetCharPtr(rc->msg)));
    return -1;
  }

  targetClass = _assoc_targetClass_Name(_broker,ref,_RefLeftClass,_RefRightClass,rc);
  if( targetClass == NULL ) { goto exit; }

  if( strcasecmp(targetClass,_RefRightClass) == 0 ) {
    /* returned instances are of type "Linux_IPProtocolEndpoint" */
    ci = _assoc_get_ipEndpoint_INST( _broker, ctx, ref, rc);
  }
  else if( strcasecmp(targetClass,_RefLeftClass) == 0 ) {
    /* returned instances are subclasses of type CIM_NetworkPort */
    ci = _assoc_get_networkPort_INST( _broker, ctx, ref, rc);
  }
  else { goto exit; }

  if( ci == NULL ) {
    CMSetStatus(rc,CMPI_RC_OK);
    goto exit;
  }

  op = CMGetObjectPath(ci,rc);
  if( op == NULL ) { goto exit; }
  CMSetNameSpace(op,CMGetCharPtr(CMGetNameSpace(ref,rc)));

  if( associators == 0 ) {
    /* references() || referenceNames() */
    if( inst == 0 ) {
      if( strcasecmp(targetClass,_RefRightClass) == 0 ) {
	rop = _assoc_get_assoc_OP_NetworkPortImplementsIPEndpoint( _broker, ref, op,rc );
      }
      else if( strcasecmp(targetClass,_RefLeftClass) == 0 ) {
	rop = _assoc_get_assoc_OP_NetworkPortImplementsIPEndpoint( _broker, op, ref, rc );
      }
      if( op == NULL ) { goto exit; }
      CMReturnObjectPath( rslt, rop );
    }
    else { /* inst == 1 */
      if( strcasecmp(targetClass,_RefRightClass) == 0 ) {
	rci = _assoc_get_assoc_INST_NetworkPortImplementsIPEndpoint( _broker, ref, op,rc );
      }
      else if( strcasecmp(targetClass,_RefLeftClass) == 0 ) {
	rci = _assoc_get_assoc_INST_NetworkPortImplementsIPEndpoint( _broker, op, ref, rc );
      }
      if( rci == NULL ) { goto exit; }
      CMReturnInstance( rslt, rci );
    }
  }
  else { /* associators == 1 */
    /* associators() || associatorNames() */
    if( inst == 0 ) { 
      CMReturnObjectPath( rslt, op ); 
    }
    else { /* inst == 1 */
      CMReturnInstance( rslt, ci );
    }
  }  

 exit:
  _OSBASE_TRACE(2,("--- _assoc_NetworkPortImplementsIPEndpoint() exited"));
  return cmdrc;
}


/* ---------------------------------------------------------------------------*/
/*          end of cmpiOSBase_NetworkPortImplementsIPEndpoint.c               */
/* ---------------------------------------------------------------------------*/

