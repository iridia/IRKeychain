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





static inline NSString* NSStringFromIRKeychainItemKind (IRKeychainItemKind kind) {

	switch (kind) {

		case IRKeychainItemKindAny:
			return @"IRKeychainItemKindAny";

		case IRKeychainItemKindPassword:
			return @"IRKeychainItemKindPassword";

		case IRKeychainItemKindInternetPassword: 
			return @"IRKeychainItemKindInternetPassword";

		case IRKeychainItemKindCertificate: 
			return @"IRKeychainItemKindCertificate";

		case IRKeychainItemKindKey: 
			return @"IRKeychainItemKindKey";

		case IRKeychainItemKindIdentity: 
			return @"IRKeychainItemKindIdentity";

		default:
			assert(NO);
			
	}
	
}





static inline CFTypeRef SecClassFromIRKeychainItemKind(IRKeychainItemKind kind) {

	switch (kind) {
			
		case IRKeychainItemKindAny:
			return NULL;
			
		case IRKeychainItemKindPassword:
			return kSecClassGenericPassword;
			
		case IRKeychainItemKindInternetPassword: 
			return kSecClassInternetPassword;
			
		case IRKeychainItemKindCertificate: 
			return kSecClassCertificate;
			
		case IRKeychainItemKindKey: 
			return kSecClassKey;
			
		case IRKeychainItemKindIdentity: 
			return kSecClassIdentity;
			
		default:
			assert(NO);
			
	}	
	
}





static inline NSString* irNSStringFromOSStatus(OSStatus status) {

	switch (status) {

		case errSecSuccess:			
			return @"Succes";
		
		case errSecUnimplemented:
			return @"Unimplemented";
			
		case errSecParam:
			return @"Keychain query parameters invalid";

		case errSecAllocate:
			return @"Can’t allocate memory";
			
		case errSecNotAvailable:
			return @"No keychain available";
			
		case errSecDuplicateItem:
			return @"duplicate item exists";

		case errSecItemNotFound:
			return @"Item not found";
			
		case errSecInteractionNotAllowed:
			return @"User interaction is not allowed";
			
		case errSecDecode:
			return @"Unable to decode the provided data";
			
		case errSecAuthFailed:
			return @"The user name or passphrase you entered is not correct";
			
		default:
			return @"Unknown status";

	}

}

#endif




