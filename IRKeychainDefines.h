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





static inline Class IRKeychainItemClassFromKind (IRKeychainItemKind kind) {

//	This surely is not optimal

	switch (kind) {
	
		case IRKeychainItemKindInternetPassword:
			return NSClassFromString(@"IRKeychainInternetPasswordItem");
			
		case IRKeychainItemKindCertificate:
			return NSClassFromString(@"IRKeychainCertificateItem");
			
		case IRKeychainItemKindKey:
			return NSClassFromString(@"IRKeychainKeyItem");
		
		case IRKeychainItemKindIdentity:
			return NSClassFromString(@"IRKeychainIdentityItem");
		
		case IRKeychainItemKindAny:
		case IRKeychainItemKindPassword:
		default:
			return NSClassFromString(@"IRKeychainPasswordItem");
	
	}

}





static inline IRKeychainItemKind IRKeychainItemKindFromClass (Class class) {

	if (class == NSClassFromString(@"IRKeychainPasswordItem"))
		return IRKeychainItemKindPassword;
		
	if (class == NSClassFromString(@"IRKeychainInternetPasswordItem"))
		return IRKeychainItemKindInternetPassword;
		
	if (class == NSClassFromString(@"IRKeychainCertificateItem"))
		return IRKeychainItemKindCertificate;
		
	if (class == NSClassFromString(@"IRKeychainKeyItem"))
		return IRKeychainItemKindKey;
	
	if (class == NSClassFromString(@"IRKeychainIdentityItem"))
		return IRKeychainItemKindIdentity;
	
	assert(NO);
	
}





static inline CFTypeRef SecAuthenticationTypeFromIRKeychainAuthenticationType(IRKeychainAuthenticationType type) {

	switch (type) {
			
		case IRKeychainAuthenticationTypeNTLM:
			return kSecAttrAuthenticationTypeNTLM;

		case IRKeychainAuthenticationTypeMSN:
			return kSecAttrAuthenticationTypeMSN;

		case IRKeychainAuthenticationTypeDPA:
			return kSecAttrAuthenticationTypeDPA;

		case IRKeychainAuthenticationTypeRPA:
			return kSecAttrAuthenticationTypeRPA;

		case IRKeychainAuthenticationTypeHTTPBasic:
			return kSecAttrAuthenticationTypeHTTPBasic;

		case IRKeychainAuthenticationTypeHTTPDigest:
			return kSecAttrAuthenticationTypeHTTPDigest;

		case IRKeychainAuthenticationTypeHTMLForm:
			return kSecAttrAuthenticationTypeHTMLForm;

		case IRKeychainAuthenticationTypeDefault:
			return kSecAttrAuthenticationTypeDefault;

		default:
			assert(NO);
			
	}	
	
}





static inline CFTypeRef SecProtocolFromIRKeychainProtocol(IRKeychainProtocol protocol) {

	switch (protocol) {

		case IRKeychainProtocolFTP:
			return kSecAttrProtocolFTP;

		case IRKeychainProtocolFTPAccount:
			return kSecAttrProtocolFTPAccount;

		case IRKeychainProtocolHTTP:
			return kSecAttrProtocolHTTP;

		case IRKeychainProtocolIRC:
			return kSecAttrProtocolIRC;

		case IRKeychainProtocolNNTP:
			return kSecAttrProtocolNNTP;

		case IRKeychainProtocolPOP3:
			return kSecAttrProtocolPOP3;

		case IRKeychainProtocolSMTP:
			return kSecAttrProtocolSMTP;

		case IRKeychainProtocolSOCKS:
			return kSecAttrProtocolSOCKS;

		case IRKeychainProtocolIMAP:
			return kSecAttrProtocolIMAP;

		case IRKeychainProtocolLDAP:
			return kSecAttrProtocolLDAP;

		case IRKeychainProtocolAppleTalk:
			return kSecAttrProtocolAppleTalk;

		case IRKeychainProtocolAFP:
			return kSecAttrProtocolAFP;

		case IRKeychainProtocolTelnet:
			return kSecAttrProtocolTelnet;

		case IRKeychainProtocolSSH:
			return kSecAttrProtocolSSH;

		case IRKeychainProtocolFTPS:
			return kSecAttrProtocolFTPS;

		case IRKeychainProtocolHTTPS:
			return kSecAttrProtocolHTTPS;

		case IRKeychainProtocolHTTPProxy:
			return kSecAttrProtocolHTTPProxy;

		case IRKeychainProtocolHTTPSProxy:
			return kSecAttrProtocolHTTPSProxy;

		case IRKeychainProtocolFTPProxy:
			return kSecAttrProtocolFTPProxy;

		case IRKeychainProtocolSMB:
			return kSecAttrProtocolSMB;

		case IRKeychainProtocolRTSP:
			return kSecAttrProtocolRTSP;

		case IRKeychainProtocolRTSPProxy:
			return kSecAttrProtocolRTSPProxy;

		case IRKeychainProtocolDAAP:
			return kSecAttrProtocolDAAP;

		case IRKeychainProtocolEPPC:
			return kSecAttrProtocolEPPC;

		case IRKeychainProtocolIPP:
			return kSecAttrProtocolIPP;

		case IRKeychainProtocolNNTPS:
			return kSecAttrProtocolNNTPS;

		case IRKeychainProtocolLDAPS:
			return kSecAttrProtocolLDAPS;

		case IRKeychainProtocolTelnetS:
			return kSecAttrProtocolTelnetS;

		case IRKeychainProtocolIMAPS:
			return kSecAttrProtocolIMAPS;

		case IRKeychainProtocolIRCS:
			return kSecAttrProtocolIRCS;

		case IRKeychainProtocolPOP3S:
			return kSecAttrProtocolPOP3S;

		default:
			assert(NO);

	}

}





#endif




