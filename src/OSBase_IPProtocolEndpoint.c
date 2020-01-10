/*
 * OSBase_IPProtocolEndpoint.c
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
 * This shared library provides resource access functionality for the class
 * Linux_IPProtocolEndpoint. 
 * It is independent from any specific CIM technology.
*/

/* ---------------------------------------------------------------------------*/

#include "OSBase_Common.h"
#include "OSBase_CommonNetwork.h"
#include "OSBase_IPProtocolEndpoint.h"

#include <unistd.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>  
#include <dirent.h>
#include <sys/stat.h>    
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>

/* ---------------------------------------------------------------------------*/
// private declarations


/* ---------------------------------------------------------------------------*/


static int _ipProtocolEndpoint_data( char * id, 
				     struct cim_ipProtocolEndpoint ** sptr );


int enum_all_ipProtocolEndpoints( struct ipPEndpointList ** lptr ) {
  struct ipPEndpointList *  hlp   = NULL;
  char                   ** hdout = NULL;
  char                   *  name  = NULL;
  char                      port[64];
  int                       i     = 2;      /* start at third line */
  int                       rc    = 0;

  _OSBASE_TRACE(3,("--- enum_all_ipProtocolEndpoints() called"));

  rc = runcommand( "cat /proc/net/dev" , NULL , &hdout , NULL );
  
  if(hdout && hdout[0]) {
    while( hdout[i] != NULL) {

      if( hlp == NULL ) {
	hlp = calloc (1,sizeof(struct ipPEndpointList));
	*lptr = hlp;
      }

      if ( hlp->sptr != NULL) { 
	hlp->next = calloc (1,sizeof(struct ipPEndpointList));
	hlp = hlp->next;
      }
      
      memset(port,0,sizeof(port));
      sscanf(hdout[i]," %[^:]:",port);
      name = _get_ipProtocolEndpoint_name( port );

      rc = _ipProtocolEndpoint_data( name, &(hlp->sptr));
      if(name) free(name);
      
      i++;
    }
    freeresultbuf(hdout);
  }

  _OSBASE_TRACE(3,("--- enum_all_ipProtocolEndpoints() exited"));
  return rc;
}

int get_ipProtocolEndpoint_data( const char * id, 
				 struct cim_ipProtocolEndpoint ** sptr ) {
  struct ipPEndpointList        * lptr = NULL;
  struct ipPEndpointList        * lhlp = NULL;
  struct cim_ipProtocolEndpoint * ep   = NULL;
  int                             rc   = 0;

  _OSBASE_TRACE(3,("--- get_ipProtocolEndpoint_data() called"));

  rc = enum_all_ipProtocolEndpoints( &lptr ) ;
  
  if( rc == 0 && lptr != NULL ) {
    lhlp = lptr;
    for ( ; lptr ; lptr = lptr->next) {
      ep = lptr->sptr;
      if( strcmp( ep->name,id) == 0 ) {
	*sptr = ep;
	ep = NULL ;
	break;
      }
    }
    lptr = lhlp;
    for ( ; lptr ; ) {
      ep = lptr->sptr;
      if( ep != *sptr ) {
	free_ipProtocolEndpoint(ep);
      }
      lhlp = lptr;
      lptr = lptr->next;
      free(lhlp);
    }
    _OSBASE_TRACE(3,("--- get_ipProtocolEndpoint_data() exited"));
    return 0;
  }
  _OSBASE_TRACE(3,("--- get_ipProtocolEndpoint_data() failed"));
  return -1;
}


static int _ipProtocolEndpoint_data( char * id, 
				     struct cim_ipProtocolEndpoint ** sptr ) {
  char *  cmd   = NULL;
  char *  str   = NULL;
  char *  end   = NULL;
  char ** hdout = NULL;
  char ** hderr = NULL;
  int     rc    = 0;

  _OSBASE_TRACE(4,("--- _ipProtocolEndpoint_data() called"));

  *sptr = calloc (1,sizeof(struct cim_ipProtocolEndpoint));

  (*sptr)->name = strdup(id);

  (*sptr)->type    = 2;     /* IPv4 */
  (*sptr)->version = 1;     /* IPv4 only */

  /* EnabledStatus : Unknown = 0 ; Enabled = 2 ; Disabled = 3 */
  (*sptr)->enabled =  _get_port_status(id+5);

  /* IPv4Address */
  
  cmd = calloc(1,(strlen(id)+11));
  strcpy(cmd, "/sbin/ifconfig ");
  strcat(cmd, id+5);
  rc = runcommand( cmd, NULL , &hdout , &hderr );
  if(cmd) free(cmd);
  
  (*sptr)->address    = NULL;
  (*sptr)->subnetmask = NULL;

  if(hdout && hdout[1]) { 
    if( strstr( hdout[1], "inet addr:") != NULL ) {
      str = strchr( hdout[1], ':');
      str = str+1;
      end = strchr(str, ' ');
      (*sptr)->address = calloc(1, (strlen(str)-strlen(end)+1) );
      strncpy((*sptr)->address, str, strlen(str)-strlen(end) );
      
      str = strstr( end, "Mask:");
      str = strchr( str, ':');
      str = str+1;
      (*sptr)->subnetmask = calloc(1, (strlen(str)+1));
      strcpy((*sptr)->subnetmask, str);
      end = strchr((*sptr)->subnetmask, '\n');
      *end = '\0';
    }
  }

  freeresultbuf(hdout);
  freeresultbuf(hderr);
  _OSBASE_TRACE(4,("--- _ipProtocolEndpoint_data() exited"));
  return 0;
}


void free_ipPEndpointList( struct ipPEndpointList * lptr ) {
  struct ipPEndpointList * ls = NULL ;
  
  if( lptr == NULL ) return;
  for( ; lptr ; ) {
    if(lptr->sptr) { free_ipProtocolEndpoint(lptr->sptr); }
    ls = lptr;
    lptr = lptr->next;
    free(ls);
  }
}

void free_ipProtocolEndpoint( struct cim_ipProtocolEndpoint * sptr ) {
  if(sptr == NULL) return;
  if(sptr->name)       free(sptr->name);
  if(sptr->address)    free(sptr->address);
  if(sptr->subnetmask) free(sptr->subnetmask);
  free(sptr);
}


/* ---------------------------------------------------------------------------*/
/*                    end of OSBase_IPProtocolEndpoint.c                      */
/* ---------------------------------------------------------------------------*/

