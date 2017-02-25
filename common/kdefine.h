//kdefine.h for my self
//#pragma once --> compile this head-file once only
#ifndef __KDEFINE_H__    //define __KDEFINE_H__ BEGIN
  #define __KDEFINE_H__
  #include <linux/kernel.h>
  
  #ifndef STR
    #define STR(X) #X
  #endif
  
  #ifndef STRING
    #define STRING(X) STR(X)
  #endif

  #ifndef PRK_DEBUG 
    #define PRK_DEBUG 23
  #endif
  
  #if (PRK_DEBUG == 1)      //if define PRK_DEBUG == 1
    #define PRK_FORMAT(fmt) fmt "\n"
    #define prk_info(fmt,args...) pr_info(PRK_FORMAT(fmt),##args)
    #define prk_err(fmt,args...) pr_err(PRK_FORMAT(fmt),##args)
    #define prk_debug(fmt,args...) pr_debug(PRK_FORMAT(fmt),##args)
    #define prk_warn(fmt,args...) pr_warn(PRK_FORMAT(fmt),##args)
    #define prk_emerg(fmt,args...) pr_emerg(PRK_FORMAT(fmt),##args)
    #define prk_alert(fmt,args...) pr_alert(PRK_FORMAT(fmt),##args)
    #define prk_crit(fmt,args...) pr_crit(PRK_FORMAT(fmt),##args)
    #define prk_cont(fmt,args...) pr_cont(PRK_FORMAT(fmt),##args)
    #define prk_notice(fmt,args...) pr_notice(PRK_FORMAT(fmt),##args)
    #pragma message("select macro PRK_DEBUG=1 for printk when we debug our driver.")
  #elif (PRK_DEBUG == 2)    //if define PRK_DEBUG == 2
    #define AUTHOR "by T.san"
    #define PREFIX "--->"
    //#define PRK_FORMAT(fmt) PREFIX fmt ";" AUTHOR " in %s();file:%s,line:%d\n"
    #define PRK_FORMAT(fmt) PREFIX fmt ";" AUTHOR " in %s();file:" __FILE__ ",line:" STRING(__LINE__) "\n"
    #define prk_info(fmt,args...) pr_info(PRK_FORMAT(fmt),##args,__PRETTY_FUNCTION__)
    #define prk_err(fmt,args...) pr_err(PRK_FORMAT(fmt),##args,__PRETTY_FUNCTION__)
    #define prk_debug(fmt,args...) pr_debug(PRK_FORMAT(fmt),##args,__PRETTY_FUNCTION__)
    #define prk_warn(fmt,args...) pr_warn(PRK_FORMAT(fmt),##args,__PRETTY_FUNCTION__)
    #define prk_emerg(fmt,args...) pr_emerg(PRK_FORMAT(fmt),##args,__PRETTY_FUNCTION__)
    #define prk_alert(fmt,args...) pr_alert(PRK_FORMAT(fmt),##args,__PRETTY_FUNCTION__)
    #define prk_crit(fmt,args...) pr_crit(PRK_FORMAT(fmt),##args,__PRETTY_FUNCTION__)
    #define prk_cont(fmt,args...) pr_cont(PRK_FORMAT(fmt),##args,__PRETTY_FUNCTION__)
    #define prk_notice(fmt,args...) pr_notice(PRK_FORMAT(fmt),##args,__PRETTY_FUNCTION__)
    #pragma message("select macro PRK_DEBUG=2 for printk when we debug our driver.")
  #else                        //if define other level
    #define prk_info(fmt,args...)
    #define prk_err(fmt,args...)
    #define prk_debug(fmt,args...)
    #define prk_warn(fmt,args...)
    #define prk_emerg(fmt,args...)
    #define prk_alert(fmt,args...)
    #define prk_crit(fmt,args...)
    #define prk_cont(fmt,args...)
    #define prk_notice(fmt,args...)
    #pragma message("select macro PRK_DEBUG=" STRING(PRK_DEBUG) " for printk when we release our driver.")
    #ifdef PRK_DEBUG
      #undef PRK_DEBUG
    #endif
  #endif                       //define PRK_DEBUG=1/PRK_DEBUG=2/ ... end

  #ifndef CHECK_PTR
    #define CHECK_PTR(ptr,err_code,err_msg) if(!(ptr)) \
                                            { \
                                              prk_err("ERROR:%s;err_code[%d],ptr[0x%X]!!!",err_msg,err_code,(unsigned int)ptr); \
                                              return err_code; \
                                            }
  #endif
  
  #ifndef CHECK_RETURN
    #define CHECK_RETURN(ret_code,err_msg) if(0 > ret_code) \
                                           { \
                                             prk_err("ERROR:%s;err_code[%d]!!!",err_msg,err_code); \
                                             return ret_code; \
                                           }
  #endif
#endif                   //define __KDEFINE_H__ END
