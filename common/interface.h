#pragma once

#ifndef __INTERFACE_H__
#define __INTERFACE_H__

struct ICallBack
{
  int (*func1)(void);
  int (*func2)(void);
};

#endif
