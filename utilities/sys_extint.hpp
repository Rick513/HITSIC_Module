/**
 * Copyright 2018 - 2019 HITSIC
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * @file 	:	sys_pitmgr.hpp
 * @author  :	Chekhov Mark/马奇科(qq:905497173)
 * @version :	v1.0.0
 *
 * @date 	:	v0.1-beta.0 2019.10.20
 * @date 	:	v0.1.1		2019.11.05
 * @date	:	v1.0.0		2020.07.25
 *
 * @brief    :   外部中断管理器
 */

#pragma once
#ifndef UTILITIES_SYS_EXTINT_HPP_
#define UTILITIES_SYS_EXTINT_HPP_
#include "inc_stdlib.h"
#include "hitsic_common.h"

#if defined(HITSIC_USE_EXTINT) && (HITSIC_USE_EXTINT > 0)
#include "sys_extint_port.hpp"


//CPU Selection
#if defined(D_RT1052_SYS_EXTINT_PORT_HPP_) || defined (D_MK66F18_SYS_EXTINT_PORT_HPP_) || defined (D_KV10Z7_SYS_EXTINT_PORT_HPP_)

class extInt_t
{
public:
	typedef void (*handler_t)(void);

	static std::map<INTC_Type*, std::map<uint32_t, extInt_t>> isrSet;

	static status_t init(void);
	static extInt_t* insert(INTC_Type* _gpio, uint32_t _pin, handler_t _handler);
	static status_t remove(INTC_Type* _gpio, uint32_t _pin);
	static status_t remove(extInt_t* _inst);
	static void isr(INTC_Type* _gpio);

	INTC_Type* gpio;
	uint32_t pin;
	handler_t handler;

	void setup(INTC_Type* _gpio, uint32_t _pin, handler_t _handler);

	void setMode(interrupt_mode_t _mode)
	{
		//mode = _mode;
		EXTINT_SetInterruptConfig(gpio, pin, _mode);
	}
	extInt_t(void){}
private:
	extInt_t(INTC_Type* _gpio, uint32_t _pin, handler_t _handler)
	{
		setup(_gpio, _pin, _handler);
	}
};


#define EXTINT_Init()	extInt_t::init()
#define EXTINT_PortSetup(_gpio, _pin, _prio, _handler)	extInt_t::insert(_gpio, _pin, _handler)
#define EXTINT_PortRemove(_gpio, _pin) 		extInt_t::remove(_gpio, _pin)
#define PORTX_IRQHandler(_gpio, _list)		extInt_t::isr(_gpio)


#else	//CPU Selection

#error "C++ API does NOT support this CPU!"

#endif // CPU Selection

#endif // ! HITSIC_USE_EXTINT

#endif // ! UTILITIES_SYS_EXTINT_HPP_


