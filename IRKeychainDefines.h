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





static inline IRKeychainItemKind IRKeychainItemKindFromSecClass (CFTypeRef class) {

//	Sigh…

	if ([(NSString *)class isEqual:(NSString *)kSecClassGenericPassword])
		return IRKeychainItemKindPassword;
			
	if ([(NSString *)class isEqual:(NSString *)kSecClassInternetPassword])
		return IRKeychainItemKindInternetPassword;
			
	if ([(NSString *)class isEqual:(NSString *)kSecClassCertificate])
		return IRKeychainItemKindCertificate;
			
	if ([(NSString *)class isEqual:(NSString *)kSecClassKey])
		return IRKeychainItemKindKey;
			
	if ([(NSString *)class isEqual:(NSString *)kSecClassIdentity])
		return IRKeychainItemKindIdentity;
			
	assert(NO);
	
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

		case IRKeychainAuthenticationTypeUnknown:
			return @"";

		default:
			assert(NO);
			
	}	
	
}





static inline IRKeychainAuthenticationType IRKeychainAuthenticationTypeFromSecAuthenticationType (CFTypeRef type) {

	if ([(NSString *)type isEqual:(NSString *)kSecAttrAuthenticationTypeNTLM])
		return IRKeychainAuthenticationTypeNTLM;

	if ([(NSString *)type isEqual:(NSString *)kSecAttrAuthenticationTypeMSN])
		return IRKeychainAuthenticationTypeMSN;

	if ([(NSString *)type isEqual:(NSString *)kSecAttrAuthenticationTypeDPA])
		return IRKeychainAuthenticationTypeDPA;

	if ([(NSString *)type isEqual:(NSString *)kSecAttrAuthenticationTypeRPA])
		return IRKeychainAuthenticationTypeRPA;

	if ([(NSString *)type isEqual:(NSString *)kSecAttrAuthenticationTypeHTTPBasic])
		return IRKeychainAuthenticationTypeHTTPBasic;

	if ([(NSString *)type isEqual:(NSString *)kSecAttrAuthenticationTypeHTTPDigest])
		return IRKeychainAuthenticationTypeHTTPDigest;

	if ([(NSString *)type isEqual:(NSString *)kSecAttrAuthenticationTypeHTMLForm])
		return IRKeychainAuthenticationTypeHTMLForm;

	if ([(NSString *)type isEqual:(NSString *)kSecAttrAuthenticationTypeDefault])
		return IRKeychainAuthenticationTypeDefault;
	
	return IRKeychainAuthenticationTypeUnknown;

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
			return [NSNumber numberWithInt:0];

	}

}





static inline IRKeychainProtocol IRKeychainProtocolFromSecProtocol (CFTypeRef protocol) {

	if ([(NSNumber *)protocol intValue] == 0)
		return IRKeychainProtocolUnknown;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolFTP intValue])
		return IRKeychainProtocolFTP;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolFTPAccount intValue])
		return IRKeychainProtocolFTPAccount;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolHTTP intValue])
		return IRKeychainProtocolHTTP;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolIRC intValue])
		return IRKeychainProtocolIRC;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolNNTP intValue])
		return IRKeychainProtocolNNTP;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolPOP3 intValue])
		return IRKeychainProtocolPOP3;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolSMTP intValue])
		return IRKeychainProtocolSMTP;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolSOCKS intValue])
		return IRKeychainProtocolSOCKS;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolIMAP intValue])
		return IRKeychainProtocolIMAP;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolLDAP intValue])
		return IRKeychainProtocolLDAP;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolAppleTalk intValue])
		return IRKeychainProtocolAppleTalk;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolAFP intValue])
		return IRKeychainProtocolAFP;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolTelnet intValue])
		return IRKeychainProtocolTelnet;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolSSH intValue])
		return IRKeychainProtocolSSH;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolFTPS intValue])
		return IRKeychainProtocolFTPS;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolHTTPS intValue])
		return IRKeychainProtocolHTTPS;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolHTTPProxy intValue])
		return IRKeychainProtocolHTTPProxy;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolHTTPSProxy intValue])
		return IRKeychainProtocolHTTPSProxy;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolFTPProxy intValue])
		return IRKeychainProtocolFTPProxy;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolSMB intValue])
		return IRKeychainProtocolSMB;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolRTSP intValue])
		return IRKeychainProtocolRTSP;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolRTSPProxy intValue])
		return IRKeychainProtocolRTSPProxy;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolDAAP intValue])
		return IRKeychainProtocolDAAP;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolEPPC intValue])
		return IRKeychainProtocolEPPC;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolIPP intValue])
		return IRKeychainProtocolIPP;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolNNTPS intValue])
		return IRKeychainProtocolNNTPS;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolLDAPS intValue])
		return IRKeychainProtocolLDAPS;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolTelnetS intValue])
		return IRKeychainProtocolTelnetS;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolIMAPS intValue])
		return IRKeychainProtocolIMAPS;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolIRCS intValue])
		return IRKeychainProtocolIRCS;

	if ([(NSNumber *)protocol intValue] == [(NSNumber *)kSecAttrProtocolPOP3S intValue])
		return IRKeychainProtocolPOP3S;

	assert(NO);

}





static inline id IRKeychainObjectOrPlaceholder (id object, id placeholder) {

	return object ? object : placeholder;
	
}

static inline id IRKeychainObjectOrNull (id object) {

	return IRKeychainObjectOrPlaceholder(object, [NSNull null]);
	
}

static inline id IRKeychainObjectOrEmptyString (id object) {

	return IRKeychainObjectOrPlaceholder(object, @"");
	
}

static inline id IRKeychainObjectOrEmptyStringData (id object) {

	return IRKeychainObjectOrPlaceholder(object, [@"" dataUsingEncoding:NSUTF8StringEncoding]);

}






#endif




