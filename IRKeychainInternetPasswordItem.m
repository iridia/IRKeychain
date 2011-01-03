//
//  IRKeychainInternetPasswordItem.m
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import "IRKeychainInternetPasswordItem.h"


@interface IRKeychainInternetPasswordItem ()

@property (nonatomic, readwrite, retain) NSDate *creationDate;
@property (nonatomic, readwrite, retain) NSDate *lastModificationDate;

@end

@implementation IRKeychainInternetPasswordItem

- (id) initWithContentsOfSecurityItemDictionary:(NSDictionary *)dictionary {

	self = [super initWithContentsOfSecurityItemDictionary:dictionary];
	if (!self) return nil;
	
	self.creationDate = (NSDate *)[dictionary objectForKey:(id)kSecAttrCreationDate];	
	self.lastModificationDate = (NSDate *)[dictionary objectForKey:(id)kSecAttrModificationDate];
	
	self.creatorCodeRepresentation = (NSNumber *)[dictionary objectForKey:(id)kSecAttrCreator];
	
	self.associatedAccountName = (NSString *)[dictionary objectForKey:(id)kSecAttrAccount];
	
	self.userDescription = (NSString *)[dictionary objectForKey:(id)kSecAttrDescription];
	self.userComment = (NSString *)[dictionary objectForKey:(id)kSecAttrComment];
	
	self.userLabel = (NSString *)[dictionary objectForKey:(id)kSecAttrLabel];
	
	self.serverSecurityDomain = (NSString *)[dictionary objectForKey:(id)kSecAttrSecurityDomain];
	self.serverAddress = (NSString *)[dictionary objectForKey:(id)kSecAttrServer];
	self.serverPort = (NSNumber *)[dictionary objectForKey:(id)kSecAttrPort];
	
	self.serverProtocol = IRKeychainProtocolFromSecProtocol([dictionary objectForKey:(id)kSecAttrProtocol]);
	self.serverAuthenticationType = IRKeychainAuthenticationTypeFromSecAuthenticationType([dictionary objectForKey:(id)kSecAttrAuthenticationType]);
	self.serverPath = (NSString *)[dictionary objectForKey:(id)kSecAttrPath];

	return self;

}

- (NSDictionary *) securityItemQueryDictionary {

	NSMutableDictionary *returnedDictionary = [[[super securityItemQueryDictionary] mutableCopy] autorelease];
	
	[returnedDictionary addEntriesFromDictionary:[NSDictionary dictionaryWithObjectsAndKeys:
	
		IRKeychainObjectOrEmptyString(self.associatedAccountName), (id)kSecAttrAccount,
		IRKeychainObjectOrEmptyString(self.userDescription), (id)kSecAttrDescription,
		IRKeychainObjectOrEmptyString(self.userComment), (id)kSecAttrComment,
		IRKeychainObjectOrEmptyString(self.userLabel), (id)kSecAttrLabel,
		IRKeychainObjectOrEmptyString(self.serverSecurityDomain), (id)kSecAttrSecurityDomain,
		IRKeychainObjectOrEmptyString(self.serverAddress), (id)kSecAttrServer,
		IRKeychainObjectOrPlaceholder(self.serverPort, [NSNumber numberWithInt:0]), (id)kSecAttrPort,
		SecProtocolFromIRKeychainProtocol(self.serverProtocol), (id)kSecAttrProtocol,
		SecAuthenticationTypeFromIRKeychainAuthenticationType(self.serverAuthenticationType), (id)kSecAttrAuthenticationType,
		IRKeychainObjectOrEmptyString(self.serverPath), (id)kSecAttrPath,
		
	nil]];
	
	for (id aKey in [[returnedDictionary copy] autorelease])
	if ([[returnedDictionary objectForKey:aKey] isEqual:@""] || [[returnedDictionary objectForKey:aKey] isEqual:[@"" dataUsingEncoding:NSUTF8StringEncoding]])
	[returnedDictionary removeObjectForKey:aKey];
	
	return returnedDictionary;

}

- (NSDictionary *) securityItemAttributesDictionary {

	NSMutableDictionary *returnedDictionary = [[[super securityItemAttributesDictionary] mutableCopy] autorelease];
	
	[returnedDictionary addEntriesFromDictionary:[NSDictionary dictionaryWithObjectsAndKeys:
	
		IRKeychainObjectOrEmptyString(self.associatedAccountName), (id)kSecAttrAccount,
		IRKeychainObjectOrEmptyString(self.userDescription), (id)kSecAttrDescription,
		IRKeychainObjectOrEmptyString(self.userComment), (id)kSecAttrComment,
		IRKeychainObjectOrEmptyString(self.userLabel), (id)kSecAttrLabel,
		IRKeychainObjectOrEmptyString(self.serverSecurityDomain), (id)kSecAttrSecurityDomain,
		IRKeychainObjectOrEmptyString(self.serverAddress), (id)kSecAttrServer,
		IRKeychainObjectOrPlaceholder(self.serverPort, [NSNumber numberWithInt:0]), (id)kSecAttrPort,
		SecProtocolFromIRKeychainProtocol(self.serverProtocol), (id)kSecAttrProtocol,
		SecAuthenticationTypeFromIRKeychainAuthenticationType(self.serverAuthenticationType), (id)kSecAttrAuthenticationType,
		IRKeychainObjectOrEmptyString(self.serverPath), (id)kSecAttrPath,
		
	nil]];
	
	return returnedDictionary;

}

@end
