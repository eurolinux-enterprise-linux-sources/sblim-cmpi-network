/*
 * OSBase_CommonNetwork.c
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
 * Linux_CommonNetwork. 
 * It is independent from any specific CIM technology.
*/

/* ---------------------------------------------------------------------------*/

#include "OSBase_Common.h"
#include "OSBase_CommonNetwork.h"

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


unsigned short _get_port_status( const char * id ) {
  char        *  cmd   = NULL;
  char        ** hdout = NULL;
  char        ** hderr = NULL;
  int            rc    = 0;
  unsigned short stat  = 0;

  _OSBASE_TRACE(4,("--- get_port_status() called"));

  /* EnabledStatus : Unknown = 0 ; Enabled = 2 ; Disabled = 3 */
  cmd = calloc(1,(strlen(id)+23));
  strcpy(cmd, "/sbin/ifconfig | grep ");
  strcat(cmd, id);
  rc = runcommand( cmd, NULL , &hdout , &hderr );
  if(cmd) free(cmd);
  if( rc != 0 ) { stat = 3; }  
  if ( rc == 0 && hdout[0] != NULL ) { stat = 2; }
  freeresultbuf(hdout);
  freeresultbuf(hderr);

  _OSBASE_TRACE(4,("--- get_port_status() exited : %i",stat));
  return stat;
}


/* ---------------------------------------------------------------------------*/

char * _get_ipProtocolEndpoint_name( const char * id ) {
  char * name = NULL;

  _OSBASE_TRACE(4,("--- get_ipProtocolEndpoint_name() called"));

  name = calloc(1,(strlen(id)+6));
  strcpy(name, "IPv4_");
  strcat(name, id);

  _OSBASE_TRACE(4,("--- get_ipProtocolEndpoint_name() exited : %s",name));
  return name;
}


/* ---------------------------------------------------------------------------*/

/* 
 * type = 1 ... Linux_EthernetPort
 * type = 1 ... Linux_TokenRingPort
 * type = 3 ... Linux_LocalLoopbackPort
 */

static int _netPort_data( char * id, 
			  unsigned short type, 
			  struct cim_netPort ** sptr );


int enum_all_netPorts( struct netPortList ** lptr ) {
  struct netPortList *  hlp   = NULL;
  char               ** hdout = NULL;
  char               ** hdchk = NULL;
  char               ** hderr = NULL;
  char               *  cmd   = NULL;
  char                  port[64];
  unsigned short        type  = 0;
  int                   i     = 2;      /* start at third line */
  int                   rc    = 0;

  _OSBASE_TRACE(3,("--- enum_all_netPorts() called"));

  rc = runcommand( "cat /proc/net/dev" , NULL , &hdout , &hderr );

  if( rc == 0 ) {
    while( hdout[i] != NULL) {	
      
      memset(port,0,sizeof(port));
      sscanf(hdout[i]," %[^:]:",port);

      cmd = calloc(1,100);
      strcpy(cmd, "/sbin/ifconfig ");
      strcat(cmd, port);
      
      rc = runcommand( cmd, NULL , &hdchk , &hderr );
      if(cmd) { free(cmd); cmd = NULL; }
      
      if(hdchk && hdchk[0]) {
	if( strstr(hdchk[0], "Ethernet") != NULL ) { type = 1; }
	if( strstr(hdchk[0], "Token Ring") != NULL ) { type = 2; }
	if( strstr(hdchk[0], "Local Loopback") != NULL ) { type = 3; }
      }
      else {
	if( strstr(port,"eth") != NULL ) { type = 1; }
	if( strstr(port,"tr")  != NULL ) { type = 2; }
	if( strstr(port,"lo")  != NULL ) { type = 3; }
      }
      freeresultbuf(hdchk);
      freeresultbuf(hderr);
      
      if( type != 0 ) {
	
	if( hlp == NULL ) {
	  hlp = calloc (1,sizeof(struct netPortList));
	  *lptr = hlp;
	}
	if ( hlp->sptr != NULL) { 
	  hlp->next = calloc (1,sizeof(struct netPortList));
	  hlp = hlp->next;
	}

	rc = _netPort_data( port, type, &(hlp->sptr));
      }
      type = 0;
      i++;
      rc = 0;
    }
  }
  else { freeresultbuf(hderr); }

  freeresultbuf(hdout);
  _OSBASE_TRACE(3,("--- enum_all_netPorts() exited"));
  return rc;
}

/* 
 * type = 1 ... Linux_EthernetPort
 * type = 1 ... Linux_TokenRingPort
 * type = 3 ... Linux_LocalLoopbackPort
 */

