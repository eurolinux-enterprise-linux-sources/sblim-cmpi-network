/*
 * cmpiOSBase_NetworkPortImplementsIPEndpointProvider.c
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
 * Interface Type : Common Manageability Programming Interface ( CMPI )
 *
 * Description: 
 * 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cmpidt.h"
#include "cmpift.h"
#include "cmpimacs.h"

#include "OSBase_Common.h"
#include "cmpiOSBase_Common.h"
#include "cmpiOSBase_NetworkPortImplementsIPEndpoint.h"

static const CMPIBroker * _broker;

/* ---------------------------------------------------------------------------*/
/* private declarations                                                       */
#ifdef CMPI_VER_100
#define OSBase_NetworkPortImplementsIPEndpointProviderSetInstance OSBase_NetworkPortImplementsIPEndpointProviderModifyInstance 
#endif


/* ---------------------------------------------------------------------------*/



/* ---------------------------------------------------------------------------*/
/*                      Instance Provider Interface                           */
/* ---------------------------------------------------------------------------*/


CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderCleanup( CMPIInstanceMI * mi, 
           const CMPIContext * ctx, CMPIBoolean terminate) { 
  _OSBASE_TRACE(1,("--- %s CMPI Cleanup() called",_ClassName));
  _OSBASE_TRACE(1,("--- %s CMPI Cleanup() exited",_ClassName));
  CMReturn(CMPI_RC_OK);
}

CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderEnumInstanceNames( CMPIInstanceMI * mi, 
           const CMPIContext * ctx, 
           const CMPIResult * rslt, 
           const CMPIObjectPath * ref) { 
  CMPIStatus rc    = {CMPI_RC_OK, NULL};
  int        refrc = 0;
  
  _OSBASE_TRACE(1,("--- %s CMPI EnumInstanceNames() called",_ClassName));

  refrc = _assoc_create_inst_NetworkPortImplementsIPEndpoint( _broker, ctx, 
							      rslt, ref, 0, 
							      &rc);

  if( refrc != 0 ) { 
    if( rc.msg != NULL ) {
      _OSBASE_TRACE(1,("--- %s CMPI EnumInstanceNames() failed : %s",_ClassName,CMGetCharPtr(rc.msg)));
    }
    else {
      _OSBASE_TRACE(1,("--- %s CMPI EnumInstanceNames() failed",_ClassName));
    }
    return rc;
  }

  CMReturnDone( rslt );
  _OSBASE_TRACE(1,("--- %s CMPI EnumInstanceNames() exited",_ClassName));
  return rc;
}

CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderEnumInstances( CMPIInstanceMI * mi, 
           const CMPIContext * ctx, 
           const CMPIResult * rslt, 
           const CMPIObjectPath * ref, 
           const char ** properties) { 
  CMPIStatus rc    = {CMPI_RC_OK, NULL};
  int        refrc = 0;

  _OSBASE_TRACE(1,("--- %s CMPI EnumInstances() called",_ClassName));

  refrc = _assoc_create_inst_NetworkPortImplementsIPEndpoint( _broker, ctx, 
							      rslt, ref, 1, 
							      &rc);

  if( refrc != 0 ) {
    if( rc.msg != NULL ) {
      _OSBASE_TRACE(1,("--- %s CMPI EnumInstances() failed : %s",_ClassName,CMGetCharPtr(rc.msg)));
    }
    else {
      _OSBASE_TRACE(1,("--- %s CMPI EnumInstances() failed",_ClassName));
    }
    return rc; 
  }

  CMReturnDone( rslt );
  _OSBASE_TRACE(1,("--- %s CMPI EnumInstances() exited",_ClassName));
  return rc;
}

CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderGetInstance( CMPIInstanceMI * mi, 
           const CMPIContext * ctx, 
           const CMPIResult * rslt, 
           const CMPIObjectPath * cop, 
           const char ** properties) {
  const CMPIInstance * ci = NULL;
  CMPIStatus     rc = {CMPI_RC_OK, NULL};

  _OSBASE_TRACE(1,("--- %s CMPI GetInstance() called",_ClassName));
  
  ci = _assoc_get_inst( _broker, ctx, cop, _ClassName, _RefLeft, _RefRight, &rc);

  if( ci == NULL ) { 
    if( rc.msg != NULL ) {
      _OSBASE_TRACE(1,("--- %s CMPI GetInstance() failed : %s",_ClassName,CMGetCharPtr(rc.msg)));
    }
    else {
      _OSBASE_TRACE(1,("--- %s CMPI GetInstance() failed",_ClassName));
    }
    return rc; 
  }

  CMReturnInstance( rslt, ci );
  CMReturnDone(rslt);
  _OSBASE_TRACE(1,("--- %s CMPI GetInstance() exited",_ClassName));
  return rc;
}

CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderCreateInstance( CMPIInstanceMI * mi, 
           const CMPIContext * ctx, 
           const CMPIResult * rslt, 
           const CMPIObjectPath * cop, 
           const CMPIInstance * ci) {
  CMPIStatus rc = {CMPI_RC_OK, NULL};

  _OSBASE_TRACE(1,("--- %s CMPI CreateInstance() called",_ClassName));

  CMSetStatusWithChars( _broker, &rc, 
			CMPI_RC_ERR_NOT_SUPPORTED, "CIM_ERR_NOT_SUPPORTED" ); 

  _OSBASE_TRACE(1,("--- %s CMPI CreateInstance() exited",_ClassName));
  return rc;
}

CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderSetInstance( CMPIInstanceMI * mi, 
           const CMPIContext * ctx, 
           const CMPIResult * rslt, 
           const CMPIObjectPath * cop,
           const CMPIInstance * ci, 
           const char **properties) {
  CMPIStatus rc = {CMPI_RC_OK, NULL};

  _OSBASE_TRACE(1,("--- %s CMPI SetInstance() called",_ClassName));

  CMSetStatusWithChars( _broker, &rc, 
			CMPI_RC_ERR_NOT_SUPPORTED, "CIM_ERR_NOT_SUPPORTED" ); 

  _OSBASE_TRACE(1,("--- %s CMPI SetInstance() exited",_ClassName));
  return rc;
}

CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderDeleteInstance( CMPIInstanceMI * mi, 
           const CMPIContext * ctx, 
           const CMPIResult * rslt, 
           const CMPIObjectPath * cop) {
  CMPIStatus rc = {CMPI_RC_OK, NULL}; 

  _OSBASE_TRACE(1,("--- %s CMPI DeleteInstance() called",_ClassName));

  CMSetStatusWithChars( _broker, &rc, 
			CMPI_RC_ERR_NOT_SUPPORTED, "CIM_ERR_NOT_SUPPORTED" ); 

  _OSBASE_TRACE(1,("--- %s CMPI DeleteInstance() exited",_ClassName));
  return rc;
}

CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderExecQuery( CMPIInstanceMI * mi, 
           const CMPIContext * ctx, 
           const CMPIResult * rslt, 
           const CMPIObjectPath * ref, 
           const char * lang, 
           const char * query) {
  CMPIStatus rc = {CMPI_RC_OK, NULL};

  _OSBASE_TRACE(1,("--- %s CMPI ExecQuery() called",_ClassName));

  CMSetStatusWithChars( _broker, &rc, 
			CMPI_RC_ERR_NOT_SUPPORTED, "CIM_ERR_NOT_SUPPORTED" ); 

  _OSBASE_TRACE(1,("--- %s CMPI ExecQuery() exited",_ClassName));
  return rc;
}


/* ---------------------------------------------------------------------------*/
/*                    Associator Provider Interface                           */
/* ---------------------------------------------------------------------------*/


CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderAssociationCleanup( CMPIAssociationMI * mi,
           const CMPIContext * ctx, CMPIBoolean terminate) {
  _OSBASE_TRACE(1,("--- %s CMPI AssociationCleanup() called",_ClassName));
  _OSBASE_TRACE(1,("--- %s CMPI AssociationCleanup() exited",_ClassName));
  CMReturn(CMPI_RC_OK);
}

/* 
 * The intention of associations is to show the relations between different
 * classes and their instances. Therefore an association has two properties. 
 * Each one representing a reference to a certain instance of the specified
 * class. We can say, that an association has a left and the right "end". 
 * 
 * Linux_NetworkPortImplementsIPEndpoint : 
 *    < role >   -> < class >
 *    Antecedent -> CIM_NetworkPort
 *    Dependent  -> Linux_IPProtocolEndpoint
 *
 */

