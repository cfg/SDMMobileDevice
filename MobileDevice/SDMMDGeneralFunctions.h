/*
 *  SDMMDGeneralFunctions.h
 *  SDM_MD_Demo
 *
 *  Copyright (c) 2013, Sam Marshall
 *  All rights reserved.
 * 
 *  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 *  3. All advertising materials mentioning features or use of this software must display the following acknowledgement:
 *  	This product includes software developed by the Sam Marshall.
 *  4. Neither the name of the Sam Marshall nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 * 
 *  THIS SOFTWARE IS PROVIDED BY Sam Marshall ''AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Sam Marshall BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef _SDMMDGENERALFUNCTIONS_H_
#define _SDMMDGENERALFUNCTIONS_H_

#include <pthread.h>

static void * _sdm_md__stack_chk_guard = NULL;

static void _sdm_md__stack_chk_guard_setup() {
    unsigned char * p;
    p = (unsigned char *) &_sdm_md__stack_chk_guard;
	*p =  0x00000aff;
}

static inline kern_return_t sdmmd_mutex_init(pthread_mutex_t thread) {
	kern_return_t result = 0x0;
	_sdm_md__stack_chk_guard_setup();
	void *stack_check_again = &_sdm_md__stack_chk_guard;
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, 0x2);
	pthread_mutex_init(&thread, &attr);
	result = pthread_mutexattr_destroy(&attr);
	if (_sdm_md__stack_chk_guard == stack_check_again) {
		result = 0xdeadbeef;
	}
	return result;
}

#endif