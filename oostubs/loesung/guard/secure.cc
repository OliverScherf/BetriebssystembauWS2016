/*
 * secure.cc
 *
 *  Created on: 15.11.2016
 *      Author: oliver
 */

#include "guard/secure.h"

Secure::Secure()
{
	guard.enter();
}
Secure::~Secure()
{
	guard.leave();
}