/*
 * general API information
 *
 * cop :
 *    Specifies the CMPIObjectPath to the CMPIInstance of the known end of 
 *    the association. Its absolutelly necessary to define this anchor point,
 *    from where the evaluation of the association starts.
 * assocPath : 
 *    If not NULL, it contains the name of the association the caller is 
 *    looking for. The provider should only return values, when the assocPath 
 *    contains the name(s) of the association(s) he is responsible for !
 * role :
 *    The caller can specify that the source instance ( cop ) has to play 
 *    a certain <role> in the association. The <role> is specified by the
 *    association definition (see above). That means, role has to contain
 *    the same value as the <role> the source instance plays in this assoc.
 *    If this requirement is not true, the provider returns nothing.
 */

/*
 * specification of associators() and associatorNames()
 *
 * These methods return CMPIInstance ( in the case of associators() ) or 
 * CMPIObjectPath ( in the case of associatorNames() ) object(s) of the 
 * opposite end of the association.
 *
 * resultRole :
 *    The caller can specify that the target instance(s) has/have to play 
 *    a certain <role> in the association. The <role> is specified by the
 *    association definition (see above). That means, resultRole has to 
 *    contain the same value as the <role> the target instance(s) plays
 *    in this assoc. If this requirement is not true, the provider returns 
 *    nothing.
 * resultClass :
 *    The caller can specify that the target instance(s) has/have to be 
 *    instances of a certain <class>. The <class> is specified by the
 *    association definition (see above). That means, resultClass has to 
 *    contain the same value as the <class> of the target instance(s).
 *    If this requirement is not true, the provider returns nothing.
 */

CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderAssociators( CMPIAssociationMI * mi,
           const CMPIContext * ctx,
           const CMPIResult * rslt,
           const CMPIObjectPath * cop,
           const char * assocClass,
           const char * resultClass,
           const char * role,
           const char * resultRole,
           const char ** propertyList ) {
  CMPIStatus       rc    = {CMPI_RC_OK, NULL};
  CMPIObjectPath * op    = NULL;
  CMPIObjectPath * rcop  = NULL;
  CMPIString     * name  = NULL;
  char           * ptr   = NULL;
  int              refrc = 0;

  _OSBASE_TRACE(1,("--- %s CMPI Associators() called",_ClassName));
    
  if( assocClass ) {
    op = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(cop,&rc)),
			  _ClassName, &rc );
    if( op==NULL ) {
      CMSetStatusWithChars( _broker, &rc,
			    CMPI_RC_ERR_FAILED, "Create CMPIObjectPath failed." );
      _OSBASE_TRACE(2,("--- %s CMPI Associators() failed : %s",CMGetCharPtr(rc.msg)));
      return rc;
    }
  }

  if( ( assocClass==NULL ) || ( CMClassPathIsA(_broker,op,assocClass,&rc) == 1 ) ) {
  
    if( _assoc_check_parameter_const( _broker,cop,_RefLeft,_RefRight,
				      _RefLeftClass,_RefRightClass,
				      resultClass,role,resultRole, 
				      &rc ) == 0 ) { goto exit; }

    if( resultClass ) {
      rcop = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(cop,&rc)),
			      resultClass, &rc );
      if(  CMClassPathIsA(_broker,rcop,_RefLeftClass,&rc) == 1  ) {

	name = CMGetKey( cop, "Name", &rc).value.string;
	if( name == NULL ) { goto exit; }
	ptr = CMGetCharPtr(name);

	if( strcasecmp(resultClass,_RefLeftClassEth) == 0 &&
	    strstr(ptr,"eth") != NULL ) {
	  _RefLeftClass = _RefLeftClassEth;
	}
	else if( strcasecmp(resultClass,_RefLeftClassTr) == 0 &&
		 strstr(ptr,"tr") != NULL ) {
	  _RefLeftClass = _RefLeftClassTr;
	}
	else if( strcasecmp(resultClass,_RefLeftClassLo) == 0 &&
		 strstr(ptr,"lo") != NULL ) {
	  _RefLeftClass = _RefLeftClassLo;
	}
	else { goto exit; }

      }
    }

    refrc = _assoc_NetworkPortImplementsIPEndpoint( _broker, ctx, rslt, 
						    cop, 1, 1, &rc);
    _RefLeftClass = _RefLeftClass_bk;

    if( refrc != 0 ) { 
      if( rc.msg != NULL )  {
	_OSBASE_TRACE(1,("--- %s CMPI Associators() failed : %s",_ClassName,CMGetCharPtr(rc.msg)));
      }
      else {
	_OSBASE_TRACE(1,("--- %s CMPI Associators() failed",_ClassName));
      }
      return rc; 
    }
  }
  
 exit:
  CMReturnDone( rslt );
  _OSBASE_TRACE(1,("--- %s CMPI Associators() exited",_ClassName));
  CMReturn(CMPI_RC_OK);
}

CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderAssociatorNames( CMPIAssociationMI * mi,
           const CMPIContext * ctx,
           const CMPIResult * rslt,
           const CMPIObjectPath * cop,
           const char * assocClass,
           const char * resultClass,
           const char * role,
           const char * resultRole) {
  CMPIStatus       rc    = {CMPI_RC_OK, NULL};
  CMPIObjectPath * op    = NULL;
  CMPIObjectPath * rcop  = NULL;
  CMPIString     * name  = NULL;
  char           * ptr   = NULL;
  int              refrc = 0;

  _OSBASE_TRACE(1,("--- %s CMPI AssociatorNames() called",_ClassName));
    
  if( assocClass ) {
    op = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(cop,&rc)),
			  _ClassName, &rc );
    if( op==NULL ) {
      CMSetStatusWithChars( _broker, &rc,
			    CMPI_RC_ERR_FAILED, "Create CMPIObjectPath failed." );
      _OSBASE_TRACE(2,("--- %s CMPI AssociatorNames() failed : %s",CMGetCharPtr(rc.msg)));
      return rc;
    }
  }

  if( ( assocClass==NULL ) || ( CMClassPathIsA(_broker,op,assocClass,&rc) == 1 ) ) {
  
    if( _assoc_check_parameter_const( _broker,cop,_RefLeft,_RefRight,
				      _RefLeftClass,_RefRightClass,
				      resultClass,role,resultRole, 
				      &rc ) == 0 ) { goto exit; }

    if( resultClass ) {
      rcop = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(cop,&rc)),
			      resultClass, &rc );

      if(  CMClassPathIsA(_broker,rcop,_RefLeftClass,&rc) == 1  ) {

	name = CMGetKey( cop, "Name", &rc).value.string;
	if( name == NULL ) { goto exit; }
	ptr = CMGetCharPtr(name);

	if( strcasecmp(resultClass,_RefLeftClassEth) == 0 &&
	    strstr(ptr,"eth") != NULL ) {
	  _RefLeftClass = _RefLeftClassEth;
	}
	else if( strcasecmp(resultClass,_RefLeftClassTr) == 0 &&
		 strstr(ptr,"tr") != NULL ) {
	  _RefLeftClass = _RefLeftClassTr;
	}
	else if( strcasecmp(resultClass,_RefLeftClassLo) == 0 &&
		 strstr(ptr,"lo") != NULL ) {
	  _RefLeftClass = _RefLeftClassLo;
	}
	else { goto exit; }

      }
    }
    refrc = _assoc_NetworkPortImplementsIPEndpoint( _broker, ctx, rslt, 
						    cop, 0, 1, &rc);
    _RefLeftClass = _RefLeftClass_bk;
    
    if( refrc != 0 ) { 
      if( rc.msg != NULL ) {
	_OSBASE_TRACE(1,("--- %s CMPI AssociatorNames() failed : %s",_ClassName,CMGetCharPtr(rc.msg)));
      }
      else {
	_OSBASE_TRACE(1,("--- %s CMPI AssociatorNames() failed",_ClassName));
      }
      return rc; 
    }

  }

 exit:
  CMReturnDone( rslt );
  _OSBASE_TRACE(1,("--- %s CMPI AssociatorNames() exited",_ClassName));
  CMReturn(CMPI_RC_OK);
}


/*
 * specification of references() and referenceNames()
 *
 * These methods return CMPIInstance ( in the case of references() ) or 
 * CMPIObjectPath ( in the case of referenceNames() ) object(s) of th 
 * association itself.
 */

CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderReferences( CMPIAssociationMI * mi,
           const CMPIContext * ctx,
           const CMPIResult * rslt,
           const CMPIObjectPath * cop,
           const char * assocClass,
           const char * role,
           const char ** propertyList ) {
  CMPIStatus       rc    = {CMPI_RC_OK, NULL};
  CMPIObjectPath * op    = NULL;
  int              refrc = 0;

  _OSBASE_TRACE(1,("--- %s CMPI References() called",_ClassName));
    
  if( assocClass ) {
    op = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(cop,&rc)),
			  _ClassName, &rc );
    if( op==NULL ) {
      CMSetStatusWithChars( _broker, &rc,
			    CMPI_RC_ERR_FAILED, "Create CMPIObjectPath failed." );
      _OSBASE_TRACE(2,("--- %s CMPI References() failed : %s",CMGetCharPtr(rc.msg)));
      return rc;
    }
  }

  if( ( assocClass==NULL ) || ( CMClassPathIsA(_broker,op,assocClass,&rc) == 1 ) ) {
  
    if( _assoc_check_parameter_const( _broker,cop,_RefLeft,_RefRight,
				      _RefLeftClass,_RefRightClass,
				      NULL,role,NULL, 
				      &rc ) == 0 ) { goto exit; }

    refrc = _assoc_NetworkPortImplementsIPEndpoint( _broker, ctx, rslt,
						    cop, 1, 0, &rc);
    
    if( refrc != 0 ) { 
      if( rc.msg != NULL ) {
	_OSBASE_TRACE(1,("--- %s CMPI References() failed : %s",_ClassName,CMGetCharPtr(rc.msg)));
      }
      else {
	_OSBASE_TRACE(1,("--- %s CMPI References() failed",_ClassName));
      }
      return rc; 
    }
  }

 exit:
  CMReturnDone( rslt );
  _OSBASE_TRACE(1,("--- %s CMPI References() exited",_ClassName));
  CMReturn(CMPI_RC_OK);
}

CMPIStatus OSBase_NetworkPortImplementsIPEndpointProviderReferenceNames( CMPIAssociationMI * mi,
           const CMPIContext * ctx,
           const CMPIResult * rslt,
           const CMPIObjectPath * cop,
           const char * assocClass,
           const char * role) {
  CMPIStatus       rc    = {CMPI_RC_OK, NULL};
  CMPIObjectPath * op    = NULL;
  int              refrc = 0;

  _OSBASE_TRACE(1,("--- %s CMPI ReferenceNames() called",_ClassName));
    
  if( assocClass ) {
    op = CMNewObjectPath( _broker, CMGetCharPtr(CMGetNameSpace(cop,&rc)),
			  _ClassName, &rc );
    if( op==NULL ) {
      CMSetStatusWithChars( _broker, &rc,
			    CMPI_RC_ERR_FAILED, "Create CMPIObjectPath failed." );
      _OSBASE_TRACE(2,("--- %s CMPI ReferenceNames() failed : %s",CMGetCharPtr(rc.msg)));
      return rc;
    }
  }

  if( ( assocClass==NULL ) || ( CMClassPathIsA(_broker,op,assocClass,&rc) == 1 ) ) {
  
    if( _assoc_check_parameter_const( _broker,cop,_RefLeft,_RefRight,
				      _RefLeftClass,_RefRightClass,
				      NULL,role,NULL, 
				      &rc ) == 0 ) { goto exit; }
    
    refrc = _assoc_NetworkPortImplementsIPEndpoint( _broker, ctx, rslt, 
						    cop, 0, 0, &rc);

    if( refrc != 0 ) {
      if( rc.msg != NULL ) {
	_OSBASE_TRACE(1,("--- %s CMPI ReferenceNames() failed : %s",_ClassName,CMGetCharPtr(rc.msg)));
      }
      else {
	_OSBASE_TRACE(1,("--- %s CMPI ReferenceNames() failed",_ClassName));
      }
      return rc;
    }
  }

 exit:
  CMReturnDone( rslt );
  _OSBASE_TRACE(1,("--- %s CMPI ReferenceNames() exited",_ClassName));
  CMReturn(CMPI_RC_OK);
}


/* ---------------------------------------------------------------------------*/
/*                              Provider Factory                              */
/* ---------------------------------------------------------------------------*/

CMInstanceMIStub( OSBase_NetworkPortImplementsIPEndpointProvider, 
                  OSBase_NetworkPortImplementsIPEndpointProvider, 
                  _broker, 
                  CMNoHook);

CMAssociationMIStub( OSBase_NetworkPortImplementsIPEndpointProvider, 
                     OSBase_NetworkPortImplementsIPEndpointProvider, 
                     _broker, 
                     CMNoHook);


/* ---------------------------------------------------------------------------*/
/*          end of cmpiOSBase_NetworkPortImplementsIPEndpointProvider         */
/* ---------------------------------------------------------------------------*/