int get_netPort_data( const char * id, 
		      unsigned short type, 
		      struct cim_netPort ** sptr ) {
  struct netPortList * lptr = NULL;
  struct netPortList * lhlp = NULL;
  struct cim_netPort * port = NULL;
  int                  rc   = 0;

  _OSBASE_TRACE(3,("--- get_netPort_data() called"));

  rc = enum_all_netPorts( &lptr ) ;
  
  if( rc == 0 && lptr != NULL ) {
    lhlp = lptr;
    for ( ; lptr ; lptr = lptr->next) {
      port = lptr->sptr;
      if( strcmp( port->name,id) == 0 ) {
	*sptr = port;
	port = NULL ;
	break;
      }
    }
    lptr = lhlp;
    for ( ; lptr ; ) {
      port = lptr->sptr;
      if( port != *sptr ) {
	free_netPort(port);
      }
      lhlp = lptr;
      lptr = lptr->next;
      free(lhlp);
    }
    _OSBASE_TRACE(3,("--- get_netPort_data() exited"));
    return 0;
  }
  _OSBASE_TRACE(3,("--- get_netPort_data() failed"));
  return -1;
}


static int _netPort_data( char * id, 
			  unsigned short type, 
			  struct cim_netPort ** sptr ) {
  char ** hdout = NULL;
  char ** hderr = NULL;
  char *  cmd   = NULL;
  char *  ptr   = NULL;
  char *  end   = NULL;
  int     rc    = 0;

  _OSBASE_TRACE(4,("--- _netPort_data() called"));

  (*sptr) = calloc (1,sizeof(struct cim_netPort));

  (*sptr)->name = strdup(id);
  (*sptr)->type = type;

  if( type == 1 ) { (*sptr)->linkTec = 2; /* Ethernet  */}
  if( type == 2 ) { (*sptr)->linkTec = 7; /* Token Ring  */}
  if( type == 3 ) { (*sptr)->linkTec = 1; /* Other : Local Loopback  */  }

  /* EnabledStatus : Unknown = 0 ; Enabled = 2 ; Disabled = 3 */
  (*sptr)->enabled =  _get_port_status(id);

  /* PermanentAddress */
  cmd = calloc(1,100);
  strcpy(cmd, "/sbin/ifconfig ");
  strcat(cmd, id);      
  rc = runcommand(cmd, NULL , &hdout , &hderr);
  memset(cmd,0,100);
  rc=0;
  if(hdout && hdout[0]) {
    if( (ptr=strstr(hdout[0],"HWaddr")) != NULL) {
      ptr=strchr(ptr,' ');
      end=strchr(ptr+1,' ');
      (*sptr)->mac_addr = calloc(1,strlen(ptr)-strlen(end));
      strncpy((*sptr)->mac_addr,ptr+1,strlen(ptr)-strlen(end)-1);
    }
  }
  freeresultbuf(hdout);
  freeresultbuf(hderr);

  /* Speed and MaxSpeed ... depends on used Link Technology */

  /* Ethernet  */
  if( (*sptr)->linkTec == 2 ) {
    strcpy(cmd, "/sbin/mii-tool -v ");
    strcat(cmd, id);
    rc = runcommand(cmd, NULL, &hdout, &hderr);
    memset(cmd,0,100);
    if(hdout && hdout[0]) {
      if( strstr(hdout[0], "100base") != NULL ) {
	(*sptr)->speed = 100*1024*1024; /* Bits per second */
      }
      else if( strstr(hdout[0], "10base") != NULL ) {
	(*sptr)->speed = 10*1024*1024;  /* Bits per second */
      }
      if( hdout[4] != NULL ) {
	if( strstr(hdout[0], "100base") != NULL ) {
	  (*sptr)->maxSpeed = 100*1024*1024; /* Bits per second */
  	}
	else if( strstr(hdout[0], "10base") != NULL ) {
	  (*sptr)->maxSpeed = 10*1024*1024;  /* Bits per second */
	}
      }
    }
    freeresultbuf(hdout);
    freeresultbuf(hderr);
    rc=0;
  }
  /* Token Ring  */
  else if( (*sptr)->linkTec == 7 ) {
    (*sptr)->maxSpeed = 16*1024*1024;
  }
  /* Other : Local Loopback  */ 
  /* else if( (*sptr)->linkTec == 1 ) { } */

  if(cmd) free(cmd);
  _OSBASE_TRACE(4,("--- _netPort_data() exited"));
  return rc;
}


void free_netPortList( struct netPortList * lptr ) {
  struct netPortList * ls = NULL ;
  
  if( lptr == NULL ) return;
  for( ; lptr ; ) {
    if(lptr->sptr) { free_netPort(lptr->sptr); }
    ls = lptr;
    lptr = lptr->next;
    free(ls);
  }

}

void free_netPort( struct cim_netPort * sptr ) {  
  if(sptr == NULL) return;
  if(sptr->name) free(sptr->name);
  if(sptr->mac_addr) free(sptr->mac_addr);
  free(sptr);
}


/* ---------------------------------------------------------------------------*/
/*                      end of OSBase_CommonNetwork.c                         */
/* ---------------------------------------------------------------------------*/

