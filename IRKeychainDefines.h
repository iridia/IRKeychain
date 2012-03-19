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

#define IRIDIA_KEYCHAIN_DEFAULT_NSERROR_DOMAIN @"com.iridia.keychain"

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

typedef enum {
    
    IRKeychainAuthenticationTypeUnknown = 0,
    IRKeychainAuthenticationTypeNTLM,
    IRKeychainAuthenticationTypeMSN,
    IRKeychainAuthenticationTypeDPA,
    IRKeychainAuthenticationTypeRPA,
    IRKeychainAuthenticationTypeHTTPBasic,
    IRKeychainAuthenticationTypeHTTPDigest,
    IRKeychainAuthenticationTypeHTMLForm,
    IRKeychainAuthenticationTypeDefault,
    	
} IRKeychainAuthenticationType;

typedef enum {

	IRKeychainProtocolUnknown,
	IRKeychainProtocolFTP,
	IRKeychainProtocolFTPAccount,
	IRKeychainProtocolHTTP,
	IRKeychainProtocolIRC,
	IRKeychainProtocolNNTP,
	IRKeychainProtocolPOP3,
	IRKeychainProtocolSMTP,
	IRKeychainProtocolSOCKS,
	IRKeychainProtocolIMAP,
	IRKeychainProtocolLDAP,
	IRKeychainProtocolAppleTalk,
	IRKeychainProtocolAFP,
	IRKeychainProtocolTelnet,
	IRKeychainProtocolSSH,
	IRKeychainProtocolFTPS,
	IRKeychainProtocolHTTPS,
	IRKeychainProtocolHTTPProxy,
	IRKeychainProtocolHTTPSProxy,
	IRKeychainProtocolFTPProxy,
	IRKeychainProtocolSMB,
	IRKeychainProtocolRTSP,
	IRKeychainProtocolRTSPProxy,
	IRKeychainProtocolDAAP,
	IRKeychainProtocolEPPC,
	IRKeychainProtocolIPP,
	IRKeychainProtocolNNTPS,
	IRKeychainProtocolLDAPS,
	IRKeychainProtocolTelnetS,
	IRKeychainProtocolIMAPS,
	IRKeychainProtocolIRCS,
	IRKeychainProtocolPOP3S

} IRKeychainProtocol;

extern NSString * NSStringFromIRKeychainItemKind (IRKeychainItemKind kind);
extern CFTypeRef SecClassFromIRKeychainItemKind (IRKeychainItemKind kind);

extern IRKeychainItemKind IRKeychainItemKindFromSecClass (CFTypeRef class);
extern NSString * irNSStringFromOSStatus (OSStatus status);

extern Class IRKeychainItemClassFromKind (IRKeychainItemKind kind);
extern IRKeychainItemKind IRKeychainItemKindFromClass (Class class);

extern CFTypeRef SecAuthenticationTypeFromIRKeychainAuthenticationType(IRKeychainAuthenticationType type);
extern IRKeychainAuthenticationType IRKeychainAuthenticationTypeFromSecAuthenticationType (CFTypeRef type);

extern CFTypeRef SecProtocolFromIRKeychainProtocol(IRKeychainProtocol protocol);
extern IRKeychainProtocol IRKeychainProtocolFromSecProtocol (CFTypeRef protocol);

extern id IRKeychainObjectOrPlaceholder (id object, id placeholder);
extern id IRKeychainObjectOrNull (id object);
extern id IRKeychainObjectOrEmptyString (id object);
extern id IRKeychainObjectOrEmptyStringData (id object);
