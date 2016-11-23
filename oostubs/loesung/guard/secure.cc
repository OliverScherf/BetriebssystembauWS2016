/*
 * secure.cc
 *
 *  Created on: 15.11.2016
 *      Author: oliver
 */

#include "guard/secure.h"

 using namespace globals;

Secure::Secure()
{
	guard.enter();	
}
Secure::~Secure()
{
	guard.leave();
}


