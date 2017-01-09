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
#include "childApp.h"

void childApp::setup()
{
    pinMode(13, OUTPUT);
}

void childApp::loop()
{
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}

// Code
