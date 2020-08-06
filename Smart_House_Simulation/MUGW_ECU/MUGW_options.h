/*
 * MUGW_options.h
 *
 * Created: 01-Aug-20 9:22:39 PM
 *  Author: Mohamed Elattar
 */ 


#ifndef MUGW_OPTIONS_H_
#define MUGW_OPTIONS_H_


#include "std_types.h"
#include "bitwise.h"
#include "DIO.h"


void mugwoptions_void_selftest();
void mugwoptions_void_securityaccess(uint8 wrongpass);
void mugwoptions_void_homepage();
void mugwoptions_void_changepasskey(uint8 newpass[]);
void mugwoptions_void_tempcontrol(uint8 tempcontrol[]);
void mugwoptions_void_viewcal();
void mugwoptions_void_setcal(uint8 setcal[]);
void mugwoptions_void_doors(uint8 doorcontrol[]);
void mugwoptions_void_RGB(uint8 rgbcontrol[]);





#endif /* MUGW_OPTIONS_H_ */