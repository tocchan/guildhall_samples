#pragma once
#if !defined( __JOB__ )
#define __JOB__

/************************************************************************/
/*                                                                      */
/* INCLUDE                                                              */
/*                                                                      */
/************************************************************************/
#include "common.h"

#include "ts_queue.h"
#include "signal.h"
#include "atomic.h"

/************************************************************************/
/*                                                                      */
/* DEFINES AND CONSTANTS                                                */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/* MACROS                                                               */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/* TYPES                                                                */
/*                                                                      */
/************************************************************************/
enum eJobType 
{
   JOB_GENERIC = 0,
   JOB_MAIN, 
   JOB_IO, 
   JOB_RENDER, 

   JOB_TYPE_COUNT,
};

/************************************************************************/
/*                                                                      */
/* STRUCTS                                                              */
/*                                                                      */
/************************************************************************/


/************************************************************************/
/*                                                                      */
/* CLASSES                                                              */
/*                                                                      */
/************************************************************************/
class Job;
void JobDispatchAndRelease( Job *job );


typedef void (*job_work_cb)( void* );

//--------------------------------------------------------------------
//--------------------------------------------------------------------
class Job
{
   public:
      eJobType type; 
      job_work_cb work_cb;

      void *user_data;

      std::vector<Job*> dependents;
      uint num_dependencies;

   public:
      void on_finish();
      void on_dependancy_finished(); 

      void dependent_on( Job *parent ); 
};

//--------------------------------------------------------------------
//--------------------------------------------------------------------
class JobConsumer
{
};

/************************************************************************/
/*                                                                      */
/* GLOBAL VARIABLES                                                     */
/*                                                                      */
/************************************************************************/

/************************************************************************/
/*                                                                      */
/* FUNCTION PROTOTYPES                                                  */
/*                                                                      */
/************************************************************************/
void JobSystemStartup( uint job_category_count, int generic_thread_count = -1 );
void JobSystemShutdown();

Job* JobCreate( eJobType type, job_work_cb work_cb, void *user_data );
void JobDispatchAndRelease( Job *job );

//------------------------------------------------------------------------
// THIS SHOULD BE MOVED TO A JOB CONSUMER OBJECT!
uint JobConsumeAll( eJobType type );

#endif 