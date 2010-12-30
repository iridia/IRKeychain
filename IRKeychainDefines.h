//
//  IRKeychainDefines.h
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreFoundation/CoreFoundation.h>
#import <Security/Security.h>





#ifndef __IRKeychain__
#define __IRKeychain__


typedef enum {
	
	IRKeychainItemKindAny,
	IRKeychainItemKindPassword,		//	kSecClassGenericPassword
	IRKeychainItemKindInternetPassword,	//	kSecClassInternetPassword
	IRKeychainItemKindCertificate,		//	kSecClassCertificate
	IRKeychainItemKindKey,			//	kSecClassKey
	IRKeychainItemKindIdentity		//	kSecClassIdentity

} IRKeychainItemKind;


typedef enum {
	
	IRKeychainItemAccessibleWhenUnlocked,
	IRKeychainItemAccessibleAfterFirstUnlock,
	IRKeychainItemAccessibleAlways,
	IRKeychainItemAccessibleWhenUnlockedThisDeviceOnly,
	IRKeychainItemAccessibleAfterFirstUnlockThisDeviceOnly,
	IRKeychainItemAccessibleAlwaysThisDeviceOnly
	
} IRKeychainItemAccessCondition;

//	Conveniences for debugging, internal use, etc.

extern NSString* NSStringFromIRKeychainItemKind (IRKeychainItemKind kind);
extern CFTypeRef SecClassFromIRKeychainItemKind(IRKeychainItemKind kind);

extern NSString* irNSStringFromOSStatus(OSStatus status);

#endif




