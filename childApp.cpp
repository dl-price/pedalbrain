//
// childApp.cpp
// Library C++ code
// ----------------------------------
// Developed with embedXcode
// http://embedXcode.weebly.com
//
// Project 		pedalbrain
//
// Created by 	Daniel Price, 09/01/2017 16:39
// 				Daniel Price
//
// Copyright 	(c) Daniel Price, 2017
// Licence		<#licence#>
//
// See 			childApp.h and ReadMe.txt for references
//


// Library header
#include "Arduino.h"
#include "libraries/usb_midi/usb_api.h"
#include "childApp.h"

void childApp::setup()
{
    pinMode(13, OUTPUT);
}

void childApp::loop()
{
    digitalWrite(13, HIGH);
    usbMIDI.sendNoteOn(60,127,1);
    delay(1000);
    digitalWrite(13, LOW);
    usbMIDI.sendNoteOff(60,0,1);
    delay(1000);
}

// Code
